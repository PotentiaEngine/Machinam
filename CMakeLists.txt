cmake_minimum_required(VERSION 3.15)

project(Potentia VERSION 0.0.1.0 LANGUAGES CXX)

file(GLOB_RECURSE SRC_FILES "potentia/**/*.h" "potentia/**/*.cpp")


file(GLOB_RECURSE SAMPLE_FILES "sample/*.h" "sample/*.cpp")
add_compile_options(-std=c++20)
add_executable(Potentia WIN32 ${SRC_FILES} ${SAMPLE_FILES})

target_include_directories(Potentia PUBLIC "./potentia")
