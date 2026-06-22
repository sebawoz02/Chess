#include "board.hpp"

Board::Board() {
    reset();
}

void Board::reset() {
    for (int rank = 0; rank < BOARD_SIZE; ++rank) {
        for (int file = 0; file < BOARD_SIZE; ++file) {
            squares_[rank][file] = Piece::makePiece(PieceType::Empty, Color::None);
        }
    }

    // Place white pieces
    squares_[0] = Row{Piece::makePiece(PieceType::Rook, Color::White),
                      Piece::makePiece(PieceType::Knight, Color::White),
                      Piece::makePiece(PieceType::Bishop, Color::White),
                      Piece::makePiece(PieceType::Queen, Color::White),
                      Piece::makePiece(PieceType::King, Color::White),
                      Piece::makePiece(PieceType::Bishop, Color::White),
                      Piece::makePiece(PieceType::Knight, Color::White),
                      Piece::makePiece(PieceType::Rook, Color::White)};
    for (int file = 0; file < BOARD_SIZE; ++file) {
        squares_[1][file] = Piece::makePiece(PieceType::Pawn, Color::White);
    }

    // Place black pieces
    squares_[7] = Row{Piece::makePiece(PieceType::Rook, Color::Black),
                      Piece::makePiece(PieceType::Knight, Color::Black),
                      Piece::makePiece(PieceType::Bishop, Color::Black),
                      Piece::makePiece(PieceType::Queen, Color::Black),
                      Piece::makePiece(PieceType::King, Color::Black),
                      Piece::makePiece(PieceType::Bishop, Color::Black),
                      Piece::makePiece(PieceType::Knight, Color::Black),
                      Piece::makePiece(PieceType::Rook, Color::Black)};
    for (int file = 0; file < BOARD_SIZE; ++file) {
        squares_[6][file] = Piece::makePiece(PieceType::Pawn, Color::Black);
    }
}

bool Board::isValidSquare(int rank, int file) const {
    return rank >= 0 && rank < BOARD_SIZE && file >= 0 && file < BOARD_SIZE;
}

void Board::setPiece(int rank, int file, Piece piece) {
    if (isValidSquare(rank, file)) {
        squares_[rank][file] = piece;
    }
}

Piece Board::getPiece(int rank, int file) const {
    if (isValidSquare(rank, file)) {
        return squares_[rank][file];
    }
    return Piece::makePiece(PieceType::Empty, Color::None);
}

std::string Board::toString() const {
    std::string output;
    for (int rank = BOARD_SIZE - 1; rank >= 0; --rank) {
        output += std::to_string(rank + 1);
        output += " ";
        for (int file = 0; file < BOARD_SIZE; ++file) {
            output += Piece::pieceToChar(squares_[rank][file]);
            output += ' ';
        }
        output += '\n';
    }
    output += "  a b c d e f g h\n";
    return output;
}