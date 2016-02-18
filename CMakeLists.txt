cmake_minimum_required(VERSION 3.3)
project(ToyJava)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES JavaASTree.h JavaBaseType.h CodeExecute.h CodeExecute.cpp parser.hpp parser.cpp tokens.cpp main.cpp)

add_executable(ToyJava ${SOURCE_FILES})