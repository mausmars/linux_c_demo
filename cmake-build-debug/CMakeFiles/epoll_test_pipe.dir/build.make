# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_SOURCE_DIR = /tmp/tmp.dFz6Z7OdDc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.dFz6Z7OdDc/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/epoll_test_pipe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/epoll_test_pipe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/epoll_test_pipe.dir/flags.make

CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.o: CMakeFiles/epoll_test_pipe.dir/flags.make
CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.o: ../src/epoll_test/epoll_test_pipe.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.dFz6Z7OdDc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.o   -c /tmp/tmp.dFz6Z7OdDc/src/epoll_test/epoll_test_pipe.c

CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.dFz6Z7OdDc/src/epoll_test/epoll_test_pipe.c > CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.i

CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.dFz6Z7OdDc/src/epoll_test/epoll_test_pipe.c -o CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.s

# Object files for target epoll_test_pipe
epoll_test_pipe_OBJECTS = \
"CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.o"

# External object files for target epoll_test_pipe
epoll_test_pipe_EXTERNAL_OBJECTS =

epoll_test_pipe: CMakeFiles/epoll_test_pipe.dir/src/epoll_test/epoll_test_pipe.c.o
epoll_test_pipe: CMakeFiles/epoll_test_pipe.dir/build.make
epoll_test_pipe: CMakeFiles/epoll_test_pipe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.dFz6Z7OdDc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable epoll_test_pipe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/epoll_test_pipe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/epoll_test_pipe.dir/build: epoll_test_pipe

.PHONY : CMakeFiles/epoll_test_pipe.dir/build

CMakeFiles/epoll_test_pipe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/epoll_test_pipe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/epoll_test_pipe.dir/clean

CMakeFiles/epoll_test_pipe.dir/depend:
	cd /tmp/tmp.dFz6Z7OdDc/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.dFz6Z7OdDc /tmp/tmp.dFz6Z7OdDc /tmp/tmp.dFz6Z7OdDc/cmake-build-debug /tmp/tmp.dFz6Z7OdDc/cmake-build-debug /tmp/tmp.dFz6Z7OdDc/cmake-build-debug/CMakeFiles/epoll_test_pipe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/epoll_test_pipe.dir/depend

