# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/dev/foundation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/dev/foundation/cmake-build-release

# Include any dependencies generated for this target.
include cpp/pmr/CMakeFiles/pmr_05.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include cpp/pmr/CMakeFiles/pmr_05.dir/compiler_depend.make

# Include the progress variables for this target.
include cpp/pmr/CMakeFiles/pmr_05.dir/progress.make

# Include the compile flags for this target's objects.
include cpp/pmr/CMakeFiles/pmr_05.dir/flags.make

cpp/pmr/CMakeFiles/pmr_05.dir/pmr_05.cpp.o: cpp/pmr/CMakeFiles/pmr_05.dir/flags.make
cpp/pmr/CMakeFiles/pmr_05.dir/pmr_05.cpp.o: ../cpp/pmr/pmr_05.cpp
cpp/pmr/CMakeFiles/pmr_05.dir/pmr_05.cpp.o: cpp/pmr/CMakeFiles/pmr_05.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/dev/foundation/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cpp/pmr/CMakeFiles/pmr_05.dir/pmr_05.cpp.o"
	cd /home/ubuntu/dev/foundation/cmake-build-release/cpp/pmr && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT cpp/pmr/CMakeFiles/pmr_05.dir/pmr_05.cpp.o -MF CMakeFiles/pmr_05.dir/pmr_05.cpp.o.d -o CMakeFiles/pmr_05.dir/pmr_05.cpp.o -c /home/ubuntu/dev/foundation/cpp/pmr/pmr_05.cpp

cpp/pmr/CMakeFiles/pmr_05.dir/pmr_05.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pmr_05.dir/pmr_05.cpp.i"
	cd /home/ubuntu/dev/foundation/cmake-build-release/cpp/pmr && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/dev/foundation/cpp/pmr/pmr_05.cpp > CMakeFiles/pmr_05.dir/pmr_05.cpp.i

cpp/pmr/CMakeFiles/pmr_05.dir/pmr_05.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pmr_05.dir/pmr_05.cpp.s"
	cd /home/ubuntu/dev/foundation/cmake-build-release/cpp/pmr && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/dev/foundation/cpp/pmr/pmr_05.cpp -o CMakeFiles/pmr_05.dir/pmr_05.cpp.s

# Object files for target pmr_05
pmr_05_OBJECTS = \
"CMakeFiles/pmr_05.dir/pmr_05.cpp.o"

# External object files for target pmr_05
pmr_05_EXTERNAL_OBJECTS =

cpp/pmr/pmr_05: cpp/pmr/CMakeFiles/pmr_05.dir/pmr_05.cpp.o
cpp/pmr/pmr_05: cpp/pmr/CMakeFiles/pmr_05.dir/build.make
cpp/pmr/pmr_05: cpp/pmr/CMakeFiles/pmr_05.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/dev/foundation/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pmr_05"
	cd /home/ubuntu/dev/foundation/cmake-build-release/cpp/pmr && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pmr_05.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cpp/pmr/CMakeFiles/pmr_05.dir/build: cpp/pmr/pmr_05
.PHONY : cpp/pmr/CMakeFiles/pmr_05.dir/build

cpp/pmr/CMakeFiles/pmr_05.dir/clean:
	cd /home/ubuntu/dev/foundation/cmake-build-release/cpp/pmr && $(CMAKE_COMMAND) -P CMakeFiles/pmr_05.dir/cmake_clean.cmake
.PHONY : cpp/pmr/CMakeFiles/pmr_05.dir/clean

cpp/pmr/CMakeFiles/pmr_05.dir/depend:
	cd /home/ubuntu/dev/foundation/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/dev/foundation /home/ubuntu/dev/foundation/cpp/pmr /home/ubuntu/dev/foundation/cmake-build-release /home/ubuntu/dev/foundation/cmake-build-release/cpp/pmr /home/ubuntu/dev/foundation/cmake-build-release/cpp/pmr/CMakeFiles/pmr_05.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cpp/pmr/CMakeFiles/pmr_05.dir/depend

