# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Users/trgalyautdinov/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake

# The command to remove a file.
RM = /Users/trgalyautdinov/Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/trgalyautdinov/webserv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/trgalyautdinov/webserv/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/webserv.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/webserv.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/webserv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/webserv.dir/flags.make

CMakeFiles/webserv.dir/srcs/main.cpp.o: CMakeFiles/webserv.dir/flags.make
CMakeFiles/webserv.dir/srcs/main.cpp.o: /Users/trgalyautdinov/webserv/srcs/main.cpp
CMakeFiles/webserv.dir/srcs/main.cpp.o: CMakeFiles/webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/webserv.dir/srcs/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserv.dir/srcs/main.cpp.o -MF CMakeFiles/webserv.dir/srcs/main.cpp.o.d -o CMakeFiles/webserv.dir/srcs/main.cpp.o -c /Users/trgalyautdinov/webserv/srcs/main.cpp

CMakeFiles/webserv.dir/srcs/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/webserv.dir/srcs/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trgalyautdinov/webserv/srcs/main.cpp > CMakeFiles/webserv.dir/srcs/main.cpp.i

CMakeFiles/webserv.dir/srcs/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/webserv.dir/srcs/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trgalyautdinov/webserv/srcs/main.cpp -o CMakeFiles/webserv.dir/srcs/main.cpp.s

CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.o: CMakeFiles/webserv.dir/flags.make
CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.o: /Users/trgalyautdinov/webserv/srcs/parsing/LocationBlock.cpp
CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.o: CMakeFiles/webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.o -MF CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.o.d -o CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.o -c /Users/trgalyautdinov/webserv/srcs/parsing/LocationBlock.cpp

CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trgalyautdinov/webserv/srcs/parsing/LocationBlock.cpp > CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.i

CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trgalyautdinov/webserv/srcs/parsing/LocationBlock.cpp -o CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.s

CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.o: CMakeFiles/webserv.dir/flags.make
CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.o: /Users/trgalyautdinov/webserv/srcs/parsing/ServerBlock.cpp
CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.o: CMakeFiles/webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.o -MF CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.o.d -o CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.o -c /Users/trgalyautdinov/webserv/srcs/parsing/ServerBlock.cpp

CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trgalyautdinov/webserv/srcs/parsing/ServerBlock.cpp > CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.i

CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trgalyautdinov/webserv/srcs/parsing/ServerBlock.cpp -o CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.s

CMakeFiles/webserv.dir/srcs/parsing/config.cpp.o: CMakeFiles/webserv.dir/flags.make
CMakeFiles/webserv.dir/srcs/parsing/config.cpp.o: /Users/trgalyautdinov/webserv/srcs/parsing/config.cpp
CMakeFiles/webserv.dir/srcs/parsing/config.cpp.o: CMakeFiles/webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/webserv.dir/srcs/parsing/config.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserv.dir/srcs/parsing/config.cpp.o -MF CMakeFiles/webserv.dir/srcs/parsing/config.cpp.o.d -o CMakeFiles/webserv.dir/srcs/parsing/config.cpp.o -c /Users/trgalyautdinov/webserv/srcs/parsing/config.cpp

CMakeFiles/webserv.dir/srcs/parsing/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/webserv.dir/srcs/parsing/config.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trgalyautdinov/webserv/srcs/parsing/config.cpp > CMakeFiles/webserv.dir/srcs/parsing/config.cpp.i

CMakeFiles/webserv.dir/srcs/parsing/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/webserv.dir/srcs/parsing/config.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trgalyautdinov/webserv/srcs/parsing/config.cpp -o CMakeFiles/webserv.dir/srcs/parsing/config.cpp.s

CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.o: CMakeFiles/webserv.dir/flags.make
CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.o: /Users/trgalyautdinov/webserv/srcs/request/RequestParsing.cpp
CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.o: CMakeFiles/webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.o -MF CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.o.d -o CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.o -c /Users/trgalyautdinov/webserv/srcs/request/RequestParsing.cpp

CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trgalyautdinov/webserv/srcs/request/RequestParsing.cpp > CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.i

CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trgalyautdinov/webserv/srcs/request/RequestParsing.cpp -o CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.s

CMakeFiles/webserv.dir/srcs/request/Request.cpp.o: CMakeFiles/webserv.dir/flags.make
CMakeFiles/webserv.dir/srcs/request/Request.cpp.o: /Users/trgalyautdinov/webserv/srcs/request/Request.cpp
CMakeFiles/webserv.dir/srcs/request/Request.cpp.o: CMakeFiles/webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/webserv.dir/srcs/request/Request.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserv.dir/srcs/request/Request.cpp.o -MF CMakeFiles/webserv.dir/srcs/request/Request.cpp.o.d -o CMakeFiles/webserv.dir/srcs/request/Request.cpp.o -c /Users/trgalyautdinov/webserv/srcs/request/Request.cpp

CMakeFiles/webserv.dir/srcs/request/Request.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/webserv.dir/srcs/request/Request.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trgalyautdinov/webserv/srcs/request/Request.cpp > CMakeFiles/webserv.dir/srcs/request/Request.cpp.i

