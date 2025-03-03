#pragma once

#include <cstdint>
#include <functional>
#include <string>

class Position {
public:
    Position() : row(0), col(0) {}
    Position(int r, int c) : row(r), col(c) {}
    
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
    
    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
    
    // For debugging and display
    std::string toString() const {
        return "(" + std::to_string(row) + "," + std::to_string(col) + ")";
    }
    
    // Check if position is valid (within board bounds)
    bool isValid() const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }
    
    int row;
    int col;
};

// Custom hash function for Position to use in unordered containers
namespace std {
    template<>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const {
            return std::hash<int>()(pos.row) ^ (std::hash<int>()(pos.col) << 1);
        }
    };
}
