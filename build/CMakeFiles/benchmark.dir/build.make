# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/enrico/Scrivania/git/CC-SAT-solver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/enrico/Scrivania/git/CC-SAT-solver/build

# Include any dependencies generated for this target.
include CMakeFiles/benchmark.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/benchmark.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/benchmark.dir/flags.make

CMakeFiles/benchmark.dir/src/benchmark.cpp.o: CMakeFiles/benchmark.dir/flags.make
CMakeFiles/benchmark.dir/src/benchmark.cpp.o: ../src/benchmark.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/enrico/Scrivania/git/CC-SAT-solver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/benchmark.dir/src/benchmark.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark.dir/src/benchmark.cpp.o -c /home/enrico/Scrivania/git/CC-SAT-solver/src/benchmark.cpp

CMakeFiles/benchmark.dir/src/benchmark.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark.dir/src/benchmark.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/enrico/Scrivania/git/CC-SAT-solver/src/benchmark.cpp > CMakeFiles/benchmark.dir/src/benchmark.cpp.i

CMakeFiles/benchmark.dir/src/benchmark.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark.dir/src/benchmark.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/enrico/Scrivania/git/CC-SAT-solver/src/benchmark.cpp -o CMakeFiles/benchmark.dir/src/benchmark.cpp.s

# Object files for target benchmark
benchmark_OBJECTS = \
"CMakeFiles/benchmark.dir/src/benchmark.cpp.o"

# External object files for target benchmark
benchmark_EXTERNAL_OBJECTS =

benchmark: CMakeFiles/benchmark.dir/src/benchmark.cpp.o
benchmark: CMakeFiles/benchmark.dir/build.make
benchmark: CMakeFiles/benchmark.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/enrico/Scrivania/git/CC-SAT-solver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable benchmark"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/benchmark.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/benchmark.dir/build: benchmark

.PHONY : CMakeFiles/benchmark.dir/build

CMakeFiles/benchmark.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/benchmark.dir/cmake_clean.cmake
.PHONY : CMakeFiles/benchmark.dir/clean

CMakeFiles/benchmark.dir/depend:
	cd /home/enrico/Scrivania/git/CC-SAT-solver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/enrico/Scrivania/git/CC-SAT-solver /home/enrico/Scrivania/git/CC-SAT-solver /home/enrico/Scrivania/git/CC-SAT-solver/build /home/enrico/Scrivania/git/CC-SAT-solver/build /home/enrico/Scrivania/git/CC-SAT-solver/build/CMakeFiles/benchmark.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/benchmark.dir/depend

