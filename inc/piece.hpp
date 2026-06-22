#include <vector>

enum class PieceType { Empty, Pawn, Knight, Bishop, Rook, Queen, King };

enum class Color { None, White, Black };

class Piece {
   public:
    PieceType type = PieceType::Empty;
    Color color = Color::None;

    static Piece makePiece(PieceType type, Color color);

    static char pieceToChar(Piece piece);

    static std::vector<std::pair<size_t, size_t>> getPossibleMoves(const Piece& piece,
                                                                   const size_t rank,
                                                                   const size_t file);

    int getValue() const;
};