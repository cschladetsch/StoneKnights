#include "Knight.h"
#include "Board.h"
#include "Constants.h"
#include <SDL2/SDL2_gfxPrimitives.h>

Knight::Knight(PlayerColor color, Position position)
    : Piece(color, position)
{
}

const std::array<std::pair<int, int>, 8>& Knight::getMoveOffsets() {
    static const std::array<std::pair<int, int>, 8> offsets = {{
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    }};
    return offsets;
}

std::vector<Position> Knight::getValidMoves(const Board& board) const {
    std::vector<Position> validMoves;
    
    for (const auto& [rowOffset, colOffset] : getMoveOffsets()) {
        Position newPos(m_position.row + rowOffset, m_position.col + colOffset);
        
        // Check if position is within board bounds
        if (!newPos.isValid()) {
            continue;
        }
        
        // Get piece at the target position
        const Piece* targetPiece = board.getPieceAt(newPos);
        
        // Can move to empty square or capture opponent's knight
        if (targetPiece == nullptr || 
            (targetPiece->isKnight() && targetPiece->getColor() != m_color)) {
            validMoves.push_back(newPos);
        }
    }
    
    return validMoves;
}

void Knight::render(SDL_Renderer* renderer, bool isSelected) const {
    int x = Constants::BOARD_OFFSET_X + m_position.col * Constants::SQUARE_SIZE + Constants::SQUARE_SIZE / 2;
    int y = Constants::BOARD_OFFSET_Y + m_position.row * Constants::SQUARE_SIZE + Constants::SQUARE_SIZE / 2;
    int radius = Constants::SQUARE_SIZE / 2 - 10;
    
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
    
    // Draw piece circle
    filledCircleRGBA(renderer, x, y, radius,
                    color.r, color.g, color.b, 255);
    
    // Draw outline
    aacircleRGBA(renderer, x, y, radius,
                outlineColor.r, outlineColor.g, outlineColor.b, 255);
    
    // Draw knight symbol (X)
    SDL_Color symbolColor = m_color == PlayerColor::White ? 
                           SDL_Color{0, 0, 0, 255} : 
                           SDL_Color{255, 255, 255, 255};
    
    // Draw an X inside the circle to represent a knight
    int offset = radius / 2;
    thickLineRGBA(renderer, x - offset, y - offset, x + offset, y + offset, 
                 3, symbolColor.r, symbolColor.g, symbolColor.b, 255);
    thickLineRGBA(renderer, x + offset, y - offset, x - offset, y + offset, 
                 3, symbolColor.r, symbolColor.g, symbolColor.b, 255);
}
