# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = "/home/niklas/Desktop/LearnOpenGL/6_shaders task2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/niklas/Desktop/LearnOpenGL/6_shaders task2/build"

# Include any dependencies generated for this target.
include CMakeFiles/LearnOpenGL.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/LearnOpenGL.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LearnOpenGL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LearnOpenGL.dir/flags.make

CMakeFiles/LearnOpenGL.dir/source/main.cpp.o: CMakeFiles/LearnOpenGL.dir/flags.make
CMakeFiles/LearnOpenGL.dir/source/main.cpp.o: ../source/main.cpp
CMakeFiles/LearnOpenGL.dir/source/main.cpp.o: CMakeFiles/LearnOpenGL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/niklas/Desktop/LearnOpenGL/6_shaders task2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LearnOpenGL.dir/source/main.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LearnOpenGL.dir/source/main.cpp.o -MF CMakeFiles/LearnOpenGL.dir/source/main.cpp.o.d -o CMakeFiles/LearnOpenGL.dir/source/main.cpp.o -c "/home/niklas/Desktop/LearnOpenGL/6_shaders task2/source/main.cpp"

CMakeFiles/LearnOpenGL.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LearnOpenGL.dir/source/main.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/niklas/Desktop/LearnOpenGL/6_shaders task2/source/main.cpp" > CMakeFiles/LearnOpenGL.dir/source/main.cpp.i

CMakeFiles/LearnOpenGL.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LearnOpenGL.dir/source/main.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/niklas/Desktop/LearnOpenGL/6_shaders task2/source/main.cpp" -o CMakeFiles/LearnOpenGL.dir/source/main.cpp.s

# Object files for target LearnOpenGL
LearnOpenGL_OBJECTS = \
"CMakeFiles/LearnOpenGL.dir/source/main.cpp.o"

# External object files for target LearnOpenGL
LearnOpenGL_EXTERNAL_OBJECTS =

LearnOpenGL: CMakeFiles/LearnOpenGL.dir/source/main.cpp.o
LearnOpenGL: CMakeFiles/LearnOpenGL.dir/build.make
LearnOpenGL: libraries/glfw/src/libglfw3.a
LearnOpenGL: libglad.a
LearnOpenGL: /usr/lib64/librt.so
LearnOpenGL: /usr/lib64/libm.so
LearnOpenGL: /usr/lib64/libX11.so
LearnOpenGL: CMakeFiles/LearnOpenGL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/niklas/Desktop/LearnOpenGL/6_shaders task2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LearnOpenGL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LearnOpenGL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LearnOpenGL.dir/build: LearnOpenGL
.PHONY : CMakeFiles/LearnOpenGL.dir/build

CMakeFiles/LearnOpenGL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LearnOpenGL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LearnOpenGL.dir/clean

CMakeFiles/LearnOpenGL.dir/depend:
	cd "/home/niklas/Desktop/LearnOpenGL/6_shaders task2/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/niklas/Desktop/LearnOpenGL/6_shaders task2" "/home/niklas/Desktop/LearnOpenGL/6_shaders task2" "/home/niklas/Desktop/LearnOpenGL/6_shaders task2/build" "/home/niklas/Desktop/LearnOpenGL/6_shaders task2/build" "/home/niklas/Desktop/LearnOpenGL/6_shaders task2/build/CMakeFiles/LearnOpenGL.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/LearnOpenGL.dir/depend

