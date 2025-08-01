# 🐍 Retro Snake Game

A classic Snake game implementation in C++ using the Raylib graphics library. Experience the nostalgic gameplay with modern features and smooth controls.

![Snake Game](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Raylib](https://img.shields.io/badge/Raylib-FF0000?style=for-the-badge&logo=raylib&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

## 🎮 Features

- **Classic Snake Gameplay**: Navigate the snake to eat food and grow longer
- **Retro Visual Design**: GameBoy-inspired green color scheme
- **Start Menu**: Animated menu with pulsing title and smooth navigation
- **Game States**: Menu, Playing, Paused, and Game Over states
- **Sound Effects**: Audio feedback for eating food and hitting walls
- **Score System**: Track your score as you play
- **Pause Functionality**: Pause and resume gameplay
- **Smooth Controls**: Responsive arrow key controls
- **Collision Detection**: Wall and self-collision detection

## 🎯 Gameplay

- Control the snake using arrow keys
- Eat the food to grow longer and increase your score
- Avoid hitting the walls or your own tail
- Try to achieve the highest score possible!

## 🕹️ Controls

### Menu Navigation
- **Arrow Keys** or **W/S**: Navigate menu options
- **Enter** or **Space**: Select option

### In-Game Controls
- **Arrow Keys**: Control snake direction
- **P** or **Escape**: Pause/Resume game
- **Enter**: Return to menu (when paused or game over)

## 🛠️ Installation

### Prerequisites
- Visual Studio 2019 or later
- Windows 10/11
- Raylib library

### Building the Project

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/SnakeGame.git
   cd SnakeGame
   ```

2. **Open in Visual Studio**
   - Open `SnakeGame.sln` in Visual Studio
   - Build the solution (Ctrl+Shift+B)

3. **Run the Game**
   - Press F5 or click "Start Debugging"
   - The game will launch in a new window

### Required Assets
Make sure you have the following files in your project directory:
- `food.png` - Food texture
- `eat.mp3` - Eating sound effect
- `wall.mp3` - Wall collision sound effect

## 📁 Project Structure

```
SnakeGame/
├── main.cpp              # Main game logic and entry point
├── StartMenu.cpp         # Menu system implementation
├── startMenu.h           # Menu class header
├── SnakeGame.sln         # Visual Studio solution file
├── SnakeGame.vcxproj     # Project configuration
└── README.md            # This file
```

## 🏗️ Architecture

The game is built using object-oriented design with the following main components:

### Core Classes
- **Snake**: Handles snake movement, growth, and rendering
- **Food**: Manages food placement and collision detection
- **Game**: Main game logic, state management, and collision handling
- **StartMenu**: Menu system with animated UI

### Game States
- **MENU**: Start menu with play/quit options
- **PLAYING**: Active gameplay state
- **PAUSED**: Paused game state
- **GAME_OVER**: Game over screen with final score

## 🎨 Visual Design

The game features a retro aesthetic with:
- GameBoy-inspired green color palette
- Rounded rectangle snake segments
- Animated pulsing title in the menu
- Clean, minimalist UI design

## 🔧 Technical Details

- **Language**: C++
- **Graphics Library**: Raylib
- **Audio**: Raylib audio system
- **Platform**: Windows (Visual Studio)
- **Resolution**: Dynamic based on cell size and count
- **Frame Rate**: 60 FPS

## 🚀 Future Enhancements

Potential features for future development:
- [ ] High score system
- [ ] Multiple difficulty levels
- [ ] Power-ups and special food
- [ ] Multiplayer support
- [ ] Custom themes
- [ ] Mobile port

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

## 👨‍💻 Author

Created by [Your Name] - A classic Snake game implementation with modern features.

---

**Enjoy the game! 🐍🎮** 