# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/wzq/crab_car/master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wzq/crab_car/master/build

# Include any dependencies generated for this target.
include CMakeFiles/crab.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/crab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/crab.dir/flags.make

CMakeFiles/crab.dir/src/main.cc.o: CMakeFiles/crab.dir/flags.make
CMakeFiles/crab.dir/src/main.cc.o: ../src/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wzq/crab_car/master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/crab.dir/src/main.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crab.dir/src/main.cc.o -c /home/wzq/crab_car/master/src/main.cc

CMakeFiles/crab.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crab.dir/src/main.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wzq/crab_car/master/src/main.cc > CMakeFiles/crab.dir/src/main.cc.i

CMakeFiles/crab.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crab.dir/src/main.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wzq/crab_car/master/src/main.cc -o CMakeFiles/crab.dir/src/main.cc.s

CMakeFiles/crab.dir/src/main.cc.o.requires:

.PHONY : CMakeFiles/crab.dir/src/main.cc.o.requires

CMakeFiles/crab.dir/src/main.cc.o.provides: CMakeFiles/crab.dir/src/main.cc.o.requires
	$(MAKE) -f CMakeFiles/crab.dir/build.make CMakeFiles/crab.dir/src/main.cc.o.provides.build
.PHONY : CMakeFiles/crab.dir/src/main.cc.o.provides

CMakeFiles/crab.dir/src/main.cc.o.provides.build: CMakeFiles/crab.dir/src/main.cc.o


# Object files for target crab
crab_OBJECTS = \
"CMakeFiles/crab.dir/src/main.cc.o"

# External object files for target crab
crab_EXTERNAL_OBJECTS =

crab: CMakeFiles/crab.dir/src/main.cc.o
crab: CMakeFiles/crab.dir/build.make
crab: libserial.so
crab: libdealy.so
crab: libthread.so
crab: librobot.so
crab: libkeyboard.so
crab: libcv.so
crab: CMakeFiles/crab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wzq/crab_car/master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable crab"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crab.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/crab.dir/build: crab

.PHONY : CMakeFiles/crab.dir/build

CMakeFiles/crab.dir/requires: CMakeFiles/crab.dir/src/main.cc.o.requires

.PHONY : CMakeFiles/crab.dir/requires

CMakeFiles/crab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/crab.dir/cmake_clean.cmake
.PHONY : CMakeFiles/crab.dir/clean

CMakeFiles/crab.dir/depend:
	cd /home/wzq/crab_car/master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wzq/crab_car/master /home/wzq/crab_car/master /home/wzq/crab_car/master/build /home/wzq/crab_car/master/build /home/wzq/crab_car/master/build/CMakeFiles/crab.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/crab.dir/depend

