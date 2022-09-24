cmake_minimum_required(VERSION 3.20)
include(../../.cmake/ProjectVars.cmake)

project(PotentiaSample_SimpleTriangle VERSION 0.0.1.0 LANGUAGES CXX) 

file(GLOB_RECURSE SRC_FILES "src/*.h" "src/*/*.h" "src/*.cpp" "src/*/*.cpp")

add_executable(PotentiaSample_SimpleTriangle ${SRC_FILES})
target_link_libraries(PotentiaSample_SimpleTriangle PUBLIC PotentiaEngine)
