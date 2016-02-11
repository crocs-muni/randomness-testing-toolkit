#include "rtt/utils.h"

namespace rtt {

std::string Utils::itostr(int i , int width) {
    std::stringstream ss;
    ss.width(width);
    ss.fill('0');
    ss << i;
    return ss.str();
}

int Utils::strtoi(const std::string & str) {
    static const std::regex RE_INTEGER { "^-?[0-9]+?$" };
    if(!std::regex_match(str.begin() , str.end() , RE_INTEGER)) {
        throw std::runtime_error("can't convert string \"" + str +"\" into integer: " +
                                 "string contains invalid characters");
    }
    try {
        int result = std::stoi(str);
        return result;
    } catch (std::out_of_range) {
        /* invalid_argument won't be thrown, regex prevents that */
        throw std::runtime_error("can't convert string \"" + str +"\" into integer: " +
                                 "value represented by string is too big");
    }
}

float Utils::strtof(const std::string & str) {
    static const std::regex RE_FLOAT { "^-?[0-9]+?(:?\\.[0-9]+?)?$" };
    if(!std::regex_match(str.begin() , str.end() , RE_FLOAT)) {
        throw std::runtime_error("can't convert string \"" + str + "\" into float: " +
                                 "string contain invalid characters");
    }
    try {
        float result = std::stof(str);
        return result;
    } catch (std::out_of_range) {
        /* invalid_argument won't be thrown, regex prevents that */
        throw std::runtime_error("can't convert string \"" + str + "\" into float: " +
                                 "value represented by string is too big");
    }
}

double Utils::strtod(const std::string & str) {
    static const std::regex RE_FLOAT { "^-?[0-9]+?(:?\\.[0-9]+?)?$" };
    if(!std::regex_match(str.begin() , str.end() , RE_FLOAT)) {
        throw std::runtime_error("can't convert string \"" + str + "\" into double: " +
                                 "string contain invalid characters");
    }
    try {
        float result = std::stod(str);
        return result;
    } catch (std::out_of_range) {
        /* invalid_argument won't be thrown, regex prevents that */
        throw std::runtime_error("can't convert string \"" + str + "\" into double: " +
                                 "value represented by string is too big");
    }
}

std::string Utils::getLastItemInPath(const std::string & path) {
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

std::string Utils::getPathWithoutLastItem(const std::string & path) {
    std::string result;
    int index = path.find_last_of('/');
    result = path.substr(0 , index + 1);
    return result;
}

std::string Utils::getTime() {
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

std::string Utils::getDate() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer , 80 , "%Y-%m-%d" , timeinfo);
    return std::string(buffer);
}

time_t Utils::getRawTime() {
    time_t rawtime;
    time(&rawtime);
    return rawtime;
}

std::string Utils::formatRawTime(const time_t & rawtime ,
                                 const std::string & format) {
    char buffer[80];
    struct tm * timeinfo;
    timeinfo = localtime(&rawtime);
    strftime(buffer , 80 , format.c_str() , timeinfo);
    return buffer;
}

std::vector<std::string> Utils::split(const std::string & toSplit , char separator) {
    std::vector<std::string> result;
    std::string temp;
    for(size_t i = 0 ; i < toSplit.length() ; i++) {
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

void Utils::fixNewlines(std::string & str) {
    std::string::size_type pos = 0;
    while ((pos = str.find("\r\n", pos)) != std::string::npos) {
        str.replace(pos, 2, "\n"); //2 is length of \r\n
    }
}

void Utils::createDirectory(const std::string & path , int access) {
    std::vector<std::string> dirs = split(path , '/');
    if(dirs.empty())
        return;

    std::string current;

    for(const std::string & dir : dirs) {
        current.append(dir + "/");
        if(mkdir(current.c_str() , access) != 0) {
            if(errno != EEXIST)
                throw std::runtime_error("an error number " + itostr(errno) + " "
                                         "occurred when creating directory: " + current);
        }

    }
}

bool Utils::fileExist(const std::string & name) {
    std::ifstream file(name);
    return file.good();
}

void Utils::sort(std::vector<int> & a , unsigned begin) {
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

void Utils::sort2D(std::vector<std::pair<int, int> > & a) {
    // Insert sort
    for(unsigned i = 0 ; i < a.size() ; i++) {
        for(unsigned k = i ; k > 0 ; k--) {
            if(a[k].first < a[k - 1].first) {
                std::iter_swap(a.begin() + k, a.begin() + k - 1);
            } else {
                break;
            }
        }
    }
    // Eliminate duplicities (the latter one survives)
    for(unsigned i = 0 ; ; i++) {
        if(i >= a.size() - 1 || a.size() == 0) break;

        if(a[i].first == a[i + 1].first) {
            a.erase(a.begin() + i);
            i--;
        }
    }
}


std::string Utils::readFileToString(const std::string & path) {
    std::ifstream file(path , std::ios::in);
    if(!file.is_open()) throw std::runtime_error("can't open input file: " + path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    if(file.is_open()) throw std::runtime_error("can't close input file: " + path);
    return buffer.str();
}



void Utils::saveStringToFile(const std::string & path , const std::string & source) {
    std::ofstream file(path , std::ios::out);
    if(!file.is_open()) throw std::runtime_error("can't open output file: " + path);
    file << source;
    file.close();
    if(file.is_open()) throw std::runtime_error("can't close output file: " + path);
}

} // namespace rtt
