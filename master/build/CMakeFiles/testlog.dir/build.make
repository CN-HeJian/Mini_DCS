# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/icf/icf/CacheSystem/master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/icf/icf/CacheSystem/master/build

# Include any dependencies generated for this target.
include CMakeFiles/testlog.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testlog.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testlog.dir/flags.make

CMakeFiles/testlog.dir/test/test_log.cpp.o: CMakeFiles/testlog.dir/flags.make
CMakeFiles/testlog.dir/test/test_log.cpp.o: ../test/test_log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/icf/icf/CacheSystem/master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testlog.dir/test/test_log.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testlog.dir/test/test_log.cpp.o -c /home/icf/icf/CacheSystem/master/test/test_log.cpp

CMakeFiles/testlog.dir/test/test_log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testlog.dir/test/test_log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/icf/icf/CacheSystem/master/test/test_log.cpp > CMakeFiles/testlog.dir/test/test_log.cpp.i

CMakeFiles/testlog.dir/test/test_log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testlog.dir/test/test_log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/icf/icf/CacheSystem/master/test/test_log.cpp -o CMakeFiles/testlog.dir/test/test_log.cpp.s

CMakeFiles/testlog.dir/common/log.cpp.o: CMakeFiles/testlog.dir/flags.make
CMakeFiles/testlog.dir/common/log.cpp.o: ../common/log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/icf/icf/CacheSystem/master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testlog.dir/common/log.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testlog.dir/common/log.cpp.o -c /home/icf/icf/CacheSystem/master/common/log.cpp

CMakeFiles/testlog.dir/common/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testlog.dir/common/log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/icf/icf/CacheSystem/master/common/log.cpp > CMakeFiles/testlog.dir/common/log.cpp.i

CMakeFiles/testlog.dir/common/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testlog.dir/common/log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/icf/icf/CacheSystem/master/common/log.cpp -o CMakeFiles/testlog.dir/common/log.cpp.s

# Object files for target testlog
testlog_OBJECTS = \
"CMakeFiles/testlog.dir/test/test_log.cpp.o" \
"CMakeFiles/testlog.dir/common/log.cpp.o"

# External object files for target testlog
testlog_EXTERNAL_OBJECTS =

testlog: CMakeFiles/testlog.dir/test/test_log.cpp.o
testlog: CMakeFiles/testlog.dir/common/log.cpp.o
testlog: CMakeFiles/testlog.dir/build.make
testlog: CMakeFiles/testlog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/icf/icf/CacheSystem/master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable testlog"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testlog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testlog.dir/build: testlog

.PHONY : CMakeFiles/testlog.dir/build

CMakeFiles/testlog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testlog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testlog.dir/clean

CMakeFiles/testlog.dir/depend:
	cd /home/icf/icf/CacheSystem/master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/icf/icf/CacheSystem/master /home/icf/icf/CacheSystem/master /home/icf/icf/CacheSystem/master/build /home/icf/icf/CacheSystem/master/build /home/icf/icf/CacheSystem/master/build/CMakeFiles/testlog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testlog.dir/depend
