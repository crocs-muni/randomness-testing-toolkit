#include "mysqlstorage.h"

namespace rtt {
namespace storage {

const std::string MySQLStorage::objectInfo = "MySQL Storage";

std::unique_ptr<MySQLStorage> MySQLStorage::getInstance(const GlobalContainer & container) {
    std::unique_ptr<MySQLStorage> s (new MySQLStorage());
    s->cliOptions       = container.getCliOptions();
    s->toolkitSettings  = container.getToolkitSettings();
    s->creationTime     = container.getCreationTime();
    s->battId           = s->cliOptions->getBatteryId();

    try {
        s->driver = get_driver_instance();
        s->conn   = std::unique_ptr<sql::Connection>(
                        s->driver->connect("localhost", "test", "test"));
        s->conn->setSchema("rtt");
        /* Commit in finalizeReport, rollback on any error. */
        s->conn->setAutoCommit(false);

        std::unique_ptr<sql::PreparedStatement> insBattStmt(s->conn->prepareStatement(
            "INSERT INTO batteries(name, passed_proportion, alpha, experiment_id) "
            "VALUES (?,?,?,?)"
        ));
        insBattStmt->setString(1, Constants::batteryToString(s->battId));
        insBattStmt->setString(2, "0/0");
        insBattStmt->setDouble(3, Constants::MATH_ALPHA);
        /* 1 is here only for testing!!! */
        insBattStmt->setUInt64(4, 1);
        insBattStmt->execute();

        s->dbBatteryId = s->getLastInsertedId();

    } catch (sql::SQLException &ex) {
        s->conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }

    return s;
}

void MySQLStorage::addNewTest(const std::string & testName) {
    if(dbBatteryId <= 0)
        raiseBugException("battery id not set");

    try {
        ++currTestIdx;

        std::unique_ptr<sql::PreparedStatement> insTestStmt(conn->prepareStatement(
            "INSERT INTO tests(name, partial_alpha, result, test_index, battery_id) "
            "VALUES(?,?,?,?,?)"
        ));

        insTestStmt->setString(1, testName);
        insTestStmt->setDouble(2, 0);
        insTestStmt->setString(3, "failed");
        insTestStmt->setUInt(4, currTestIdx);
        insTestStmt->setUInt64(5, dbBatteryId);
        insTestStmt->execute();

        currDbTestId = getLastInsertedId();
    } catch (sql::SQLException &ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::finalizeTest() {
    if(currDbTestId <= 0)
        raiseBugException("test id not set");

    currDbSubtestId = 0;
    currDbVariantId = 0;
    currDbTestId = 0;
    currVariantIdx = 0;
    currSubtestIdx = 0;
}

void MySQLStorage::addVariant() {
    if(currDbTestId <= 0)
        raiseBugException("test id not set");

    try {
        ++currVariantIdx;

        std::unique_ptr<sql::PreparedStatement> insVariantStmt(conn->prepareStatement(
            "INSERT INTO variants(variant_index, test_id) "
            "VALUES(?,?)"
        ));

        insVariantStmt->setUInt(1, currVariantIdx);
        insVariantStmt->setUInt64(2, currDbTestId);
        insVariantStmt->execute();

        currDbVariantId = getLastInsertedId();
    } catch (sql::SQLException &ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::finalizeVariant() {
    if(currDbVariantId <= 0)
        raiseBugException("variant id not set");

    currDbSubtestId = 0;
    currDbVariantId = 0;
    currSubtestIdx = 0;
}

void MySQLStorage::addSubTest() {
    if(currDbVariantId <= 0)
        raiseBugException("variant id not set");

    try {
        ++currSubtestIdx;

        std::unique_ptr<sql::PreparedStatement> insSubtestStmt(conn->prepareStatement(
            "INSERT INTO subtests(subtest_index, variant_id) "
            "VALUES(?,?)"
        ));

        insSubtestStmt->setUInt(1, currSubtestIdx);
        insSubtestStmt->setUInt64(2, currDbVariantId);
        insSubtestStmt->execute();

        currDbSubtestId = getLastInsertedId();
    } catch (sql::SQLException &ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::finalizeSubTest() {
    if(currDbSubtestId <= 0)
        raiseBugException("subtest id not set");

    currDbSubtestId = 0;
}

void MySQLStorage::setTestResult(bool passed) {
    if(currDbTestId <= 0)
        raiseBugException("test id not set");

    try {
        std::string val = "failed";
        ++totalTestCount;
        if(passed) {
            ++passedTestCount;
            val = "passed";
        }

        std::unique_ptr<sql::PreparedStatement> updTestResStmt(conn->prepareStatement(
            "UPDATE tests SET result=? WHERE id=?"
        ));
        updTestResStmt->setString(1, val);
        updTestResStmt->setUInt64(2, currDbTestId);
        updTestResStmt->execute();

    } catch (sql::SQLException &ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::setTestPartialAlpha(double alpha) {
    if(currDbTestId <= 0)
        raiseBugException("test id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> updTestPartAlpStmt(conn->prepareStatement(
            "UPDATE tests SET partial_alpha=? WHERE id=?"
        ));
        updTestPartAlpStmt->setDouble(1, alpha);
        updTestPartAlpStmt->setUInt64(2, currDbTestId);
        updTestPartAlpStmt->execute();

    } catch(sql::SQLException & ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::setUserSettings(const std::vector<std::string> & options) {
    if(currDbVariantId <= 0)
        raiseBugException("variant id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insUserSettStmt(conn->prepareStatement(
            "INSERT INTO user_settings(name, value, variant_id) "
            "VALUES(?,?,?)"
        ));
        insUserSettStmt->setUInt64(3, currDbVariantId);

        for(const std::string & sett : options) {
            /* Only temporarily, till new interface is implemented :) */
            auto settPair = Utils::split(sett, ':');
            insUserSettStmt->setString(1, settPair.at(0));
            insUserSettStmt->setString(2, settPair.at(1));
            insUserSettStmt->execute();
        }

    } catch(sql::SQLException & ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::setTestParameters(const std::vector<std::string> & options) {
    if(currDbSubtestId <= 0)
        raiseBugException("subtest id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insTestParamsStmt(conn->prepareStatement(
            "INSERT INTO test_parameters(name, value, subtest_id) "
            "VALUES(?,?,?)"
        ));
        insTestParamsStmt->setUInt64(3, currDbSubtestId);

        for(const std::string & param : options) {
            /* Only temporarily, till new interface is implemented :) */
            auto paramPair = Utils::split(param, '=');
            insTestParamsStmt->setString(1, paramPair.at(0));
            insTestParamsStmt->setString(2, paramPair.at(1));
            insTestParamsStmt->execute();
        }

    } catch(sql::SQLException & ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::setWarningMessages(const std::vector<std::string> & warnings) {
    if(currDbVariantId <= 0)
        raiseBugException("variant id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insWarnMessStmt(conn->prepareStatement(
            "INSERT INTO warning_messages(message, variant_id) "
            "VALUES(?,?)"
        ));
        insWarnMessStmt->setUInt64(2, currDbVariantId);

        for(const std::string & mess : warnings) {
            insWarnMessStmt->setString(1, mess);
            insWarnMessStmt->execute();
        }

    } catch(sql::SQLException & ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::setErrorMessages(const std::vector<std::string> & errors) {
    if(currDbVariantId <= 0)
        raiseBugException("variant id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insErrMessStmt(conn->prepareStatement(
            "INSERT INTO error_messages(message, variant_id) "
            "VALUES(?,?)"
        ));
        insErrMessStmt->setUInt64(2, currDbVariantId);

        for(const std::string & mess : errors) {
            insErrMessStmt->setString(1, mess);
            insErrMessStmt->execute();
        }

    } catch(sql::SQLException & ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::setStdErrMessages(const std::vector<std::string> & stderr) {
    if(currDbVariantId <= 0)
        raiseBugException("variant id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insStderrMessStmt(conn->prepareStatement(
            "INSERT INTO stderr_messages(message, variant_id) "
            "VALUES(?,?)"
        ));
        insStderrMessStmt->setUInt64(2, currDbVariantId);

        for(const std::string & mess : stderr) {
            insStderrMessStmt->setString(1, mess);
            insStderrMessStmt->execute();
        }

    } catch(sql::SQLException & ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::addStatisticResult(const std::string & statName,
                                      double value, int precision, bool passed){
    if(currDbSubtestId <= 0)
        raiseBugException("subtest id not set");

    try {
        std::string passedStr = "failed";
        if(passed)
            passedStr = "passed";

        std::unique_ptr<sql::PreparedStatement> insStatStmt(conn->prepareStatement(
            "INSERT INTO statistics(name, value, result, subtest_id) "
            "VALUES(?,?,?,?)"
        ));
        insStatStmt->setString(1, statName);
        insStatStmt->setDouble(2, value);
        insStatStmt->setString(3, passedStr);
        insStatStmt->setUInt64(4, currDbSubtestId);
        insStatStmt->execute();

    } catch(sql::SQLException & ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::addPValues(const std::vector<double> & pvals, int precision) {
    if(currDbSubtestId <= 0)
        raiseBugException("subtest id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insPValsStmt(conn->prepareStatement(
            "INSERT INTO p_values(value, subtest_id) "
            "VALUES(?,?)"
        ));

        for(const double & pval : pvals) {
            insPValsStmt->setDouble(1, pval);
            insPValsStmt->setUInt64(2, currDbSubtestId);
            insPValsStmt->execute();
        }
    } catch(sql::SQLException & ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::finalizeReport() {
    if(dbBatteryId <= 0)
        raiseBugException("battery id not set");

    /* Finishing call, after this, subsequent calls to this object will fail. */
    currDbSubtestId = 0;
    currDbVariantId = 0;
    currDbTestId = 0;
    currTestIdx = 0;
    currVariantIdx = 0;
    currSubtestIdx = 0;

    try {
        std::string passedTestProp = { Utils::itostr(passedTestCount) + "/" + Utils::itostr(totalTestCount) };

        std::unique_ptr<sql::PreparedStatement> updBattPassProp(conn->prepareStatement(
            "UPDATE batteries SET passed_proportion=? WHERE id=?"
        ));
        updBattPassProp->setString(1, passedTestProp);
        updBattPassProp->setUInt64(2, dbBatteryId);
        updBattPassProp->execute();

        dbBatteryId = 0;

        /* Final commit, will confirm whole transaction */
        conn->commit();

    } catch(sql::SQLException & ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

uint64_t MySQLStorage::getLastInsertedId() {
    try {
        auto stmt = std::unique_ptr<sql::Statement>(conn->createStatement());
        auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(
            "SELECT @@identity AS id"
        ));
        if(res->next())
            return res->getUInt64("id");

        throw RTTException(objectInfo, "error when getting last inserted id");
    } catch (sql::SQLException &ex) {
        conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}


} // namespace storage
} // namespace rtt
