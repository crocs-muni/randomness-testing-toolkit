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
    static std::string itostr(int i , int width = 0) {
        std::stringstream ss;
        ss.width(width);
        ss.fill('0');
        ss << i;
        return ss.str();
    };

    /** Opens file, reads it into string, closes file, returns string
      * @param path                path to file
      * @return                    content of the file
      * @throws runtime_error      when file can't be opened
      */
    /*static std::string readFileToString(const std::string & path) {
        std::ifstream file(path , std::ios::in);
        if(!file.is_open()) throw std::runtime_error("can't open input file: " + path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        if(file.is_open()) throw std::runtime_error("can't close input file: " + path);
        return buffer.str();
    }*/

    /** Opens file, loads string into it, closes it.
      * Source's content is NOT erased.
      * @param path              path to file
      * @param source            string to be saved
      * @throws runtime_error    when file can't be opened
      */
    /*static void saveStringToFile(const std::string & path , const std::string & source) {
        std::ofstream file(path , std::ios::out);
        if(!file.is_open()) throw std::runtime_error("can't open output file: " + path);
        file << source;
        file.close();
        if(file.is_open()) throw std::runtime_error("can't close output file: " + path);
    }*/

    /** Returns string after last separator in path.
      * If no separator is found, whole path is returned.
      * ../../example returns example
      * @param path                path to be parsed
      * @return                    extracted directory or file name
      */
    static std::string getLastItemInPath(const std::string & path) {
        std::string result;
        for(int i = path.length() - 1 ; i >= 0 ; i--) {
            if(path[i] == '/') {
                break;
            } else {
                result.insert(result.begin() , path[i]);
            }
        }
        return result;
    }

    /** Returns string before last separator in path (including separator).
      * If no separator is found nothing is returned. If path ends with separator
      * path is returned. ./exampleDir/exampleFile.txt returns ./exampleDir/
      * @param path                path to be parsed
      * @return                    extracted path without last item
      */
    static std::string getPathWithoutLastItem(const std::string & path) {
        std::string result;
        int index = path.find_last_of('/');
        result = path.substr(0 , index + 1);
        return result;
    }

    /** Returns time in [hh:mm:ss] format.
      * @return                time
      */
    static std::string getTime() {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer , 80 , "%H:%M:%S" , timeinfo);
        std::stringstream temp;
        temp << "[" << buffer << "] ";
        return temp.str();
    }

    /** Retuns date in yy-mm-dd format.
      * @return                date
      */
    static std::string getDate() {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer , 80 , "%Y-%m-%d" , timeinfo);
        return std::string(buffer);
    }

    /** Splits string into shorter strings, separated by separator
      * @param                 toSplit string to be splitted
      * @return                vector of strings
      */
    static std::vector<std::string> split(const std::string & toSplit , char separator) {
        std::vector<std::string> result;
        std::string temp;
        for(unsigned i = 0 ; i < toSplit.length() ; i++) {
            if(toSplit[i] != separator) {
                temp.push_back(toSplit[i]);
            } else {
                if(temp.length() > 0) result.push_back(temp);
                temp.clear();
            }
        }
        if(temp.length() > 0) result.push_back(temp);
        return result;
    }

    /** Replaces all Windows newlines (\r\n) with Unix newlines (\n).
      * Sometimes Unix system will read \r\n instead of \n from file.
      * Input text files that will be modified (such as script samples)
      * should have \n newline, otherwise strange things will happen.
      * @param str                string to be fixed
    */
    static void fixNewlines(std::string & str) {
        std::string::size_type pos = 0;
        while ((pos = str.find("\r\n", pos)) != std::string::npos) {
            str.replace(pos, 2, "\n"); //2 is length of \r\n
        }
    }

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
    static void sort(std::vector<int> & a , unsigned begin = 0) {
        for(unsigned i = begin ; i < a.size() ; i++) {
            for(unsigned k = i ; k > begin ; k--) {
                if(a[k] < a[k - 1]) {
                    std::iter_swap(a.begin() + k, a.begin() + k - 1);
                } else {
                    break;
                }
            }
        }
        for(unsigned i = begin ; ; i++) {
            if(i >= a.size() - 1 || a.size() == 0) break;
            if(a[i] == a[i + 1]) {
                a.erase(a.begin() + i);
                i--;
            }
        }
    }
};
#endif //UTILS_H
