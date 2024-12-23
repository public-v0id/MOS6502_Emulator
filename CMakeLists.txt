cmake_minimum_required(VERSION 2.8)

project(mos6502_emulator)

set(SOURCES src/emulator.cpp src/mos6502.cpp src/operations.cpp src/memory.cpp src/bit_manip.cpp src/hex.cpp)

add_executable(emulator ${SOURCES})

target_include_directories(emulator PRIVATE ${CMAKE_SOURCE_DIR}/include)
