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
CMAKE_SOURCE_DIR = /home/zhzhou33_linux/codefile/c++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhzhou33_linux/codefile/c++/MyTinySTL

# Include any dependencies generated for this target.
include MyTinySTL/CMakeFiles/Project.dir/depend.make

# Include the progress variables for this target.
include MyTinySTL/CMakeFiles/Project.dir/progress.make

# Include the compile flags for this target's objects.
include MyTinySTL/CMakeFiles/Project.dir/flags.make

MyTinySTL/CMakeFiles/Project.dir/main.cpp.o: MyTinySTL/CMakeFiles/Project.dir/flags.make
MyTinySTL/CMakeFiles/Project.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhzhou33_linux/codefile/c++/MyTinySTL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object MyTinySTL/CMakeFiles/Project.dir/main.cpp.o"
	cd /home/zhzhou33_linux/codefile/c++/MyTinySTL/MyTinySTL && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/main.cpp.o -c /home/zhzhou33_linux/codefile/c++/MyTinySTL/main.cpp

MyTinySTL/CMakeFiles/Project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/main.cpp.i"
	cd /home/zhzhou33_linux/codefile/c++/MyTinySTL/MyTinySTL && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhzhou33_linux/codefile/c++/MyTinySTL/main.cpp > CMakeFiles/Project.dir/main.cpp.i

MyTinySTL/CMakeFiles/Project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/main.cpp.s"
	cd /home/zhzhou33_linux/codefile/c++/MyTinySTL/MyTinySTL && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhzhou33_linux/codefile/c++/MyTinySTL/main.cpp -o CMakeFiles/Project.dir/main.cpp.s

MyTinySTL/CMakeFiles/Project.dir/src/Alloc.cpp.o: MyTinySTL/CMakeFiles/Project.dir/flags.make
MyTinySTL/CMakeFiles/Project.dir/src/Alloc.cpp.o: src/Alloc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhzhou33_linux/codefile/c++/MyTinySTL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object MyTinySTL/CMakeFiles/Project.dir/src/Alloc.cpp.o"
	cd /home/zhzhou33_linux/codefile/c++/MyTinySTL/MyTinySTL && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/src/Alloc.cpp.o -c /home/zhzhou33_linux/codefile/c++/MyTinySTL/src/Alloc.cpp

MyTinySTL/CMakeFiles/Project.dir/src/Alloc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/src/Alloc.cpp.i"
	cd /home/zhzhou33_linux/codefile/c++/MyTinySTL/MyTinySTL && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhzhou33_linux/codefile/c++/MyTinySTL/src/Alloc.cpp > CMakeFiles/Project.dir/src/Alloc.cpp.i

MyTinySTL/CMakeFiles/Project.dir/src/Alloc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/src/Alloc.cpp.s"
	cd /home/zhzhou33_linux/codefile/c++/MyTinySTL/MyTinySTL && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhzhou33_linux/codefile/c++/MyTinySTL/src/Alloc.cpp -o CMakeFiles/Project.dir/src/Alloc.cpp.s

# Object files for target Project
Project_OBJECTS = \
"CMakeFiles/Project.dir/main.cpp.o" \
"CMakeFiles/Project.dir/src/Alloc.cpp.o"

# External object files for target Project
Project_EXTERNAL_OBJECTS =

MyTinySTL/Project: MyTinySTL/CMakeFiles/Project.dir/main.cpp.o
MyTinySTL/Project: MyTinySTL/CMakeFiles/Project.dir/src/Alloc.cpp.o
MyTinySTL/Project: MyTinySTL/CMakeFiles/Project.dir/build.make
MyTinySTL/Project: MyTinySTL/CMakeFiles/Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhzhou33_linux/codefile/c++/MyTinySTL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Project"
	cd /home/zhzhou33_linux/codefile/c++/MyTinySTL/MyTinySTL && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
MyTinySTL/CMakeFiles/Project.dir/build: MyTinySTL/Project

.PHONY : MyTinySTL/CMakeFiles/Project.dir/build

MyTinySTL/CMakeFiles/Project.dir/clean:
	cd /home/zhzhou33_linux/codefile/c++/MyTinySTL/MyTinySTL && $(CMAKE_COMMAND) -P CMakeFiles/Project.dir/cmake_clean.cmake
.PHONY : MyTinySTL/CMakeFiles/Project.dir/clean

MyTinySTL/CMakeFiles/Project.dir/depend:
	cd /home/zhzhou33_linux/codefile/c++/MyTinySTL && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhzhou33_linux/codefile/c++ /home/zhzhou33_linux/codefile/c++/MyTinySTL /home/zhzhou33_linux/codefile/c++/MyTinySTL /home/zhzhou33_linux/codefile/c++/MyTinySTL/MyTinySTL /home/zhzhou33_linux/codefile/c++/MyTinySTL/MyTinySTL/CMakeFiles/Project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : MyTinySTL/CMakeFiles/Project.dir/depend

