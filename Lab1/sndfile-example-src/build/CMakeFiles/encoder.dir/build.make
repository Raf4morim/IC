# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/lib/python3.8/dist-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /usr/local/lib/python3.8/dist-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build

# Include any dependencies generated for this target.
include CMakeFiles/encoder.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/encoder.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/encoder.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/encoder.dir/flags.make

CMakeFiles/encoder.dir/encoder.cpp.o: CMakeFiles/encoder.dir/flags.make
CMakeFiles/encoder.dir/encoder.cpp.o: /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/encoder.cpp
CMakeFiles/encoder.dir/encoder.cpp.o: CMakeFiles/encoder.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/encoder.dir/encoder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/encoder.dir/encoder.cpp.o -MF CMakeFiles/encoder.dir/encoder.cpp.o.d -o CMakeFiles/encoder.dir/encoder.cpp.o -c /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/encoder.cpp

CMakeFiles/encoder.dir/encoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encoder.dir/encoder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/encoder.cpp > CMakeFiles/encoder.dir/encoder.cpp.i

CMakeFiles/encoder.dir/encoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encoder.dir/encoder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/encoder.cpp -o CMakeFiles/encoder.dir/encoder.cpp.s

# Object files for target encoder
encoder_OBJECTS = \
"CMakeFiles/encoder.dir/encoder.cpp.o"

# External object files for target encoder
encoder_EXTERNAL_OBJECTS =

/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-bin/encoder: CMakeFiles/encoder.dir/encoder.cpp.o
/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-bin/encoder: CMakeFiles/encoder.dir/build.make
/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-bin/encoder: CMakeFiles/encoder.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-bin/encoder"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/encoder.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/encoder.dir/build: /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-bin/encoder
.PHONY : CMakeFiles/encoder.dir/build

CMakeFiles/encoder.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/encoder.dir/cmake_clean.cmake
.PHONY : CMakeFiles/encoder.dir/clean

CMakeFiles/encoder.dir/depend:
	cd /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build /mnt/c/Users/repol/Documents/GitHub/IC/Lab1/sndfile-example-src/build/CMakeFiles/encoder.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/encoder.dir/depend

