#pragma once

#include <SDL2/SDL.h>
#include "Board.h"
#include "Player.h"

class GameState {
public:
    GameState();
    ~GameState();

    void run();

private:
    // Game components
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    Board m_board;
    Player m_whitePlayer;
    Player m_blackPlayer;

    // Game loop and event handling
    void processEvents();
    void update();
    void render();

    // Initialization helpers
    bool initSDL();
    void cleanup();
};