CMakeFiles/webserv.dir/srcs/request/Request.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/webserv.dir/srcs/request/Request.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trgalyautdinov/webserv/srcs/request/Request.cpp -o CMakeFiles/webserv.dir/srcs/request/Request.cpp.s

CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.o: CMakeFiles/webserv.dir/flags.make
CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.o: /Users/trgalyautdinov/webserv/srcs/sockets/WebServer.cpp
CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.o: CMakeFiles/webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.o -MF CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.o.d -o CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.o -c /Users/trgalyautdinov/webserv/srcs/sockets/WebServer.cpp

CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trgalyautdinov/webserv/srcs/sockets/WebServer.cpp > CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.i

CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trgalyautdinov/webserv/srcs/sockets/WebServer.cpp -o CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.s

CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.o: CMakeFiles/webserv.dir/flags.make
CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.o: /Users/trgalyautdinov/webserv/srcs/sockets/SocketListener.cpp
CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.o: CMakeFiles/webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.o -MF CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.o.d -o CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.o -c /Users/trgalyautdinov/webserv/srcs/sockets/SocketListener.cpp

CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trgalyautdinov/webserv/srcs/sockets/SocketListener.cpp > CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.i

CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trgalyautdinov/webserv/srcs/sockets/SocketListener.cpp -o CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.s

CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.o: CMakeFiles/webserv.dir/flags.make
CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.o: /Users/trgalyautdinov/webserv/srcs/sockets/DataStorage.cpp
CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.o: CMakeFiles/webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.o -MF CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.o.d -o CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.o -c /Users/trgalyautdinov/webserv/srcs/sockets/DataStorage.cpp

CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trgalyautdinov/webserv/srcs/sockets/DataStorage.cpp > CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.i

CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trgalyautdinov/webserv/srcs/sockets/DataStorage.cpp -o CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.s

CMakeFiles/webserv.dir/srcs/Utils.cpp.o: CMakeFiles/webserv.dir/flags.make
CMakeFiles/webserv.dir/srcs/Utils.cpp.o: /Users/trgalyautdinov/webserv/srcs/Utils.cpp
CMakeFiles/webserv.dir/srcs/Utils.cpp.o: CMakeFiles/webserv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/webserv.dir/srcs/Utils.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/webserv.dir/srcs/Utils.cpp.o -MF CMakeFiles/webserv.dir/srcs/Utils.cpp.o.d -o CMakeFiles/webserv.dir/srcs/Utils.cpp.o -c /Users/trgalyautdinov/webserv/srcs/Utils.cpp

CMakeFiles/webserv.dir/srcs/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/webserv.dir/srcs/Utils.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/trgalyautdinov/webserv/srcs/Utils.cpp > CMakeFiles/webserv.dir/srcs/Utils.cpp.i

CMakeFiles/webserv.dir/srcs/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/webserv.dir/srcs/Utils.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/trgalyautdinov/webserv/srcs/Utils.cpp -o CMakeFiles/webserv.dir/srcs/Utils.cpp.s

# Object files for target webserv
webserv_OBJECTS = \
"CMakeFiles/webserv.dir/srcs/main.cpp.o" \
"CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.o" \
"CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.o" \
"CMakeFiles/webserv.dir/srcs/parsing/config.cpp.o" \
"CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.o" \
"CMakeFiles/webserv.dir/srcs/request/Request.cpp.o" \
"CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.o" \
"CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.o" \
"CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.o" \
"CMakeFiles/webserv.dir/srcs/Utils.cpp.o"

# External object files for target webserv
webserv_EXTERNAL_OBJECTS =

webserv: CMakeFiles/webserv.dir/srcs/main.cpp.o
webserv: CMakeFiles/webserv.dir/srcs/parsing/LocationBlock.cpp.o
webserv: CMakeFiles/webserv.dir/srcs/parsing/ServerBlock.cpp.o
webserv: CMakeFiles/webserv.dir/srcs/parsing/config.cpp.o
webserv: CMakeFiles/webserv.dir/srcs/request/RequestParsing.cpp.o
webserv: CMakeFiles/webserv.dir/srcs/request/Request.cpp.o
webserv: CMakeFiles/webserv.dir/srcs/sockets/WebServer.cpp.o
webserv: CMakeFiles/webserv.dir/srcs/sockets/SocketListener.cpp.o
webserv: CMakeFiles/webserv.dir/srcs/sockets/DataStorage.cpp.o
webserv: CMakeFiles/webserv.dir/srcs/Utils.cpp.o
webserv: CMakeFiles/webserv.dir/build.make
webserv: CMakeFiles/webserv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable webserv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/webserv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/webserv.dir/build: webserv
.PHONY : CMakeFiles/webserv.dir/build

CMakeFiles/webserv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/webserv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/webserv.dir/clean

CMakeFiles/webserv.dir/depend:
	cd /Users/trgalyautdinov/webserv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/trgalyautdinov/webserv /Users/trgalyautdinov/webserv /Users/trgalyautdinov/webserv/cmake-build-debug /Users/trgalyautdinov/webserv/cmake-build-debug /Users/trgalyautdinov/webserv/cmake-build-debug/CMakeFiles/webserv.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/webserv.dir/depend

