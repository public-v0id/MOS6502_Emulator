# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/Petrign/Проги/CPP/mos6502_emulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Petrign/Проги/CPP/mos6502_emulator/cmake

# Include any dependencies generated for this target.
include CMakeFiles/emulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/emulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/emulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/emulator.dir/flags.make

CMakeFiles/emulator.dir/src/emulator.cpp.o: CMakeFiles/emulator.dir/flags.make
CMakeFiles/emulator.dir/src/emulator.cpp.o: /home/Petrign/Проги/CPP/mos6502_emulator/src/emulator.cpp
CMakeFiles/emulator.dir/src/emulator.cpp.o: CMakeFiles/emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/Petrign/Проги/CPP/mos6502_emulator/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/emulator.dir/src/emulator.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/emulator.dir/src/emulator.cpp.o -MF CMakeFiles/emulator.dir/src/emulator.cpp.o.d -o CMakeFiles/emulator.dir/src/emulator.cpp.o -c /home/Petrign/Проги/CPP/mos6502_emulator/src/emulator.cpp

CMakeFiles/emulator.dir/src/emulator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/emulator.dir/src/emulator.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Petrign/Проги/CPP/mos6502_emulator/src/emulator.cpp > CMakeFiles/emulator.dir/src/emulator.cpp.i

CMakeFiles/emulator.dir/src/emulator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/emulator.dir/src/emulator.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Petrign/Проги/CPP/mos6502_emulator/src/emulator.cpp -o CMakeFiles/emulator.dir/src/emulator.cpp.s

# Object files for target emulator
emulator_OBJECTS = \
"CMakeFiles/emulator.dir/src/emulator.cpp.o"

# External object files for target emulator
emulator_EXTERNAL_OBJECTS =

emulator: CMakeFiles/emulator.dir/src/emulator.cpp.o
emulator: CMakeFiles/emulator.dir/build.make
emulator: libmos6502.a
emulator: libmemory.a
emulator: libbit_manip.a
emulator: CMakeFiles/emulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/Petrign/Проги/CPP/mos6502_emulator/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable emulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/emulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/emulator.dir/build: emulator
.PHONY : CMakeFiles/emulator.dir/build

CMakeFiles/emulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/emulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/emulator.dir/clean

CMakeFiles/emulator.dir/depend:
	cd /home/Petrign/Проги/CPP/mos6502_emulator/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Petrign/Проги/CPP/mos6502_emulator /home/Petrign/Проги/CPP/mos6502_emulator /home/Petrign/Проги/CPP/mos6502_emulator/cmake /home/Petrign/Проги/CPP/mos6502_emulator/cmake /home/Petrign/Проги/CPP/mos6502_emulator/cmake/CMakeFiles/emulator.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/emulator.dir/depend

