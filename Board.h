#pragma once

#include <vector>
#include <memory>
#include <array>
#include <SDL2/SDL.h>
#include "Position.h"
#include "Player.h"
#include "Piece.h"
#include "Constants.h"  // Add this include

class Stone;
class Knight;

class Board {
public:
    Board();
    ~Board();

    // Board management
    void reset();
    
    // Piece queries
    const Piece* getPieceAt(const Position& pos) const;
    Piece* getPieceAt(const Position& pos);
    bool isEmptyAt(const Position& pos) const;
    bool isOccupiedByColor(const Position& pos, PlayerColor color) const;
    
    // Piece actions
    bool movePiece(const Position& from, const Position& to);
    void removePiece(const Position& pos);
    bool placeStone(PlayerColor color, const Position& pos);
    
    // Rendering
    void render(SDL_Renderer* renderer, const Position* selectedPosition, 
                const std::vector<Position>& validMoves) const;
    
    // Capture mechanics
    std::vector<Position> checkStoneCaptures(const Position& pos, PlayerColor player) const;

private:
    // Piece container
    std::vector<std::unique_ptr<Piece>> m_pieces;
    
    // Helper methods
    void setupInitialPieces();
    void clearPieces();
    void addPiece(std::unique_ptr<Piece> piece);
    
    // Position validation
    bool isValidPosition(const Position& pos) const {
        return pos.row >= 0 && pos.row < Constants::BOARD_SIZE && 
               pos.col >= 0 && pos.col < Constants::BOARD_SIZE;
    }
};
