cmake_minimum_required(VERSION 3.5)
project(GBEMU)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CPU.h)
set(SOURCE_FILES main.cpp MMU.h definitions.h)

add_executable(GBEMU ${SOURCE_FILES})