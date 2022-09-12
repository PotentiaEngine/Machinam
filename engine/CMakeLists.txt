cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Game VERSION 0.0.1.0 LANGUAGES CXX)

file(GLOB_RECURSE SRC_FILES "*/*.h" "*/*.cpp")

add_compile_options(-std=c++20)

add_executable(Game WIN32 ${SRC_FILES})
target_include_directories(Game PUBLIC "src/")
