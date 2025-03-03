#include "Piece.h"

Piece::Piece(PlayerColor color, Position position)
    : m_color(color), m_position(position)
{
}

std::string Piece::toString() const {
    std::string typeStr = isKnight() ? "Knight" : "Stone";
    std::string colorStr = m_color == PlayerColor::White ? "White" : "Black";
    return colorStr + " " + typeStr + " at " + m_position.toString();
}
