cmake_minimum_required(VERSION 3.16)
project(STL_Container_Inspector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(stl_inspector
    src/main.cpp
)

target_include_directories(stl_inspector PRIVATE include)
