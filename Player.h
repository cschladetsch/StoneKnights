#pragma once

#include <string>
#include <SDL2/SDL.h>

enum class PlayerColor {
    White,
    Black
};

class Player {
public:
    Player(PlayerColor color);
    
    // Getters
    PlayerColor getColor() const { return m_color; }
    int getStonesLeft() const { return m_stonesLeft; }
    const std::string& getName() const { return m_name; }
    
    // Actions
    void decrementStonesLeft() { if (m_stonesLeft > 0) m_stonesLeft--; }
    void reset();
    
    // Get the color as SDL_Color for rendering
    SDL_Color getSDLColor() const;
    
    // Get the opponent color
    static PlayerColor getOpponent(PlayerColor color) {
        return color == PlayerColor::White ? PlayerColor::Black : PlayerColor::White;
    }
    
    // Convert PlayerColor to string
    static std::string colorToString(PlayerColor color) {
        return color == PlayerColor::White ? "White" : "Black";
    }
    
private:
    PlayerColor m_color;
    std::string m_name;
    int m_stonesLeft;
};
