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
include CMakeFiles/semaphore.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/semaphore.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/semaphore.dir/flags.make

CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.o: CMakeFiles/semaphore.dir/flags.make
CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.o: ../src/thread_test/thread_semaphore_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.dFz6Z7OdDc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.o   -c /tmp/tmp.dFz6Z7OdDc/src/thread_test/thread_semaphore_test.c

CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/tmp.dFz6Z7OdDc/src/thread_test/thread_semaphore_test.c > CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.i

CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/tmp.dFz6Z7OdDc/src/thread_test/thread_semaphore_test.c -o CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.s

# Object files for target semaphore
semaphore_OBJECTS = \
"CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.o"

# External object files for target semaphore
semaphore_EXTERNAL_OBJECTS =

semaphore: CMakeFiles/semaphore.dir/src/thread_test/thread_semaphore_test.c.o
semaphore: CMakeFiles/semaphore.dir/build.make
semaphore: CMakeFiles/semaphore.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.dFz6Z7OdDc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable semaphore"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/semaphore.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/semaphore.dir/build: semaphore

.PHONY : CMakeFiles/semaphore.dir/build

CMakeFiles/semaphore.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/semaphore.dir/cmake_clean.cmake
.PHONY : CMakeFiles/semaphore.dir/clean

CMakeFiles/semaphore.dir/depend:
	cd /tmp/tmp.dFz6Z7OdDc/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.dFz6Z7OdDc /tmp/tmp.dFz6Z7OdDc /tmp/tmp.dFz6Z7OdDc/cmake-build-debug /tmp/tmp.dFz6Z7OdDc/cmake-build-debug /tmp/tmp.dFz6Z7OdDc/cmake-build-debug/CMakeFiles/semaphore.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/semaphore.dir/depend

