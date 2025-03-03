#include "Board.h"
#include "Piece.h"
#include "Knight.h"
#include "Stone.h"
#include "Constants.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <algorithm>
#include <iostream>

Board::Board() {
    setupInitialPieces();
}

Board::~Board() {
    clearPieces();
}

void Board::reset() {
    clearPieces();
    setupInitialPieces();
}

void Board::setupInitialPieces() {
    clearPieces();
    
    // Create black knights (top row)
    for (int col = 0; col < Constants::BOARD_SIZE; ++col) {
        addPiece(std::make_unique<Knight>(PlayerColor::Black, Position(0, col)));
    }
    
    // Create white knights (bottom row)
    for (int col = 0; col < Constants::BOARD_SIZE; ++col) {
        addPiece(std::make_unique<Knight>(PlayerColor::White, Position(7, col)));
    }
}

void Board::render(SDL_Renderer* renderer, const Position* selectedPosition, 
                   const std::vector<Position>& validMoves) const {
    // Draw board squares
    for (int row = 0; row < Constants::BOARD_SIZE; ++row) {
        for (int col = 0; col < Constants::BOARD_SIZE; ++col) {
            // Calculate square position
            SDL_Rect square = {
                Constants::BOARD_OFFSET_X + col * Constants::SQUARE_SIZE,
                Constants::BOARD_OFFSET_Y + row * Constants::SQUARE_SIZE,
                Constants::SQUARE_SIZE,
                Constants::SQUARE_SIZE
            };
            
            // Determine square color (alternating pattern)
            bool isLightSquare = (row + col) % 2 == 0;
            SDL_Color squareColor;
            
            if (isLightSquare) {
                squareColor = {Constants::LIGHT_SQUARE_R, Constants::LIGHT_SQUARE_G, Constants::LIGHT_SQUARE_B, 255};
            } else {
                squareColor = {Constants::DARK_SQUARE_R, Constants::DARK_SQUARE_G, Constants::DARK_SQUARE_B, 255};
            }
            
            // Draw the square
            SDL_SetRenderDrawColor(renderer, squareColor.r, squareColor.g, squareColor.b, squareColor.a);
            SDL_RenderFillRect(renderer, &square);
            
            // Draw square border
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &square);
        }
    }
    
    // Draw valid move indicators
    for (const auto& pos : validMoves) {
        int centerX = Constants::BOARD_OFFSET_X + pos.col * Constants::SQUARE_SIZE + Constants::SQUARE_SIZE / 2;
        int centerY = Constants::BOARD_OFFSET_Y + pos.row * Constants::SQUARE_SIZE + Constants::SQUARE_SIZE / 2;
        
        filledCircleRGBA(renderer, centerX, centerY, 10,
                        Constants::VALID_MOVE_R, 
                        Constants::VALID_MOVE_G, 
                        Constants::VALID_MOVE_B, 
                        Constants::VALID_MOVE_A);
    }
    
    // Draw all pieces
    for (const auto& piece : m_pieces) {
        bool isSelected = selectedPosition && *selectedPosition == piece->getPosition();
        piece->render(renderer, isSelected);
    }
}

void Board::clearPieces() {
    m_pieces.clear();
}

void Board::addPiece(std::unique_ptr<Piece> piece) {
    m_pieces.push_back(std::move(piece));
}

const Piece* Board::getPieceAt(const Position& pos) const {
    for (const auto& piece : m_pieces) {
        if (piece->getPosition() == pos) {
            return piece.get();
        }
    }
    return nullptr;
}

Piece* Board::getPieceAt(const Position& pos) {
    for (auto& piece : m_pieces) {
        if (piece->getPosition() == pos) {
            return piece.get();
        }
    }
    return nullptr;
}

bool Board::isEmptyAt(const Position& pos) const {
    return getPieceAt(pos) == nullptr;
}

bool Board::isOccupiedByColor(const Position& pos, PlayerColor color) const {
    const Piece* piece = getPieceAt(pos);
    return piece && piece->getColor() == color;
}

bool Board::movePiece(const Position& from, const Position& to) {
    if (!isValidPosition(from) || !isValidPosition(to)) {
        return false;
    }
    
    Piece* movingPiece = getPieceAt(from);
    if (!movingPiece || !movingPiece->isKnight()) {
        return false;
    }
    
    // Check if the "to" position contains a piece to capture
    Piece* targetPiece = getPieceAt(to);
    if (targetPiece) {
        // Can only capture knights of the opposite color
        if (targetPiece->isKnight() && targetPiece->getColor() != movingPiece->getColor()) {
            // Remove the captured piece
            removePiece(to);
        } else {
            // Can't capture own pieces or stones
            return false;
        }
    }
    
    // Update the piece's position
    movingPiece->setPosition(to);
    return true;
}

void Board::removePiece(const Position& pos) {
    m_pieces.erase(
        std::remove_if(m_pieces.begin(), m_pieces.end(),
                      [&pos](const std::unique_ptr<Piece>& piece) {
                          return piece->getPosition() == pos;
                      }),
        m_pieces.end());
}

bool Board::placeStone(PlayerColor color, const Position& pos) {
    if (!isValidPosition(pos) || !isEmptyAt(pos)) {
        return false;
    }
    
    // Add the new stone
    addPiece(std::make_unique<Stone>(color, pos));
    
    return true;
}

std::vector<Position> Board::checkStoneCaptures(const Position& pos, PlayerColor player) const {
    std::vector<Position> capturedPositions;
    PlayerColor opponentColor = Player::getOpponent(player);
    
    // Four directions: up, right, down, left
    const std::array<std::pair<int, int>, 4> directions = {{
        {-1, 0}, {0, 1}, {1, 0}, {0, -1}
    }};
    
    for (const auto& [dx, dy] : directions) {
        std::vector<Position> captureChain;
        int currentRow = pos.row + dx;
        int currentCol = pos.col + dy;
        
        // First, check if there's an opponent's stone adjacent
        if (currentRow >= 0 && currentRow < Constants::BOARD_SIZE && 
            currentCol >= 0 && currentCol < Constants::BOARD_SIZE) {
            
            const Piece* adjacentPiece = getPieceAt(Position(currentRow, currentCol));
            
            if (adjacentPiece && adjacentPiece->isStone() && adjacentPiece->getColor() == opponentColor) {
                // Found an opponent's stone, start tracking the chain
                while (currentRow >= 0 && currentRow < Constants::BOARD_SIZE && 
                       currentCol >= 0 && currentCol < Constants::BOARD_SIZE) {
                    
                    Position currentPos(currentRow, currentCol);
                    const Piece* currentPiece = getPieceAt(currentPos);
                    
                    if (!currentPiece) {
                        // Chain broken by empty space
                        captureChain.clear();
                        break;
                    }
                    
                    if (currentPiece->getColor() == player) {
                        // Chain closed by same color, capture all stones in between
                        capturedPositions.insert(capturedPositions.end(), captureChain.begin(), captureChain.end());
                        break;
                    }
                    
                    if (currentPiece->isKnight()) {
                        // Knights can't be captured by stones, chain broken
                        captureChain.clear();
                        break;
                    }
                    
                    captureChain.push_back(currentPos);
                    
                    // Move to next position in the direction
                    currentRow += dx;
                    currentCol += dy;
                }
            }
        }
    }
    
    return capturedPositions;
}
