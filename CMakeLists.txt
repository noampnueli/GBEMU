cmake_minimum_required(VERSION 3.5)
project(GBEMU)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lSDL2")

set(SOURCE_FILES main.cpp CPU.h)
set(SOURCE_FILES main.cpp MMU.h definitions.h GUI.h GPU.h opcodes.h opmap.h extra_opcodes.h)

add_executable(GBEMU ${SOURCE_FILES})