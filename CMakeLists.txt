cmake_minimum_required(VERSION 3.10)

# Suppress CMake developer warnings
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS TRUE CACHE BOOL "" FORCE)

project(Chess LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(COMMON_WARNING_FLAGS
    $<$<CXX_COMPILER_ID:GNU>:-Wall>
    $<$<CXX_COMPILER_ID:GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:GNU>:-Wpedantic>
    $<$<CXX_COMPILER_ID:GNU>:-Wconversion>
    $<$<CXX_COMPILER_ID:GNU>:-Wshadow>
    $<$<CXX_COMPILER_ID:GNU>:-Wsign-conversion>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-unused-parameter>
)

set(CHESS_SOURCES
    src/main.cpp
    src/board.cpp
    src/piece.cpp
)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

add_executable(Chess ${CHESS_SOURCES})

target_include_directories(Chess PRIVATE ${CMAKE_SOURCE_DIR}/inc)

target_compile_options(Chess PRIVATE ${COMMON_WARNING_FLAGS})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test subdirectory
add_subdirectory(test)
