cmake_minimum_required(VERSION 3.17)
project(Siec_przewodowa)

set(CMAKE_CXX_STANDARD 17)

add_executable(Siec_przewodowa main.cpp approximately.h approximately.cpp exact.h exact.cpp)