#pragma once

namespace Constants {
    constexpr int BOARD_SIZE = 8;
    constexpr int SQUARE_SIZE = 64;
    constexpr int BOARD_OFFSET_X = 50;
    constexpr int BOARD_OFFSET_Y = 50;

    // Square colors
    constexpr int LIGHT_SQUARE_R = 240;
    constexpr int LIGHT_SQUARE_G = 217;
    constexpr int LIGHT_SQUARE_B = 181;

    constexpr int DARK_SQUARE_R = 181;
    constexpr int DARK_SQUARE_G = 136;
    constexpr int DARK_SQUARE_B = 99;

    // Piece colors
    constexpr int WHITE_PIECE_R = 255;
    constexpr int WHITE_PIECE_G = 255;
    constexpr int WHITE_PIECE_B = 255;

    constexpr int BLACK_PIECE_R = 0;
    constexpr int BLACK_PIECE_G = 0;
    constexpr int BLACK_PIECE_B = 0;

    // Piece outline colors
    constexpr int WHITE_OUTLINE_R = 200;
    constexpr int WHITE_OUTLINE_G = 200;
    constexpr int WHITE_OUTLINE_B = 200;

    constexpr int BLACK_OUTLINE_R = 50;
    constexpr int BLACK_OUTLINE_G = 50;
    constexpr int BLACK_OUTLINE_B = 50;

    // Selected square colors
    constexpr int SELECTED_SQUARE_R = 100;
    constexpr int SELECTED_SQUARE_G = 200;
    constexpr int SELECTED_SQUARE_B = 100;
    constexpr int SELECTED_SQUARE_A = 128;

    // Valid move indicator
    constexpr int VALID_MOVE_R = 100;
    constexpr int VALID_MOVE_G = 200;
    constexpr int VALID_MOVE_B = 100;
    constexpr int VALID_MOVE_A = 128;

    // Initial stone count per player
    constexpr int INITIAL_STONE_COUNT = 20;
}
