#include <SDL2/SDL.h>
#include "GameState.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create game state and run the game
    GameState gameState;
    gameState.run();

    // Quit SDL
    SDL_Quit();

    return 0;
}
