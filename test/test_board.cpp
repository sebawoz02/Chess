#include <gtest/gtest.h>
#include "board.hpp"

class BoardTest : public ::testing::Test {
protected:
    Board board;
};

// ----------- BOARD isValidSquare() TEST SECTION -----------

// Test that isValidSquare returns true for valid squares
TEST_F(BoardTest, IsValidSquareReturnsTrueForValidSquares) {
    EXPECT_TRUE(board.isValidSquare(0, 0));
    EXPECT_TRUE(board.isValidSquare(7, 7));
    EXPECT_TRUE(board.isValidSquare(3, 4));
}

// Test that isValidSquare returns false for invalid squares
TEST_F(BoardTest, IsValidSquareReturnsFalseForInvalidSquares) {
    EXPECT_FALSE(board.isValidSquare(-1, 0));
    EXPECT_FALSE(board.isValidSquare(0, -1));
    EXPECT_FALSE(board.isValidSquare(8, 0));
    EXPECT_FALSE(board.isValidSquare(0, 54));
}

// ----------- BOARD getPiece() TEST SECTION -----------

// Test that getPiece returns the correct piece for a given square
TEST_F(BoardTest, GetPieceReturnsCorrectPiece) {
    board.reset();
    Piece piece = board.getPiece(0, 0);  // Should be a white rook
    EXPECT_EQ(piece.type, PieceType::Rook);
    EXPECT_EQ(piece.color, Color::White);
}

// ----------- BOARD reset() TEST SECTION -----------

// Test that reset initializes the board with the correct starting position
TEST_F(BoardTest, ResetInitializesPawns) {
    board.reset();
    
    // White pawns at rank 1
    for (size_t file = 0; file < Board::BOARD_SIZE; ++file) {
        Piece pawn = board.getPiece(1, file);
        EXPECT_EQ(pawn.type, PieceType::Pawn);
        EXPECT_EQ(pawn.color, Color::White);
    }
    
    // Black pawns at rank 6
    for (size_t file = 0; file < Board::BOARD_SIZE; ++file) {
        Piece pawn = board.getPiece(6, file);
        EXPECT_EQ(pawn.type, PieceType::Pawn);
        EXPECT_EQ(pawn.color, Color::Black);
    }
}

// Test that reset initializes white back rank correctly
TEST_F(BoardTest, ResetInitializesWhiteBackRank) {
    board.reset();
    
    // Expected order: Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook
    PieceType expectedOrder[] = {
        PieceType::Rook, PieceType::Knight, PieceType::Bishop,
        PieceType::Queen, PieceType::King, PieceType::Bishop,
        PieceType::Knight, PieceType::Rook
    };
    
    for (size_t file = 0; file < Board::BOARD_SIZE; ++file) {
        Piece piece = board.getPiece(0, file);
        EXPECT_EQ(piece.type, expectedOrder[file]);
        EXPECT_EQ(piece.color, Color::White);
    }
}

// Test that reset initializes black back rank correctly
TEST_F(BoardTest, ResetInitializesBlackBackRank) {
    board.reset();
    
    // Expected order: Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook
    PieceType expectedOrder[] = {
        PieceType::Rook, PieceType::Knight, PieceType::Bishop,
        PieceType::Queen, PieceType::King, PieceType::Bishop,
        PieceType::Knight, PieceType::Rook
    };
    
    for (size_t file = 0; file < Board::BOARD_SIZE; ++file) {
        Piece piece = board.getPiece(7, file);
        EXPECT_EQ(piece.type, expectedOrder[file]);
        EXPECT_EQ(piece.color, Color::Black);
    }
}

// Test that middle squares are empty after reset
TEST_F(BoardTest, ResetEmptiesMiddleSquares) {
    board.reset();
    
    for (size_t rank = 2; rank < 6; ++rank) {
        for (size_t file = 0; file < Board::BOARD_SIZE; ++file) {
            Piece piece = board.getPiece(rank, file);
            EXPECT_EQ(piece.type, PieceType::Empty);
            EXPECT_EQ(piece.color, Color::None);
        }
    }
}

// Test that reset can be called multiple times
TEST_F(BoardTest, ResetCanBeCalledMultipleTimes) {
    board.reset();
    board.getPiece(4, 4);  // Make some queries
    
    board.reset();  // Reset again
    
    // Verify the board is still correctly initialized
    Piece whitePawn = board.getPiece(1, 0);
    EXPECT_EQ(whitePawn.type, PieceType::Pawn);
    EXPECT_EQ(whitePawn.color, Color::White);
    
    Piece blackPawn = board.getPiece(6, 0);
    EXPECT_EQ(blackPawn.type, PieceType::Pawn);
    EXPECT_EQ(blackPawn.color, Color::Black);
}

// Test piece value after reset
TEST_F(BoardTest, PieceValuesAfterReset) {
    board.reset();
    
    // Check pawn value
    Piece pawn = board.getPiece(1, 0);
    EXPECT_EQ(pawn.getValue(), 1);
    
    // Check knight value
    Piece knight = board.getPiece(0, 1);
    EXPECT_EQ(knight.getValue(), 3);
    
    // Check rook value
    Piece rook = board.getPiece(0, 0);
    EXPECT_EQ(rook.getValue(), 5);
    
    // Check queen value
    Piece queen = board.getPiece(0, 3);
    EXPECT_EQ(queen.getValue(), 9);
    
    // Check king value
    Piece king = board.getPiece(0, 4);
    EXPECT_EQ(king.getValue(), 0);
}

// ----------- BOARD setPiece() TEST SECTION -----------
TEST_F(BoardTest, SetPieceUpdatesSquare) {
    board.reset();
    
    // Set a white queen at (4, 4)
    Piece newQueen = Piece::makePiece(PieceType::Queen, Color::White);
    board.setPiece(4, 4, newQueen);
    
    Piece retrievedPiece = board.getPiece(4, 4);
    EXPECT_EQ(retrievedPiece.type, PieceType::Queen);
    EXPECT_EQ(retrievedPiece.color, Color::White);
}
