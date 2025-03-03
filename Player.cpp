#include "Player.h"
#include "Constants.h"

Player::Player(PlayerColor color) : 
    m_color(color), 
    m_stonesLeft(Constants::INITIAL_STONE_COUNT) 
{
    m_name = colorToString(color);
}

void Player::reset() {
    m_stonesLeft = Constants::INITIAL_STONE_COUNT;
}

SDL_Color Player::getSDLColor() const {
    if (m_color == PlayerColor::White) {
        return { 
            Constants::WHITE_PIECE_R, 
            Constants::WHITE_PIECE_G, 
            Constants::WHITE_PIECE_B, 
            255 
        };
    } else {
        return { 
            Constants::BLACK_PIECE_R, 
            Constants::BLACK_PIECE_G, 
            Constants::BLACK_PIECE_B, 
            255 
        };
    }
}
