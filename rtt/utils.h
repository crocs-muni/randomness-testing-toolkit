#ifndef RTT_UTILS_H
#define RTT_UTILS_H

#include <istream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <vector>
#include <regex>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <iomanip>

/* File with global methods declared */

#define my_min(a,b) (((a)<(b))?(a):(b))
#define my_max(a,b) (((a)>(b))?(a):(b))

namespace rtt {

class Utils {
public:
    /** Converts integral value to string.
      * Number is prefixed with 0 if digit count is
      * less than width argument.
      * @param x          integer to be converted
      * @param width      length of resulting string
      * @return string    converted integer
      */
    static std::string itostr(int i , int width = 0);

    /** Converts string to integral value if possible.
      * Throws std::runtime error if string is not
      * numeric or his value is too big to store.
      * @param str              string to convert
      * @return                 converted integer
      * @throws runtime_error   string can't be converted
      */
    static int strtoi(const std::string & str);

    /** Converts string to float value if possible.
      * @brief strtof           String to float
      * @param str              string to convert
      * @return                 converted float
      * @throws runtime_error   argument is not valid
      *                         float or float is too big
      */
    static float strtof(const std::string & str);

    static double strtod(const std::string & str);

    /** Opens file, reads it into string, closes file, returns string
      * @param path                path to file
      * @return                    content of the file
      * @throws runtime_error      when file can't be opened
      */
    static std::string readFileToString(const std::string & path);

    /** Opens file, loads string into it, closes it.
      * Source's content is NOT erased.
      * @param path              path to file
      * @param source            string to be saved
      * @throws runtime_error    when file can't be opened
      */
    static void saveStringToFile(const std::string & path , const std::string & source);

    static void appendStringToFile(const std::string & path , const std::string & source);

    /** Returns string after last separator in path.
      * If no separator is found, whole path is returned.
      * ../../example returns example
      * @param path                path to be parsed
      * @return                    extracted directory or file name
      */
    static std::string getLastItemInPath(const std::string & path);

    /** Returns string before last separator in path (including separator).
      * If no separator is found nothing is returned. If path ends with separator
      * path is returned. ./exampleDir/exampleFile.txt returns ./exampleDir/
      * @param path                path to be parsed
      * @return                    extracted path without last item
      */
    static std::string getPathWithoutLastItem(const std::string & path);

    /** Returns time in [hh:mm:ss] format.
      * @return                time
      */
    static std::string getTime();

    /** Retuns date in yy-mm-dd format.
      * @return                date
      */
    static std::string getDate();

    static time_t getRawTime();

    static std::string formatRawTime(const time_t & rawtime,
                                     const std::string & format);

    /** Splits string into shorter strings, separated by separator
      * @param                 toSplit string to be splitted
      * @return                vector of strings
      */
    static std::vector<std::string> split(const std::string & toSplit , char separator);

    /** Replaces all Windows newlines (\r\n) with Unix newlines (\n).
      * Sometimes Unix system will read \r\n instead of \n from file.
      * Input text files that will be modified (such as script samples)
      * should have \n newline, otherwise strange things will happen.
      * @param str                string to be fixed
    */
    static void fixNewlines(std::string & str);

    static std::vector<int> parseStringWithIntRanges(const std::string & str);

    /**
     * @brief createDirectory   Creates recursive directory structure.
     *                          If some dirs already exist doesn't report.
     *                          Any other failure is reported. Only for Linux
     * @param path              Path to final directory, separator is '/'
     * @param access            Access rights for new dirs, default is 0775
     */
    static void createDirectory(const std::string & path, int access = 0775);

    static bool fileExist(const std::string & name);

    static void rmDirFiles(const std::string & n);

    static std::string getLogFilePath(time_t creationTime ,
                                      const std::string & logDir ,
                                      const std::string & inputFilePath ,
                                      std::string batteryShort = "");

    static std::string intToHex(int num, uint width = 0);

    template<typename T>
    static std::vector<T *> getRawPtrs(const std::vector<std::unique_ptr<T>> & source) {
        std::vector<T *> rval(source.size());
        std::transform(source.begin(), source.end(), rval.begin(),
                       [](const auto & el){ return el.get(); });
        return rval;
    }
};

} // namespace rtt
#endif // RTT_UTILS_H
