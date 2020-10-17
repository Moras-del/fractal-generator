cmake_minimum_required(VERSION 3.5)

project(fractal-generator LANGUAGES CXX)
add_executable(fractal-generator src/main.cpp src/climanager.hpp)
target_include_directories(fractal-generator PRIVATE include)
target_link_libraries(fractal-generator GL glut)