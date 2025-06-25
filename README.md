# Pong Game 🏓

A classic Pong game implemented in C++ using the Raylib graphics library.

## Features

- **Two-player gameplay** with separate controls
- **Real-time collision detection** between ball and paddles
- **Scoring system** that tracks points for both players
- **Start screen** with instructions
- **Smooth 60 FPS gameplay** with VSync
- **Object-oriented design** using C++ structs

## Controls

- **Left Player (Player 1)**: W (up) / S (down)
- **Right Player (Player 2)**: UP Arrow (up) / DOWN Arrow (down)
- **Start Game**: Press any key on the start screen

## Screenshots

*Game in action with scoring display and smooth paddle movement*

## How to Play

1. Run the game executable
2. Press any key to start the game
3. Use your assigned keys to move your paddle up and down
4. Try to hit the ball past your opponent's paddle to score points
5. The game continues indefinitely - first to X points wins (you decide!)

## Technical Details

### Built With
- **Language**: C++
- **Graphics Library**: Raylib 5.5
- **Compiler**: GCC (MinGW-w64)
- **IDE**: Visual Studio Code

### Game Objects
- `Ball`: Handles position, movement, and wall collision
- `Paddle`: Manages player input and paddle movement
- `Score`: Tracks points and handles goal detection
- `CheckCollision()`: Detects ball-paddle collisions

### Key Features
- Frame-rate independent movement using `GetFrameTime()`
- Proper collision detection with bounding boxes
- Ball resets to center after each goal
- Paddles constrained to screen boundaries

## Building from Source

### Prerequisites
- MSYS2 with MinGW-w64
- Raylib library installed
- GCC compiler

### Installation Steps
1. Install MSYS2 and update packages:
   ```bash
   pacman -Syu
   ```

2. Install development tools and Raylib:
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
   pacman -S mingw-w64-ucrt-x86_64-raylib
   ```

3. Clone this repository:
   ```bash
   git clone https://github.com/zl0618/PingPong_Game.git
   cd PingPong_Game
   ```

4. Compile the game:
   ```bash
   gcc -o pingpong pingpong.cpp -lraylib -lopengl32 -lgdi32 -lwinmm
   ```

5. Run the executable:
   ```bash
   ./pingpong.exe
   ```

## Game Logic

The game follows classic Pong rules:
- Ball bounces off top and bottom walls
- Ball bounces off paddles, reversing horizontal direction
- If ball exits left side, right player scores
- If ball exits right side, left player scores
- Ball resets to center after each goal

## Future Enhancements

- [ ] AI opponent for single-player mode
- [ ] Sound effects and background music
- [ ] Particle effects for collisions
- [ ] Different difficulty levels
- [ ] Win condition (first to 10 points)
- [ ] Pause functionality
- [ ] Better graphics and animations

## Contributing

Feel free to fork this project and submit pull requests for any improvements!

## License

This project is open source and available under the [MIT License](LICENSE).

## Author

Created by [zl0618](https://github.com/zl0618) as a learning project for C++ game development.

---

**Enjoy playing Pong!** 🎮