#include "GameState.h"
#include "Constants.h"
#include <iostream>

GameState::GameState() 
    : m_window(nullptr), 
      m_renderer(nullptr), 
      m_whitePlayer(PlayerColor::White), 
      m_blackPlayer(PlayerColor::Black) 
{
    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
    }
}

GameState::~GameState() {
    cleanup();
}

bool GameState::initSDL() {
    // Create window
    m_window = SDL_CreateWindow(
        "Stone Knights", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        Constants::BOARD_SIZE * Constants::SQUARE_SIZE + 2 * Constants::BOARD_OFFSET_X, 
        Constants::BOARD_SIZE * Constants::SQUARE_SIZE + 2 * Constants::BOARD_OFFSET_Y, 
        SDL_WINDOW_SHOWN
    );
    
    if (!m_window) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void GameState::cleanup() {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}

void GameState::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return;
            
            // Add more event handling as needed
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return;
                }
                break;
        }
    }
}

void GameState::update() {
    // Game logic updates
}

void GameState::render() {
    // Clear screen
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    // Render board
    m_board.render(m_renderer, nullptr, {});

    // Present renderer
    SDL_RenderPresent(m_renderer);
}

void GameState::run() {
    bool quit = false;
    while (!quit) {
        processEvents();
        update();
        render();

        // Cap to ~60 FPS
        SDL_Delay(16);
    }
}
