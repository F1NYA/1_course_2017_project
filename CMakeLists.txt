cmake_minimum_required(VERSION 3.6)
project(1_course_2017_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp include/render.h src/render.c tests/main.c)
add_executable(1_course_2017_project ${SOURCE_FILES} tests/main.c)