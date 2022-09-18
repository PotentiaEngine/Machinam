cmake_minimum_required(VERSION 3.15)


set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Potentia VERSION 0.0.1.0 LANGUAGES CXX)

# ENGINE

file(GLOB_RECURSE ENGINE_FILES "potentia/**/*.h" "potentia/**/*.cpp")
add_library(PotentiaEngine ${ENGINE_FILES})
target_include_directories(PotentiaEngine PUBLIC "./potentia/")

# TESTS

include(GoogleTest)
enable_testing()
file(GLOB_RECURSE TEST_FILES "./potentia-test/*/*.h" "./potentia-test/*/*.cpp")

add_executable(PotentiaTest ${TEST_FILES})
target_link_libraries(PotentiaTest PUBLIC PotentiaEngine)
target_include_directories(PotentiaTest PUBLIC "./")
find_package(GTest CONFIG REQUIRED)
target_link_libraries(PotentiaTest PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
gtest_add_tests(TARGET PotentiaTest ${TEST_FILES})

# SAMPLE

file(GLOB_RECURSE SAMPLE_FILES "sample/*.h" "sample/*.cpp")
add_executable(PotentiaSample WIN32 ${SAMPLE_FILES})
target_link_libraries(PotentiaSample PUBLIC PotentiaEngine)
target_include_directories(PotentiaSample PUBLIC "./")


# --- TOOLS ---

## ASSET BUNDLER
file (GLOB_RECURSE ASSET_BUNDLER_FILES "./tools/asset-bundler/*/*.h" "./tools/asset-bundler/*/*.cpp" "./tools/asset-bundler/*.h" "./tools/asset-bundler/*.cpp")
add_executable(PotentiaTool_AssetBundler ${ASSET_BUNDLER_FILES})
target_include_directories(PotentiaTool_AssetBundler PUBLIC ./tools/asset-bundler/)
find_package(CLI11 CONFIG REQUIRED)
target_link_libraries(PotentiaTool_AssetBundler PRIVATE CLI11::CLI11)
find_package(assimp CONFIG REQUIRED)
target_link_libraries(PotentiaTool_AssetBundler PRIVATE assimp::assimp)
