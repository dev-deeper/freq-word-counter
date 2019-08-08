cmake_minimum_required(VERSION 3.10)
project(freq)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(freq ${SOURCES})
