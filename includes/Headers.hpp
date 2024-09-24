#pragma once

// STL
#include <vector>
#include <map>
#include <set>
#include <list>
#include <iterator>

// System
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <signal.h>

// Network
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>

// Utils
#include <string>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <fcntl.h>
#include <ctime>
#include <cstdarg>
#include <cstdlib>
#include <dirent.h>
#include <cctype>

#define MAX_CONTENT_LENGTH 30000000
#define MESSAGE_BUFFER 40000

// Utils
std::string statusCodeString(short statusCode);

template <typename T>
std::string to_string(const T &value) {
    std::ostringstream os;
    os << value;
    return os.str();
}