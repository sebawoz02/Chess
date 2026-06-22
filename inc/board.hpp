#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <array>
#include <string>

#include "piece.hpp"

class Board {
public:

    static constexpr int BOARD_SIZE = 8;
    using Row = std::array<Piece, BOARD_SIZE>;
    using Grid = std::array<Row, BOARD_SIZE>;

    Board();
    void reset();
    bool isValidSquare(int rank, int file) const;
    void setPiece(int rank, int file, Piece piece);
    Piece getPiece(int rank, int file) const;
    std::string toString() const;
private:
    Grid squares_;
};

#endif // CHESS_BOARD_H
