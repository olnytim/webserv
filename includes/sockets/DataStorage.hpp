#pragma once

#include "../Headers.hpp"

class DataStorage {
private:
    static std::string getCurrentWorkingDirectory();
public:

    DataStorage();
    std::string root;
    std::map<int, std::string> defaultErrorPages;
    std::map<std::string, std::string> mimeTypes;

    std::string getMimeType(const std::string &extension);
    std::map<int, std::string> getErrorPages();
};
