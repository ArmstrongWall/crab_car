# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/wang/crab/master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wang/crab/master/build

# Include any dependencies generated for this target.
include CMakeFiles/crab.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/crab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/crab.dir/flags.make

CMakeFiles/crab.dir/src/main.c.o: CMakeFiles/crab.dir/flags.make
CMakeFiles/crab.dir/src/main.c.o: ../src/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/wang/crab/master/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/crab.dir/src/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/crab.dir/src/main.c.o   -c /home/wang/crab/master/src/main.c

CMakeFiles/crab.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/crab.dir/src/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/wang/crab/master/src/main.c > CMakeFiles/crab.dir/src/main.c.i

CMakeFiles/crab.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/crab.dir/src/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/wang/crab/master/src/main.c -o CMakeFiles/crab.dir/src/main.c.s

CMakeFiles/crab.dir/src/main.c.o.requires:
.PHONY : CMakeFiles/crab.dir/src/main.c.o.requires

CMakeFiles/crab.dir/src/main.c.o.provides: CMakeFiles/crab.dir/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/crab.dir/build.make CMakeFiles/crab.dir/src/main.c.o.provides.build
.PHONY : CMakeFiles/crab.dir/src/main.c.o.provides

CMakeFiles/crab.dir/src/main.c.o.provides.build: CMakeFiles/crab.dir/src/main.c.o

# Object files for target crab
crab_OBJECTS = \
"CMakeFiles/crab.dir/src/main.c.o"

# External object files for target crab
crab_EXTERNAL_OBJECTS =

crab: CMakeFiles/crab.dir/src/main.c.o
crab: CMakeFiles/crab.dir/build.make
crab: libserial.so
crab: CMakeFiles/crab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable crab"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crab.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/crab.dir/build: crab
.PHONY : CMakeFiles/crab.dir/build

CMakeFiles/crab.dir/requires: CMakeFiles/crab.dir/src/main.c.o.requires
.PHONY : CMakeFiles/crab.dir/requires

CMakeFiles/crab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/crab.dir/cmake_clean.cmake
.PHONY : CMakeFiles/crab.dir/clean

CMakeFiles/crab.dir/depend:
	cd /home/wang/crab/master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wang/crab/master /home/wang/crab/master /home/wang/crab/master/build /home/wang/crab/master/build /home/wang/crab/master/build/CMakeFiles/crab.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/crab.dir/depend

