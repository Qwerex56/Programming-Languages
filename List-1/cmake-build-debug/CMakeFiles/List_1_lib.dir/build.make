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
include CMakeFiles/List_1_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/List_1_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/List_1_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/List_1_lib.dir/flags.make

CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.o: CMakeFiles/List_1_lib.dir/flags.make
CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.o: /home/adrianczubaty/Documents/Programming-Languages/List-1/NthBaseCalculatorLib/src/NthBaseNumber.cpp
CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.o: CMakeFiles/List_1_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.o -MF CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.o.d -o CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.o -c /home/adrianczubaty/Documents/Programming-Languages/List-1/NthBaseCalculatorLib/src/NthBaseNumber.cpp

CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adrianczubaty/Documents/Programming-Languages/List-1/NthBaseCalculatorLib/src/NthBaseNumber.cpp > CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.i

CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adrianczubaty/Documents/Programming-Languages/List-1/NthBaseCalculatorLib/src/NthBaseNumber.cpp -o CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.s

# Object files for target List_1_lib
List_1_lib_OBJECTS = \
"CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.o"

# External object files for target List_1_lib
List_1_lib_EXTERNAL_OBJECTS =

libList_1_lib.a: CMakeFiles/List_1_lib.dir/NthBaseCalculatorLib/src/NthBaseNumber.cpp.o
libList_1_lib.a: CMakeFiles/List_1_lib.dir/build.make
libList_1_lib.a: CMakeFiles/List_1_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libList_1_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/List_1_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/List_1_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/List_1_lib.dir/build: libList_1_lib.a
.PHONY : CMakeFiles/List_1_lib.dir/build

CMakeFiles/List_1_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/List_1_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/List_1_lib.dir/clean

CMakeFiles/List_1_lib.dir/depend:
	cd /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adrianczubaty/Documents/Programming-Languages/List-1 /home/adrianczubaty/Documents/Programming-Languages/List-1 /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug /home/adrianczubaty/Documents/Programming-Languages/List-1/cmake-build-debug/CMakeFiles/List_1_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/List_1_lib.dir/depend

