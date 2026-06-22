# Create test executable
add_executable(board_test test_board.cpp)

# Link GTest
target_link_libraries(board_test GTest::gtest GTest::gtest_main)

# Link board implementation - need to include board sources
target_sources(board_test PRIVATE 
    ../src/board.cpp 
    ../src/piece.cpp
)

# Include directories
target_include_directories(board_test PRIVATE ${CMAKE_SOURCE_DIR}/inc)

# Apply same compiler warnings to tests
target_compile_options(board_test PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall>
    $<$<CXX_COMPILER_ID:GNU>:-Wextra>
    $<$<CXX_COMPILER_ID:GNU>:-Wpedantic>
    $<$<CXX_COMPILER_ID:GNU>:-Wconversion>
    $<$<CXX_COMPILER_ID:GNU>:-Wshadow>
    $<$<CXX_COMPILER_ID:GNU>:-Wsign-conversion>
)

# Register test
add_test(NAME board_tests COMMAND board_test)
