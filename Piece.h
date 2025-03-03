#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "Position.h"
#include "Player.h"

enum class PieceType {
    Knight,
    Stone
};

// Forward declarations
class Board;

class Piece {
public:
    Piece(PlayerColor color, Position position);
    virtual ~Piece() = default;
    
    // Get piece properties
    PlayerColor getColor() const { return m_color; }
    const Position& getPosition() const { return m_position; }
    virtual PieceType getType() const = 0;
    
    // Set piece position
    void setPosition(const Position& position) { m_position = position; }
    
    // Type checking
    virtual bool isKnight() const { return false; }
    virtual bool isStone() const { return false; }
    
    // Rendering
    virtual void render(SDL_Renderer* renderer, bool isSelected) const = 0;
    
    // Game logic
    virtual std::vector<Position> getValidMoves(const Board& board) const = 0;
    
    // Utility
    std::string toString() const;
    
protected:
    PlayerColor m_color;
    Position m_position;
};
