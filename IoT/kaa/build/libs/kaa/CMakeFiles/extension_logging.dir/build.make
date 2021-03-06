# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /home/pi/kaa

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/kaa/build

# Include any dependencies generated for this target.
include libs/kaa/CMakeFiles/extension_logging.dir/depend.make

# Include the progress variables for this target.
include libs/kaa/CMakeFiles/extension_logging.dir/progress.make

# Include the compile flags for this target's objects.
include libs/kaa/CMakeFiles/extension_logging.dir/flags.make

libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o: libs/kaa/CMakeFiles/extension_logging.dir/flags.make
libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o: ../libs/kaa/src/extensions/logging/kaa_logging.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/kaa/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o"
	cd /home/pi/kaa/build/libs/kaa && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o   -c /home/pi/kaa/libs/kaa/src/extensions/logging/kaa_logging.c

libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.i"
	cd /home/pi/kaa/build/libs/kaa && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/kaa/libs/kaa/src/extensions/logging/kaa_logging.c > CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.i

libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.s"
	cd /home/pi/kaa/build/libs/kaa && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/kaa/libs/kaa/src/extensions/logging/kaa_logging.c -o CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.s

libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o.requires:

.PHONY : libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o.requires

libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o.provides: libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o.requires
	$(MAKE) -f libs/kaa/CMakeFiles/extension_logging.dir/build.make libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o.provides.build
.PHONY : libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o.provides

libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o.provides.build: libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o


# Object files for target extension_logging
extension_logging_OBJECTS = \
"CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o"

# External object files for target extension_logging
extension_logging_EXTERNAL_OBJECTS =

libs/kaa/libextension_logging.a: libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o
libs/kaa/libextension_logging.a: libs/kaa/CMakeFiles/extension_logging.dir/build.make
libs/kaa/libextension_logging.a: libs/kaa/CMakeFiles/extension_logging.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/kaa/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libextension_logging.a"
	cd /home/pi/kaa/build/libs/kaa && $(CMAKE_COMMAND) -P CMakeFiles/extension_logging.dir/cmake_clean_target.cmake
	cd /home/pi/kaa/build/libs/kaa && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/extension_logging.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/kaa/CMakeFiles/extension_logging.dir/build: libs/kaa/libextension_logging.a

.PHONY : libs/kaa/CMakeFiles/extension_logging.dir/build

libs/kaa/CMakeFiles/extension_logging.dir/requires: libs/kaa/CMakeFiles/extension_logging.dir/src/extensions/logging/kaa_logging.c.o.requires

.PHONY : libs/kaa/CMakeFiles/extension_logging.dir/requires

libs/kaa/CMakeFiles/extension_logging.dir/clean:
	cd /home/pi/kaa/build/libs/kaa && $(CMAKE_COMMAND) -P CMakeFiles/extension_logging.dir/cmake_clean.cmake
.PHONY : libs/kaa/CMakeFiles/extension_logging.dir/clean

libs/kaa/CMakeFiles/extension_logging.dir/depend:
	cd /home/pi/kaa/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/kaa /home/pi/kaa/libs/kaa /home/pi/kaa/build /home/pi/kaa/build/libs/kaa /home/pi/kaa/build/libs/kaa/CMakeFiles/extension_logging.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/kaa/CMakeFiles/extension_logging.dir/depend

