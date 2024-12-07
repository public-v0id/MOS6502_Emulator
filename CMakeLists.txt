cmake_minimum_required(VERSION 2.8)

project(mos6502_emulator)

set(SOURCE_EXE src/emulator.cpp)

add_library(mos6502 STATIC src/mos6502.cpp)

add_library(memory STATIC src/memory.cpp)

add_library(bit_manip STATIC src/memory.cpp)

add_executable(emulator ${SOURCE_EXE})

target_link_libraries(emulator mos6502 memory bit_manip)
