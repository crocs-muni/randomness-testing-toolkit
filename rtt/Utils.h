#ifndef UTILS_H
#define UTILS_H

#include <istream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// File with global methods declared

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

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

    /** Converts string to numeric value if possible.
      * Throws std::runtime error if string is not
      * numerir or his value is too big to store.
      * @param str              string to convert
      * @return                 converted integer
      * @throws runtime_error   string can't be converted
      */
    static int strtoi(std::string str);

    /** Opens file, reads it into string, closes file, returns string
      * @param path                path to file
      * @return                    content of the file
      * @throws runtime_error      when file can't be opened
      */
    //static std::string readFileToString(const std::string & path);

    /** Opens file, loads string into it, closes it.
      * Source's content is NOT erased.
      * @param path              path to file
      * @param source            string to be saved
      * @throws runtime_error    when file can't be opened
      */
    //static void saveStringToFile(const std::string & path , const std::string & source);

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

    /** Creates directory.
      * Permissions 0777 under Linux.
      * @param path            absolute or relative
      */
    /*static void createDirectory(const std::string & path) {
        if(mkdir(path.c_str() , 0777) != 0) {
            if(errno != EEXIST) { throw std::runtime_error("error when creating directory: " + path); }
        }
    }*/

    /** Simple insert sort algorithm, sorts vector of integer in ascending order,
      * after sorting kills duplicities.
      * @param a                   vector to be sorted
      * @param begin               denotes from which index should start sorting.
      *                            0 sorts whole vector, 1 leaves first element unmoved, etc...
      */
    static void sort(std::vector<int> & a , unsigned begin = 0);

    static void sort2D(std::vector<std::pair<int , int>> & a );
};
#endif //UTILS_H
