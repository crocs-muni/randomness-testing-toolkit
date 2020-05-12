#include "rtt/utils.h"

namespace rtt {

std::string Utils::itostr(int i , int width) {
    std::stringstream ss;
    ss.width(width);
    ss.fill('0');
    ss << i;
    return ss.str();
}

static const std::regex RE_INTEGER("^-?[0-9]+?$");
static const std::regex RE_FLOAT("^-?[0-9]+?(:?\\.[0-9]+?)?$");

int Utils::strtoi(const std::string & str) {
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

std::vector<int> Utils::parseStringWithIntRanges(const std::string &str) {
    std::vector<std::string> values = Utils::split(str , ' ');
    std::vector<std::string> range;
    std::vector<int> rval;
    int botRange = 0;
    int topRange = 0;

    for(const std::string & value : values) {
        if(value.find('-') == std::string::npos) {
            /* Only integer is in value */
            rval.push_back(Utils::strtoi(value));
        } else {
            /* Range of integers */
            range = Utils::split(value , '-');
            if(range.size() != 2) /* more than one dash in string, why would you do that??? */
                throw std::runtime_error("invalid range denoted in string " + value);
            botRange = Utils::strtoi(range.front());
            topRange = Utils::strtoi(range.back());
            for( ; botRange <= topRange ; ++botRange)
                rval.push_back(botRange);
        }
    }

    /* Sorting ensures correct order and eliminates duplicities */
    std::sort(rval.begin(), rval.end());
    return rval;
}

void Utils::createDirectory(const std::string & path , int access) {
    std::vector<std::string> dirs = split(path , '/');
    if(dirs.empty())
        return;

    std::string current;
    /* Handles absolute paths */
    if(path.front() == '/')
        current.push_back('/');

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

void Utils::rmDirFiles(const std::string & n) {
    std::string name = n;
    if(name.back() != '/')
        name.append("/");

    std::string filename;
    DIR * d = opendir(name.c_str());

    if(d) {
        struct dirent * p;

        while((p = readdir(d))) {
            if(strcmp(p->d_name , ".") == 0 || strcmp(p->d_name , "..") == 0)
                continue;

            filename = name + p->d_name;
            unlink(filename.c_str());
        }
    }
    closedir(d);
}

std::string Utils::getLogFilePath(time_t creationTime,
                                  const std::string & logDir,
                                  const std::string & inputFilePath,
                                  std::string batteryShort,
                                  std::uint64_t jid) {
    std::string rval;
    rval.append(logDir);
    rval.append(Utils::formatRawTime(creationTime , "%Y%m%d%H%M%S"));
    if(!batteryShort.empty()) {
        rval.append("-");
        rval.append(batteryShort);
    }
    rval.append("-");
    auto inputFileName = Utils::getLastItemInPath(inputFilePath);
    std::replace(inputFileName.begin(), inputFileName.end(), '.', '_');
    rval.append(inputFileName);
    if (jid > 0){
        rval.append("-");
        rval.append(std::to_string(jid));
    }
    rval.append("-log.txt");
    return rval;
}

std::string Utils::intToHex(int num, uint width) {
    std::stringstream rval;
    rval << "0x" << std::setfill('0') << std::setw(width)
         << std::hex << std::uppercase << num;
    return rval.str();
}

std::string Utils::readFileToString(const std::string & path) {
    std::ifstream file(path , std::ios::in);
    if(!file.is_open())
        throw std::runtime_error("can't open input file: " + path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

void Utils::saveStringToFile(const std::string & path , const std::string & source) {
    std::ofstream file(path , std::ios::out);
    if(!file.is_open())
        throw std::runtime_error("can't open output file: " + path);
    file << source;
    file.close();
}

void Utils::appendStringToFile(const std::string & path, const std::string & source) {
    std::ofstream file(path , std::ios::out | std::ios::app);
    if(!file.is_open())
        throw std::runtime_error("can't open output file: " + path);
    file << source;
    file.close();
}

} // namespace rtt
