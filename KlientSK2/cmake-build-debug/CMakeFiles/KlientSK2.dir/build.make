# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/matt/Desktop/clion-2019.1.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/matt/Desktop/clion-2019.1.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/matt/CLionProjects/KlientSK2/KlientSK2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matt/CLionProjects/KlientSK2/KlientSK2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/KlientSK2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/KlientSK2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/KlientSK2.dir/flags.make

CMakeFiles/KlientSK2.dir/main.cpp.o: CMakeFiles/KlientSK2.dir/flags.make
CMakeFiles/KlientSK2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matt/CLionProjects/KlientSK2/KlientSK2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/KlientSK2.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KlientSK2.dir/main.cpp.o -c /home/matt/CLionProjects/KlientSK2/KlientSK2/main.cpp

CMakeFiles/KlientSK2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KlientSK2.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matt/CLionProjects/KlientSK2/KlientSK2/main.cpp > CMakeFiles/KlientSK2.dir/main.cpp.i

CMakeFiles/KlientSK2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KlientSK2.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matt/CLionProjects/KlientSK2/KlientSK2/main.cpp -o CMakeFiles/KlientSK2.dir/main.cpp.s

# Object files for target KlientSK2
KlientSK2_OBJECTS = \
"CMakeFiles/KlientSK2.dir/main.cpp.o"

# External object files for target KlientSK2
KlientSK2_EXTERNAL_OBJECTS =

KlientSK2: CMakeFiles/KlientSK2.dir/main.cpp.o
KlientSK2: CMakeFiles/KlientSK2.dir/build.make
KlientSK2: CMakeFiles/KlientSK2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matt/CLionProjects/KlientSK2/KlientSK2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable KlientSK2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KlientSK2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/KlientSK2.dir/build: KlientSK2

.PHONY : CMakeFiles/KlientSK2.dir/build

CMakeFiles/KlientSK2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/KlientSK2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/KlientSK2.dir/clean

CMakeFiles/KlientSK2.dir/depend:
	cd /home/matt/CLionProjects/KlientSK2/KlientSK2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matt/CLionProjects/KlientSK2/KlientSK2 /home/matt/CLionProjects/KlientSK2/KlientSK2 /home/matt/CLionProjects/KlientSK2/KlientSK2/cmake-build-debug /home/matt/CLionProjects/KlientSK2/KlientSK2/cmake-build-debug /home/matt/CLionProjects/KlientSK2/KlientSK2/cmake-build-debug/CMakeFiles/KlientSK2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/KlientSK2.dir/depend

