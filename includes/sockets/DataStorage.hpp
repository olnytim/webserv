#pragma once

//#include <map>
//#include <string>
//#include <cstdio>
//#include <unistd.h>
#include "../Headers.hpp"

class DataStorage {
private:
    static std::string getCurrentWorkingDirectory();
    static std::map<std::string, std::string> initMimeTypes();
    static std::map<int, std::string> defaultErrorPages;

public:
    DataStorage();
    static std::string root;
    static std::map<std::string, std::string> MimeTypes;
    static void initDefaultErrorPages();
};
