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
CMAKE_SOURCE_DIR = /workspaces/cs225env/.devcontainer/release-f22/lab_debug

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/cs225env/.devcontainer/release-f22/lab_debug/build

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/tests/tests.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/tests/tests.cpp.o: ../tests/tests.cpp
CMakeFiles/test.dir/tests/tests.cpp.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cs225env/.devcontainer/release-f22/lab_debug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.dir/tests/tests.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/tests/tests.cpp.o -MF CMakeFiles/test.dir/tests/tests.cpp.o.d -o CMakeFiles/test.dir/tests/tests.cpp.o -c /workspaces/cs225env/.devcontainer/release-f22/lab_debug/tests/tests.cpp

CMakeFiles/test.dir/tests/tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/tests/tests.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cs225env/.devcontainer/release-f22/lab_debug/tests/tests.cpp > CMakeFiles/test.dir/tests/tests.cpp.i

CMakeFiles/test.dir/tests/tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/tests/tests.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cs225env/.devcontainer/release-f22/lab_debug/tests/tests.cpp -o CMakeFiles/test.dir/tests/tests.cpp.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/tests/tests.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

test: CMakeFiles/test.dir/tests/tests.cpp.o
test: CMakeFiles/test.dir/build.make
test: /usr/lib/libCatch2Main.a
test: src/libsrc.a
test: /usr/lib/libCatch2.a
test: lib/libcs225.a
test: lib/liblodepng.a
test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/cs225env/.devcontainer/release-f22/lab_debug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=test -D TEST_EXECUTABLE=/workspaces/cs225env/.devcontainer/release-f22/lab_debug/build/test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/workspaces/cs225env/.devcontainer/release-f22/lab_debug/build -D TEST_SPEC= -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_LIST=test_TESTS -D TEST_REPORTER= -D TEST_OUTPUT_DIR= -D TEST_OUTPUT_PREFIX= -D TEST_OUTPUT_SUFFIX= -D TEST_DL_PATHS= -D CTEST_FILE=/workspaces/cs225env/.devcontainer/release-f22/lab_debug/build/test_tests-b12d07c.cmake -P /usr/lib/cmake/Catch2/CatchAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test
.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /workspaces/cs225env/.devcontainer/release-f22/lab_debug/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/cs225env/.devcontainer/release-f22/lab_debug /workspaces/cs225env/.devcontainer/release-f22/lab_debug /workspaces/cs225env/.devcontainer/release-f22/lab_debug/build /workspaces/cs225env/.devcontainer/release-f22/lab_debug/build /workspaces/cs225env/.devcontainer/release-f22/lab_debug/build/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

