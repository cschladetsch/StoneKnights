#pragma once

#include "Piece.h"
#include "Position.h"

class Board; // Forward declaration

class Stone : public Piece {
public:
    Stone(PlayerColor color, Position position);
    
    // Override pure virtual methods from Piece
    PieceType getType() const override { return PieceType::Stone; }
    bool isStone() const override { return true; }
    
    // Implement getValidMoves
    std::vector<Position> getValidMoves(const Board& board) const override;
    
    // Implement render method
    void render(SDL_Renderer* renderer, bool isSelected) const override;
};
