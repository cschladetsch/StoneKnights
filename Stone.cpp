#include "Stone.h"
#include "Board.h"
#include "Constants.h"
#include <SDL2/SDL2_gfxPrimitives.h>

Stone::Stone(PlayerColor color, Position position)
    : Piece(color, position)
{
}

std::vector<Position> Stone::getValidMoves(const Board& board) const {
    // Stones can't move, return empty vector
    return {};
}

void Stone::render(SDL_Renderer* renderer, bool isSelected) const {
    int x = Constants::BOARD_OFFSET_X + m_position.col * Constants::SQUARE_SIZE + Constants::SQUARE_SIZE / 2;
    int y = Constants::BOARD_OFFSET_Y + m_position.row * Constants::SQUARE_SIZE + Constants::SQUARE_SIZE / 2;
    int radius = Constants::SQUARE_SIZE / 3; // Stones are smaller than knights
    
    SDL_Color color = m_color == PlayerColor::White ? 
                     SDL_Color{Constants::WHITE_PIECE_R, Constants::WHITE_PIECE_G, Constants::WHITE_PIECE_B, 255} :
                     SDL_Color{Constants::BLACK_PIECE_R, Constants::BLACK_PIECE_G, Constants::BLACK_PIECE_B, 255};
    
    SDL_Color outlineColor = m_color == PlayerColor::White ? 
                           SDL_Color{Constants::WHITE_OUTLINE_R, Constants::WHITE_OUTLINE_G, Constants::WHITE_OUTLINE_B, 255} :
                           SDL_Color{Constants::BLACK_OUTLINE_R, Constants::BLACK_OUTLINE_G, Constants::BLACK_OUTLINE_B, 255};
    
    // Draw highlight if selected
    if (isSelected) {
        filledCircleRGBA(renderer, x, y, radius + 5,
                        Constants::SELECTED_SQUARE_R, 
                        Constants::SELECTED_SQUARE_G, 
                        Constants::SELECTED_SQUARE_B, 
                        Constants::SELECTED_SQUARE_A);
    }
    
    // Draw stone circle
    filledCircleRGBA(renderer, x, y, radius,
                    color.r, color.g, color.b, 255);
    
    // Draw outline
    aacircleRGBA(renderer, x, y, radius,
                outlineColor.r, outlineColor.g, outlineColor.b, 255);
}
