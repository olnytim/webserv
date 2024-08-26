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

#define CONNECTION_TIMEOUT 60
#define MAX_CONTENT_LENGTH 30000000
#define MESSAGE_BUFFER 40000
#define MAX_URI_LENGTH 2000

// Utils

//int ft_stoi(const std::string &str);
std::string statusCodeString(short statusCode);
unsigned int fromHexToDec(const std::string &nb);