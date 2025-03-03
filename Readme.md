# Stone Knights

## Overview

Stone Knights is a strategic board game implemented in C++ using SDL2. The game features an 8x8 grid where players control knights and place stones to create strategic advantages.

See also [GamePlay](GamePlay.md)

## Game Mechanics

### Pieces
- **Knights**: Can move and capture opponent knights
- **Stones**: Placed strategically to block or create capture opportunities

### Basic Rules
- Players take turns moving knights or placing stones
- Knights can capture opponent knights
- Stones can create capture chains

## Prerequisites

### Dependencies
- SDL2
- SDL2_gfx
- SDL2_image
- SDL2_ttf
- CMake (3.16 or higher)
- C++23 compiler

### Installation on Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install \
    libsdl2-dev \
    libsdl2-gfx-dev \
    libsdl2-image-dev \
    libsdl2-ttf-dev \
    cmake \
    build-essential
```

## Building the Project

### Quick Build
```bash
# Clone the repository
git clone https://github.com/yourusername/stone-knights.git
cd stone-knights

# Build using the provided script
./r
```

### Manual Build
```bash
mkdir build
cd build
cmake ..
make
```

## Running the Game
```bash
# After building
./build/bin/StoneKnights
```

## Controls
- **Escape**: Quit the game
- Game controls will be detailed in future updates

## Project Structure
- `src/`: Source code files
- `assets/`: Game assets
- `build/`: Compilation output directory

## Planned Features
- Full game rule implementation
- Multiplayer support
- AI opponent
- Enhanced UI and graphics

## Contributing
1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License
Do what you want.
