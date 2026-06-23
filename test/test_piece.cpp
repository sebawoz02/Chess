#include <gtest/gtest.h>

#include <utility>

#include "piece.hpp"

class PieceTest : public ::testing::Test {
   protected:
    Piece piece;
};

TEST_F(PieceTest, MakePieceCreatesCorrectPiece) {
    piece = Piece::makePiece(PieceType::Knight, Color::Black);
    EXPECT_EQ(piece.type, PieceType::Knight);
    EXPECT_EQ(piece.color, Color::Black);

    piece = Piece::makePiece(PieceType::Pawn, Color::White);
    EXPECT_EQ(piece.type, PieceType::Pawn);
    EXPECT_EQ(piece.color, Color::White);
}

TEST_F(PieceTest, GetValueReturnsCorrectValue) {
    piece = Piece::makePiece(PieceType::Pawn, Color::White);
    EXPECT_EQ(piece.getValue(), 1);

    piece = Piece::makePiece(PieceType::Knight, Color::Black);
    EXPECT_EQ(piece.getValue(), 3);

    piece = Piece::makePiece(PieceType::Bishop, Color::White);
    EXPECT_EQ(piece.getValue(), 3);

    piece = Piece::makePiece(PieceType::Rook, Color::Black);
    EXPECT_EQ(piece.getValue(), 5);

    piece = Piece::makePiece(PieceType::Queen, Color::White);
    EXPECT_EQ(piece.getValue(), 9);

    piece = Piece::makePiece(PieceType::King, Color::Black);
    EXPECT_EQ(piece.getValue(), 0);

    piece = Piece::makePiece(PieceType::Empty, Color::None);
    EXPECT_EQ(piece.getValue(), 0);
}

TEST_F(PieceTest, GetPossibleMovesReturnsCorrectMoves) {
    // Test for a white pawn at (1, 0)
    piece = Piece::makePiece(PieceType::Pawn, Color::White);
    auto moves = Piece::getPossibleMoves(piece, 1, 0);
    EXPECT_EQ(moves.size(), 2);
    EXPECT_NE(std::find(moves.begin(), moves.end(), std::make_pair<size_t, size_t>(2, 0)),
              moves.end());
    EXPECT_NE(std::find(moves.begin(), moves.end(), std::make_pair<size_t, size_t>(3, 0)),
              moves.end());

    // Test for a black knight at (7, 1)
    piece = Piece::makePiece(PieceType::Knight, Color::Black);
    moves = Piece::getPossibleMoves(piece, 7, 1);
    EXPECT_EQ(moves.size(), 3);
    EXPECT_NE(std::find(moves.begin(), moves.end(), std::make_pair<size_t, size_t>(5, 0)),
              moves.end());
    EXPECT_NE(std::find(moves.begin(), moves.end(), std::make_pair<size_t, size_t>(5, 2)),
              moves.end());
    EXPECT_NE(std::find(moves.begin(), moves.end(), std::make_pair<size_t, size_t>(6, 3)),
              moves.end());

    piece = Piece::makePiece(PieceType::Empty, Color::None);
    moves = Piece::getPossibleMoves(piece, 4, 4);
    EXPECT_TRUE(moves.empty());

    piece = Piece::makePiece(PieceType::Queen, Color::White);
    moves = Piece::getPossibleMoves(piece, 4, 4);
    EXPECT_FALSE(moves.empty());
    EXPECT_EQ(moves.size(),
              27);  // Queen can move in 8 directions, but some moves are blocked by the board edges
}

// TEMPORARY: Test to later removed functionality

TEST_F(PieceTest, PieceToCharReturnsCorrectCharacter) {
    piece = Piece::makePiece(PieceType::Rook, Color::White);
    EXPECT_EQ(Piece::pieceToChar(piece), 'R');

    piece = Piece::makePiece(PieceType::Queen, Color::Black);
    EXPECT_EQ(Piece::pieceToChar(piece), 'q');

    piece = Piece::makePiece(PieceType::Empty, Color::None);
    EXPECT_EQ(Piece::pieceToChar(piece), '.');
}