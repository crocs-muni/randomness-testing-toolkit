#include "mysqlstorage.h"

namespace rtt {
namespace storage {

const std::string MySQLStorage::objectInfo = "MySQL Storage";

std::unique_ptr<MySQLStorage> MySQLStorage::getInstance(const GlobalContainer & container) {
    std::unique_ptr<MySQLStorage> s (new MySQLStorage());
    s->rttCliOptions    = container.getRttCliOptions();
    s->toolkitSettings  = container.getToolkitSettings();
    s->creationTime     = container.getCreationTime();
    s->gContainer       = &container;
    s->battery          = s->rttCliOptions->getBatteryArg();

    s->dbAddress = s->rttCliOptions->hasMysqlDbHost() ?
                   s->rttCliOptions->getMysqlDbHost() :
                   s->toolkitSettings->getRsMysqlAddress();
    s->dbAddress.append(":");
    s->dbAddress.append(s->rttCliOptions->hasMysqlDbPort() ?
                     std::to_string(s->rttCliOptions->getMysqlDbPort()) :
                     s->toolkitSettings->getRsMysqlPort());

    s->connectDb();
    return s;
}

void MySQLStorage::connectDb() {
    try {
        driver = get_driver_instance();
        conn   = std::unique_ptr<sql::Connection>(
            driver->connect(dbAddress,
                               toolkitSettings->getRsMysqlUserName(),
                               toolkitSettings->getRsMysqlPwd()));
        conn->setSchema(toolkitSettings->getRsMysqlDbName());
        /* Commit in finalizeReport, rollback on any error. */
        conn->setAutoCommit(false);

    } catch (sql::SQLException &ex) {
        gContainer->getLogger()->error(std::string("DB Connect failed: ") + std::string(ex.what()));
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::init() {

}

void MySQLStorage::initBatteryIfNeeded() {
    if (dbBatteryId == 0){
        initBattery();
    }
}

void MySQLStorage::initBattery() {
    if(dbBatteryId > 0)
        raiseBugException("storage was already initialized");

    std::unique_ptr<sql::PreparedStatement> insBattStmt(conn->prepareStatement(
        "INSERT INTO batteries(name, passed_tests, total_tests, alpha, experiment_id, job_id) "
        "VALUES (?,?,?,?,?,?)"
    ));
    insBattStmt->setString(1, battery.getName());
    insBattStmt->setUInt64(2, 0);
    insBattStmt->setUInt64(3, 0);
    insBattStmt->setDouble(4, Constants::MATH_ALPHA);
    insBattStmt->setUInt64(5, rttCliOptions->getMysqlDbEid());
    if (rttCliOptions->hasJid()){
        insBattStmt->setUInt64(6, rttCliOptions->getJid());
    } else {
        insBattStmt->setNull(6, sql::DataType::BIGINT);
    }
    insBattStmt->execute();

    dbBatteryId = getLastInsertedId();
}

void MySQLStorage::writeResults(const std::vector<batteries::ITestResult *> & testResults) {
    if(dbBatteryId <= 0)
        raiseBugException("battery id not set");
    if(testResults.empty())
        raiseBugException("empty results");

    auto batteryConfiguration = gContainer->getBatteryConfiguration();
    bool skipPvalueStorage = false;
    if (batteryConfiguration != nullptr && batteryConfiguration->hasSkipPvalueStorage()) {
        skipPvalueStorage = batteryConfiguration->skipPvalueStorage();
    } else if (rttCliOptions->hasSkipPvalues()) {
        skipPvalueStorage = rttCliOptions->getSkipPvalues();
    } else if (toolkitSettings != nullptr && toolkitSettings->hasShouldSkipPvalueStorage()){
        skipPvalueStorage = toolkitSettings->shouldSkipPvalueStorage();
    }

    gContainer->getLogger()->info(std::string("Pvalue storage skipped: ") + (skipPvalueStorage ? "y" : "n"));

    /* Storing actual results */
    for(const auto & testRes : testResults) {
        addNewTest(testRes->getTestName());

        if(testRes->getOptionalPassed().second) {
            setTestResult(testRes->getOptionalPassed().first);
            setTestPartialAlpha(testRes->getPartialAlpha());
        }

        const auto & variantResults = testRes->getVariantResults();
        for(const auto & varRes : variantResults) {
            addVariant();

            setUserSettings(varRes.getUserSettings());
            setVariantWarnings(varRes.getBatteryOutput().getWarnings());
            setVariantErrors(varRes.getBatteryOutput().getErrors());
            setVariantStdErr(Utils::split(varRes.getBatteryOutput().getStdErr(), '\n'));

            const auto & subResults = varRes.getSubResults();
            for(const batteries::result::SubTestResult & subRes : subResults) {
                addSubTest();

                setTestParameters(subRes.getTestParameters());

                for(const batteries::result::Statistic & stat : subRes.getStatistics()) {
                    addStatisticResult(stat.getName(), stat.getValue(),
                                       testRes->isPValuePassing(stat.getValue()));
                }

                if(!skipPvalueStorage && subRes.getPvalues().size() > 0)
                    addPValues(subRes.getPvalues());

                finalizeSubTest();
            }
            finalizeVariant();
        }
        finalizeTest();
    }
}

void MySQLStorage::close() {
    if(dbBatteryId <= 0)
        raiseBugException("storage wasn't initialized");

    finalizeReport();

    /* Resetting state of the storage. */
    dbBatteryId = 0;
    currDbTestId = 0;
    currDbVariantId = 0;
    currDbSubtestId = 0;
    currTestIdx = 0;
    currSubtestIdx = 0;
    currVariantIdx = 0;
    totalTestCount = 0;
    passedTestCount = 0;

    try {
        /* Final commit, will confirm whole transaction */
        conn->commit();
    } catch(sql::SQLException & ex) {
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::addBatteryError(const std::string & error) {
    addBatteryErrors({error});
}

void MySQLStorage::addBatteryErrors(const std::vector<std::string> & errors) {
    if(dbBatteryId <= 0)
        raiseBugException("battery id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insBattError(conn->prepareStatement(
            "INSERT INTO battery_errors(message, battery_id) "
            "VALUES(?,?)"
        ));
        insBattError->setUInt64(2, dbBatteryId);

        for(const std::string & e : errors) {
            insBattError->setString(1, e);
            insBattError->execute();
        }

    } catch(sql::SQLException & ex) {
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::addBatteryWarning(const std::string & warning) {
    addBatteryWarnings({warning});
}

void MySQLStorage::addBatteryWarnings(const std::vector<std::string> & warnings) {
    if(dbBatteryId <= 0)
        raiseBugException("battery id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insBattWarning(conn->prepareStatement(
            "INSERT INTO battery_warnings(message, battery_id) "
            "VALUES(?,?)"
        ));
        insBattWarning->setUInt64(2, dbBatteryId);

        for(const std::string & w : warnings) {
            insBattWarning->setString(1, w);
            insBattWarning->execute();
        }

    } catch(sql::SQLException & ex) {
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

/*
                     __                       __
                    |  \                     |  \
  ______    ______   \$$ __     __  ______  _| $$_     ______
 /      \  /      \ |  \|  \   /  \|      \|   $$ \   /      \
|  $$$$$$\|  $$$$$$\| $$ \$$\ /  $$ \$$$$$$\\$$$$$$  |  $$$$$$\
| $$  | $$| $$   \$$| $$  \$$\  $$ /      $$ | $$ __ | $$    $$
| $$__/ $$| $$      | $$   \$$ $$ |  $$$$$$$ | $$|  \| $$$$$$$$
| $$    $$| $$      | $$    \$$$   \$$    $$  \$$  $$ \$$     \
| $$$$$$$  \$$       \$$     \$     \$$$$$$$   \$$$$   \$$$$$$$
| $$
| $$
 \$$
*/
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
        if(conn)
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
        if(conn)
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
        if(conn)
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
        if(conn)
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
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::setUserSettings(
        const std::vector<std::pair<std::string, std::string>> & options) {
    if(currDbVariantId <= 0)
        raiseBugException("variant id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insUserSettStmt(conn->prepareStatement(
            "INSERT INTO user_settings(name, value, variant_id) "
            "VALUES(?,?,?)"
        ));
        insUserSettStmt->setUInt64(3, currDbVariantId);

        for(const auto & sett : options) {
            insUserSettStmt->setString(1, sett.first);
            insUserSettStmt->setString(2, sett.second);
            insUserSettStmt->execute();
        }

    } catch(sql::SQLException & ex) {
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::setTestParameters(
        const std::vector<std::pair<std::string, std::string> > & options) {
    if(currDbSubtestId <= 0)
        raiseBugException("subtest id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insTestParamsStmt(conn->prepareStatement(
            "INSERT INTO test_parameters(name, value, subtest_id) "
            "VALUES(?,?,?)"
        ));
        insTestParamsStmt->setUInt64(3, currDbSubtestId);

        for(const auto & param : options) {
            insTestParamsStmt->setString(1, param.first);
            insTestParamsStmt->setString(2, param.second);
            insTestParamsStmt->execute();
        }

    } catch(sql::SQLException & ex) {
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::setVariantWarnings(const std::vector<std::string> & warnings) {
    if(currDbVariantId <= 0)
        raiseBugException("variant id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insWarnMessStmt(conn->prepareStatement(
            "INSERT INTO variant_warnings(message, variant_id) "
            "VALUES(?,?)"
        ));
        insWarnMessStmt->setUInt64(2, currDbVariantId);

        for(const std::string & mess : warnings) {
            insWarnMessStmt->setString(1, mess);
            insWarnMessStmt->execute();
        }

    } catch(sql::SQLException & ex) {
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::setVariantErrors(const std::vector<std::string> & errors) {
    if(currDbVariantId <= 0)
        raiseBugException("variant id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insErrMessStmt(conn->prepareStatement(
            "INSERT INTO variant_errors(message, variant_id) "
            "VALUES(?,?)"
        ));
        insErrMessStmt->setUInt64(2, currDbVariantId);

        for(const std::string & mess : errors) {
            insErrMessStmt->setString(1, mess);
            insErrMessStmt->execute();
        }

    } catch(sql::SQLException & ex) {
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::setVariantStdErr(const std::vector<std::string> & stderr) {
    if(currDbVariantId <= 0)
        raiseBugException("variant id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> insStderrMessStmt(conn->prepareStatement(
            "INSERT INTO variant_stderr(message, variant_id) "
            "VALUES(?,?)"
        ));
        insStderrMessStmt->setUInt64(2, currDbVariantId);

        for(const std::string & mess : stderr) {
            insStderrMessStmt->setString(1, mess);
            insStderrMessStmt->execute();
        }

    } catch(sql::SQLException & ex) {
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::addStatisticResult(const std::string & statName,
                                      double value, bool passed){
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
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::addPValues(const std::vector<double> & pvals) {
    if(currDbSubtestId <= 0)
        raiseBugException("subtest id not set");
    if (pvals.size() == 0)
        return;

    const size_t batchSize = 100;
    const size_t chunks = my_max(1, pvals.size() / batchSize);
    auto chunkVct = Utils::chunks(pvals.begin(), pvals.end(), chunks);
    size_t lastChunkSize = 0;

    try {
        std::unique_ptr<sql::PreparedStatement> insPValsStmt;
        for (const auto & cur : chunkVct){
            const auto curSize = std::distance(cur.first, cur.second);
            if (lastChunkSize != curSize || !insPValsStmt) {
                std::ostringstream os;
                os << "INSERT INTO p_values(value, subtest_id) VALUES(?,?)";
                if (curSize > 1) {
                    std::fill_n(std::ostream_iterator<std::string>(os), curSize - 1, ",(?,?)");
                }
                insPValsStmt.reset(conn->prepareStatement(os.str()));
                lastChunkSize = curSize;
            }

            unsigned int idx = 1;
            for(auto iter = cur.first; iter != cur.second; iter++, idx += 2){
                insPValsStmt->setDouble(idx, *iter);
                insPValsStmt->setUInt64(idx + 1, currDbSubtestId);
            }
            insPValsStmt->execute();
        }
    } catch(sql::SQLException & ex) {
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

void MySQLStorage::finalizeReport() {
    if(dbBatteryId <= 0)
        raiseBugException("battery id not set");

    try {
        std::unique_ptr<sql::PreparedStatement> updBattPassProp(conn->prepareStatement(
            "UPDATE batteries SET passed_tests=?, total_tests=? WHERE id=?"
        ));
        updBattPassProp->setUInt64(1, passedTestCount);
        updBattPassProp->setUInt64(2, totalTestCount);
        updBattPassProp->setUInt64(3, dbBatteryId);
        updBattPassProp->execute();

    } catch(sql::SQLException & ex) {
        if(conn)
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
        if(conn)
            conn->rollback();
        throw RTTException(objectInfo, ex.what());
    }
}

bool MySQLStorage::pingConnection() {
    try {
        auto stmt = std::unique_ptr<sql::Statement>(conn->createStatement());
        auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(
            "SELECT 1 FROM jobs LIMIT 1"
        ));

        if(res->next()) {
            return true;
        }

        gContainer->getLogger()->warn(std::string("Ping DB failed path 1"));

    } catch (sql::SQLException &ex) {
        gContainer->getLogger()->warn(std::string("Ping DB failed with exception: ") + std::string(ex.what()));
        if(conn) {
            try {
                conn->rollback();
            } catch (sql::SQLException &ex2) {
                gContainer->getLogger()->warn(std::string("Ping DB: rollback failed with exception: ") + std::string(ex2.what()));
            }
        }
    }
    return false;
}

bool MySQLStorage::reconnectIfNeeded() {
    if (pingConnection()) {
        return false;
    }

    const auto log = gContainer->getLogger();
    log->error(std::string("Ping DB failed, trying to reconnect"));

    if (conn) {
        try {
            conn->close();
        } catch (sql::SQLException &ex) {}
        conn.reset();
    }

    connectDb();

    // Battery not committed, reset state.
    dbBatteryId = 0;
    init();
    return true;
}

void MySQLStorage::checkStorage() {
    // Ping database, reopen connection if needed
    const auto reconnected = reconnectIfNeeded();
    if (reconnected && (currDbTestId > 0 || currTestIdx > 0)) {
        throw RTTException(objectInfo, std::string("DB link reconnected but some results were lost, aborting"));
    }

    // If DB is reconnected, battery is lost, reinit if needed.
    // Also lazy inits if DB works but battery was not added yet.
    initBatteryIfNeeded();
}

} // namespace storage
} // namespace rtt
