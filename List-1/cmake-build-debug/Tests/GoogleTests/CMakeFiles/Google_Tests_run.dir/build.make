# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /home/adrianczubaty/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/adrianczubaty/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adrianczubaty/Documents/Programming-Languages/List-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug

# Include any dependencies generated for this target.
include Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/compiler_depend.make

# Include the progress variables for this target.
include Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/progress.make

# Include the compile flags for this target's objects.
include Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/flags.make

Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/test1.cpp.o: Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/flags.make
Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/test1.cpp.o: /home/adrianczubaty/Documents/Programming-Languages/List-1/Tests/GoogleTests/test1.cpp
Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/test1.cpp.o: Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/test1.cpp.o"
	cd /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/Tests/GoogleTests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/test1.cpp.o -MF CMakeFiles/Google_Tests_run.dir/test1.cpp.o.d -o CMakeFiles/Google_Tests_run.dir/test1.cpp.o -c /home/adrianczubaty/Documents/Programming-Languages/List-1/Tests/GoogleTests/test1.cpp

Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/test1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Google_Tests_run.dir/test1.cpp.i"
	cd /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/Tests/GoogleTests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adrianczubaty/Documents/Programming-Languages/List-1/Tests/GoogleTests/test1.cpp > CMakeFiles/Google_Tests_run.dir/test1.cpp.i

Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/test1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Google_Tests_run.dir/test1.cpp.s"
	cd /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/Tests/GoogleTests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adrianczubaty/Documents/Programming-Languages/List-1/Tests/GoogleTests/test1.cpp -o CMakeFiles/Google_Tests_run.dir/test1.cpp.s

# Object files for target Google_Tests_run
Google_Tests_run_OBJECTS = \
"CMakeFiles/Google_Tests_run.dir/test1.cpp.o"

# External object files for target Google_Tests_run
Google_Tests_run_EXTERNAL_OBJECTS =

Tests/GoogleTests/Google_Tests_run: Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/test1.cpp.o
Tests/GoogleTests/Google_Tests_run: Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/build.make
Tests/GoogleTests/Google_Tests_run: lib/libgtest.a
Tests/GoogleTests/Google_Tests_run: lib/libgtest_main.a
Tests/GoogleTests/Google_Tests_run: lib/libgtest.a
Tests/GoogleTests/Google_Tests_run: Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Google_Tests_run"
	cd /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/Tests/GoogleTests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Google_Tests_run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/build: Tests/GoogleTests/Google_Tests_run
.PHONY : Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/build

Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/clean:
	cd /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/Tests/GoogleTests && $(CMAKE_COMMAND) -P CMakeFiles/Google_Tests_run.dir/cmake_clean.cmake
.PHONY : Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/clean

Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/depend:
	cd /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adrianczubaty/Documents/Programming-Languages/List-1 /home/adrianczubaty/Documents/Programming-Languages/List-1/Tests/GoogleTests /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/Tests/GoogleTests /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Tests/GoogleTests/CMakeFiles/Google_Tests_run.dir/depend

