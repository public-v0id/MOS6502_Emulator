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
include CMakeFiles/memory.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/memory.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/memory.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/memory.dir/flags.make

CMakeFiles/memory.dir/src/memory.cpp.o: CMakeFiles/memory.dir/flags.make
CMakeFiles/memory.dir/src/memory.cpp.o: /home/Petrign/Проги/CPP/mos6502_emulator/src/memory.cpp
CMakeFiles/memory.dir/src/memory.cpp.o: CMakeFiles/memory.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/Petrign/Проги/CPP/mos6502_emulator/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/memory.dir/src/memory.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/memory.dir/src/memory.cpp.o -MF CMakeFiles/memory.dir/src/memory.cpp.o.d -o CMakeFiles/memory.dir/src/memory.cpp.o -c /home/Petrign/Проги/CPP/mos6502_emulator/src/memory.cpp

CMakeFiles/memory.dir/src/memory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/memory.dir/src/memory.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Petrign/Проги/CPP/mos6502_emulator/src/memory.cpp > CMakeFiles/memory.dir/src/memory.cpp.i

CMakeFiles/memory.dir/src/memory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/memory.dir/src/memory.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Petrign/Проги/CPP/mos6502_emulator/src/memory.cpp -o CMakeFiles/memory.dir/src/memory.cpp.s

# Object files for target memory
memory_OBJECTS = \
"CMakeFiles/memory.dir/src/memory.cpp.o"

# External object files for target memory
memory_EXTERNAL_OBJECTS =

libmemory.a: CMakeFiles/memory.dir/src/memory.cpp.o
libmemory.a: CMakeFiles/memory.dir/build.make
libmemory.a: CMakeFiles/memory.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/Petrign/Проги/CPP/mos6502_emulator/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmemory.a"
	$(CMAKE_COMMAND) -P CMakeFiles/memory.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/memory.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/memory.dir/build: libmemory.a
.PHONY : CMakeFiles/memory.dir/build

CMakeFiles/memory.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/memory.dir/cmake_clean.cmake
.PHONY : CMakeFiles/memory.dir/clean

CMakeFiles/memory.dir/depend:
	cd /home/Petrign/Проги/CPP/mos6502_emulator/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Petrign/Проги/CPP/mos6502_emulator /home/Petrign/Проги/CPP/mos6502_emulator /home/Petrign/Проги/CPP/mos6502_emulator/cmake /home/Petrign/Проги/CPP/mos6502_emulator/cmake /home/Petrign/Проги/CPP/mos6502_emulator/cmake/CMakeFiles/memory.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/memory.dir/depend

