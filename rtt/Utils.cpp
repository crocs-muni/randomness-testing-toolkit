#include <Utils.h>

std::string Utils::itostr(int i , int width) {
    std::stringstream ss;
    ss.width(width);
    ss.fill('0');
    ss << i;
    return ss.str();
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

std::vector<std::string> Utils::split(const std::string & toSplit , char separator) {
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

void Utils::fixNewlines(std::string & str) {
    std::string::size_type pos = 0;
    while ((pos = str.find("\r\n", pos)) != std::string::npos) {
        str.replace(pos, 2, "\n"); //2 is length of \r\n
    }
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

/*
std::string Utils::readFileToString(const std::string & path) {
    std::ifstream file(path , std::ios::in);
    if(!file.is_open()) throw std::runtime_error("can't open input file: " + path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    if(file.is_open()) throw std::runtime_error("can't close input file: " + path);
    return buffer.str();
}
*/

/*
void Utils::saveStringToFile(const std::string & path , const std::string & source) {
    std::ofstream file(path , std::ios::out);
    if(!file.is_open()) throw std::runtime_error("can't open output file: " + path);
    file << source;
    file.close();
    if(file.is_open()) throw std::runtime_error("can't close output file: " + path);
}
*/
