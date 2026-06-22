#include "piece.hpp"

#include <cctype>
#include <string>

static void generateBishopMoves(const Piece& piece, const size_t rank, const size_t file,
                                std::vector<std::pair<size_t, size_t>>& moves);
static void generateRookMoves(const Piece& piece, const size_t rank, const size_t file,
                              std::vector<std::pair<size_t, size_t>>& moves);

Piece Piece::makePiece(PieceType type, Color color) {
    Piece piece;
    piece.type = type;
    piece.color = color;
    return piece;
}

char Piece::pieceToChar(Piece piece) {
    char c = '.';
    switch (piece.type) {
        case PieceType::Pawn:
            c = 'p';
            break;
        case PieceType::Knight:
            c = 'n';
            break;
        case PieceType::Bishop:
            c = 'b';
            break;
        case PieceType::Rook:
            c = 'r';
            break;
        case PieceType::Queen:
            c = 'q';
            break;
        case PieceType::King:
            c = 'k';
            break;
        default:
            c = '.';
            break;
    }
    if (piece.color == Color::White && c != '.') {
        c = static_cast<char>(std::toupper(c));
    }
    return c;
}

int Piece::getValue() const {
    switch (type) {
        case PieceType::Pawn:
            return 1;
        case PieceType::Knight:
            return 3;
        case PieceType::Bishop:
            return 3;
        case PieceType::Rook:
            return 5;
        case PieceType::Queen:
            return 9;
        case PieceType::King:
            return 0;
        default:
            return 0;
    }
}

std::vector<std::pair<size_t, size_t>> Piece::getPossibleMoves(const Piece& piece,
                                                               const size_t rank,
                                                               const size_t file) {
    if (piece.type == PieceType::Empty) {
        return {};
    }

    std::vector<std::pair<size_t, size_t>> moves;
    switch (piece.type) {
        case PieceType::Pawn:
            // Pawns can move forward one square, or two squares from their starting position
            if (piece.color == Color::White) {
                if (rank < 7) {
                    moves.emplace_back(rank + 1, file);
                    if (rank == 1) {
                        moves.emplace_back(rank + 2, file);
                    }
                }
            } else {
                if (rank > 0) {
                    moves.emplace_back(rank - 1, file);
                    if (rank == 6) {
                        moves.emplace_back(rank - 2, file);
                    }
                }
            }
            break;
        case PieceType::Knight:
            // Knights move in an "L" shape: two squares in one direction and then one square
            // perpendicular
            for (int8_t dr : {-2, -1, 1, 2}) {
                for (int8_t df : {-2, -1, 1, 2}) {
                    if (std::abs(dr) != std::abs(df)) {
                        size_t newRank = rank + dr;
                        size_t newFile = file + df;
                        if (newRank < 8 && newFile < 8) {
                            moves.emplace_back(newRank, newFile);
                        }
                    }
                }
            }
            break;
        case PieceType::Bishop:
            // Bishops move diagonally any number of squares
            generateBishopMoves(piece, rank, file, moves);
            break;
        case PieceType::Rook:
            // Rooks move horizontally or vertically any number of squares
            generateRookMoves(piece, rank, file, moves);
            break;
        case PieceType::Queen:
            // Queens move like both rooks and bishops
            generateBishopMoves(piece, rank, file, moves);
            generateRookMoves(piece, rank, file, moves);
            break;
        case PieceType::King:
            // Kings move one square in any direction
            for (int8_t dr : {-1, 0, 1}) {
                for (int8_t df : {-1, 0, 1}) {
                    if (dr != 0 || df != 0) {
                        size_t newRank = rank + dr;
                        size_t newFile = file + df;
                        if (newRank < 8 && newFile < 8) {
                            moves.emplace_back(newRank, newFile);
                        }
                    }
                }
            }
            break;
        default:
            break;
    }
    return moves;
}

static void generateBishopMoves(const Piece& piece, const size_t rank, const size_t file,
                                std::vector<std::pair<size_t, size_t>>& moves) {
    for (int8_t dr : {-1, 1}) {
        for (int8_t df : {-1, 1}) {
            size_t newRank = rank;
            size_t newFile = file;
            while (newRank > 0 && newRank < 7 && newFile < 7 && newFile > 0) {
                newRank += dr;
                newFile += df;
                moves.emplace_back(newRank, newFile);
            }
        }
    }
}

static void generateRookMoves(const Piece& piece, const size_t rank, const size_t file,
                              std::vector<std::pair<size_t, size_t>>& moves) {
    for (int8_t dr : {-1, 1}) {
        size_t newRank = rank;
        while (0 < newRank && newRank < 7) {
            newRank += dr;
            moves.emplace_back(newRank, file);
        }
        size_t newFile = file;
        while (0 < newFile && newFile < 7) {
            newFile += dr;
            moves.emplace_back(rank, newFile);
        }
    }
}
