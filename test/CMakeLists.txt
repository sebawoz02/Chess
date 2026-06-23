# Create test executable
add_executable(board_test test_board.cpp)

set(BOARD_TEST_SOURCES
    ../src/board.cpp
    ../src/piece.cpp
)

target_link_libraries(board_test PRIVATE GTest::gtest GTest::gtest_main)

target_sources(board_test PRIVATE ${BOARD_TEST_SOURCES})
target_include_directories(board_test PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_compile_options(board_test PRIVATE ${COMMON_WARNING_FLAGS})
add_test(NAME board_tests COMMAND board_test)

# Create test executable for piece
add_executable(piece_test test_piece.cpp)

set(PIECE_TEST_SOURCES
    ../src/piece.cpp
)

target_link_libraries(piece_test PRIVATE GTest::gtest GTest::gtest_main)

target_sources(piece_test PRIVATE ${PIECE_TEST_SOURCES})
target_include_directories(piece_test PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_compile_options(piece_test PRIVATE ${COMMON_WARNING_FLAGS})
add_test(NAME piece_tests COMMAND piece_test)
