#pragma once

/* STL containers */
#include <map>
#include <vector>
#include <set>
#include <iterator>
#include <list>

/* System */
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

/* Network */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

/* C++ */
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <fcntl.h>
#include <dirent.h>

/* other includes */
#include "parsing/LocationBlock.hpp"
#include "parsing/ServerBlock.hpp"
#include "parsing/config.hpp"

#define MAX_URI_LENGTH 2048
#define MAX_CONTENT_LENGTH 30000000
#define CONNECTION_TIMEOUT 60
#define MESSAGE_BUFFER 40000

template <typename T>
std::string toString(const T val)
{
    std::stringstream ss;
    ss << val;
    return ss.str();
}

/* utils */

int ft_stoi(const std::string &str);
unsigned int fromHexToDec(const std::string& nb);
std::string statusCodeString(short statusCode);
std::string getErrorPage(short statusCode);
int buildHtmlIndex(std::string &, std::vector<uint8_t> &, size_t &);