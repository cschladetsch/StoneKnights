#pragma once

#include "Piece.h"
#include <array>

class Board; // Forward declaration if needed

class Knight : public Piece {
public:
    Knight(PlayerColor color, Position position);
    
    // Implementation of virtual methods
    PieceType getType() const override { return PieceType::Knight; }
    bool isKnight() const override { return true; }
    void render(SDL_Renderer* renderer, bool isSelected) const override;
    std::vector<Position> getValidMoves(const Board& board) const override;
    
    // Static method to get knight move offsets
    static const std::array<std::pair<int, int>, 8>& getMoveOffsets();
};
