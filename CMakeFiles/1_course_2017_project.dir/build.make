# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.8.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.8.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/georgekobelev/KPIcourses/1_course_2017_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/georgekobelev/KPIcourses/1_course_2017_project

# Include any dependencies generated for this target.
include CMakeFiles/1_course_2017_project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/1_course_2017_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1_course_2017_project.dir/flags.make

CMakeFiles/1_course_2017_project.dir/main.cpp.o: CMakeFiles/1_course_2017_project.dir/flags.make
CMakeFiles/1_course_2017_project.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/georgekobelev/KPIcourses/1_course_2017_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1_course_2017_project.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/1_course_2017_project.dir/main.cpp.o -c /Users/georgekobelev/KPIcourses/1_course_2017_project/main.cpp

CMakeFiles/1_course_2017_project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1_course_2017_project.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/georgekobelev/KPIcourses/1_course_2017_project/main.cpp > CMakeFiles/1_course_2017_project.dir/main.cpp.i

CMakeFiles/1_course_2017_project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1_course_2017_project.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/georgekobelev/KPIcourses/1_course_2017_project/main.cpp -o CMakeFiles/1_course_2017_project.dir/main.cpp.s

CMakeFiles/1_course_2017_project.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/1_course_2017_project.dir/main.cpp.o.requires

CMakeFiles/1_course_2017_project.dir/main.cpp.o.provides: CMakeFiles/1_course_2017_project.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/1_course_2017_project.dir/build.make CMakeFiles/1_course_2017_project.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/1_course_2017_project.dir/main.cpp.o.provides

CMakeFiles/1_course_2017_project.dir/main.cpp.o.provides.build: CMakeFiles/1_course_2017_project.dir/main.cpp.o


CMakeFiles/1_course_2017_project.dir/src/render.c.o: CMakeFiles/1_course_2017_project.dir/flags.make
CMakeFiles/1_course_2017_project.dir/src/render.c.o: src/render.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/georgekobelev/KPIcourses/1_course_2017_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/1_course_2017_project.dir/src/render.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/1_course_2017_project.dir/src/render.c.o   -c /Users/georgekobelev/KPIcourses/1_course_2017_project/src/render.c

CMakeFiles/1_course_2017_project.dir/src/render.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/1_course_2017_project.dir/src/render.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/georgekobelev/KPIcourses/1_course_2017_project/src/render.c > CMakeFiles/1_course_2017_project.dir/src/render.c.i

CMakeFiles/1_course_2017_project.dir/src/render.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/1_course_2017_project.dir/src/render.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/georgekobelev/KPIcourses/1_course_2017_project/src/render.c -o CMakeFiles/1_course_2017_project.dir/src/render.c.s

CMakeFiles/1_course_2017_project.dir/src/render.c.o.requires:

.PHONY : CMakeFiles/1_course_2017_project.dir/src/render.c.o.requires

CMakeFiles/1_course_2017_project.dir/src/render.c.o.provides: CMakeFiles/1_course_2017_project.dir/src/render.c.o.requires
	$(MAKE) -f CMakeFiles/1_course_2017_project.dir/build.make CMakeFiles/1_course_2017_project.dir/src/render.c.o.provides.build
.PHONY : CMakeFiles/1_course_2017_project.dir/src/render.c.o.provides

CMakeFiles/1_course_2017_project.dir/src/render.c.o.provides.build: CMakeFiles/1_course_2017_project.dir/src/render.c.o


CMakeFiles/1_course_2017_project.dir/tests/main.c.o: CMakeFiles/1_course_2017_project.dir/flags.make
CMakeFiles/1_course_2017_project.dir/tests/main.c.o: tests/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/georgekobelev/KPIcourses/1_course_2017_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/1_course_2017_project.dir/tests/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/1_course_2017_project.dir/tests/main.c.o   -c /Users/georgekobelev/KPIcourses/1_course_2017_project/tests/main.c

CMakeFiles/1_course_2017_project.dir/tests/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/1_course_2017_project.dir/tests/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/georgekobelev/KPIcourses/1_course_2017_project/tests/main.c > CMakeFiles/1_course_2017_project.dir/tests/main.c.i

CMakeFiles/1_course_2017_project.dir/tests/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/1_course_2017_project.dir/tests/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/georgekobelev/KPIcourses/1_course_2017_project/tests/main.c -o CMakeFiles/1_course_2017_project.dir/tests/main.c.s

CMakeFiles/1_course_2017_project.dir/tests/main.c.o.requires:

.PHONY : CMakeFiles/1_course_2017_project.dir/tests/main.c.o.requires

CMakeFiles/1_course_2017_project.dir/tests/main.c.o.provides: CMakeFiles/1_course_2017_project.dir/tests/main.c.o.requires
	$(MAKE) -f CMakeFiles/1_course_2017_project.dir/build.make CMakeFiles/1_course_2017_project.dir/tests/main.c.o.provides.build
.PHONY : CMakeFiles/1_course_2017_project.dir/tests/main.c.o.provides

CMakeFiles/1_course_2017_project.dir/tests/main.c.o.provides.build: CMakeFiles/1_course_2017_project.dir/tests/main.c.o


# Object files for target 1_course_2017_project
1_course_2017_project_OBJECTS = \
"CMakeFiles/1_course_2017_project.dir/main.cpp.o" \
"CMakeFiles/1_course_2017_project.dir/src/render.c.o" \
"CMakeFiles/1_course_2017_project.dir/tests/main.c.o"

# External object files for target 1_course_2017_project
1_course_2017_project_EXTERNAL_OBJECTS =

1_course_2017_project: CMakeFiles/1_course_2017_project.dir/main.cpp.o
1_course_2017_project: CMakeFiles/1_course_2017_project.dir/src/render.c.o
1_course_2017_project: CMakeFiles/1_course_2017_project.dir/tests/main.c.o
1_course_2017_project: CMakeFiles/1_course_2017_project.dir/build.make
1_course_2017_project: CMakeFiles/1_course_2017_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/georgekobelev/KPIcourses/1_course_2017_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable 1_course_2017_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1_course_2017_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1_course_2017_project.dir/build: 1_course_2017_project

.PHONY : CMakeFiles/1_course_2017_project.dir/build

CMakeFiles/1_course_2017_project.dir/requires: CMakeFiles/1_course_2017_project.dir/main.cpp.o.requires
CMakeFiles/1_course_2017_project.dir/requires: CMakeFiles/1_course_2017_project.dir/src/render.c.o.requires
CMakeFiles/1_course_2017_project.dir/requires: CMakeFiles/1_course_2017_project.dir/tests/main.c.o.requires

.PHONY : CMakeFiles/1_course_2017_project.dir/requires

CMakeFiles/1_course_2017_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1_course_2017_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1_course_2017_project.dir/clean

CMakeFiles/1_course_2017_project.dir/depend:
	cd /Users/georgekobelev/KPIcourses/1_course_2017_project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/georgekobelev/KPIcourses/1_course_2017_project /Users/georgekobelev/KPIcourses/1_course_2017_project /Users/georgekobelev/KPIcourses/1_course_2017_project /Users/georgekobelev/KPIcourses/1_course_2017_project /Users/georgekobelev/KPIcourses/1_course_2017_project/CMakeFiles/1_course_2017_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/1_course_2017_project.dir/depend

