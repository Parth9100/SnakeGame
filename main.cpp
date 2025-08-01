#include <iostream>
#include "raylib.h"
#include <deque>
#include <raymath.h>
#include "StartMenu.h"

using namespace std;

Color gameboyGreen = { 139, 172, 15, 255 };
Color mediumGreen = { 48, 98, 48, 255 };

float cellSize = 30, cellCount = 25, offSet = 75;

double lastUpdateTime = 0;

bool elementInDeque(Vector2 element, deque<Vector2> deque) {
    for (unsigned int i = 0; i < deque.size(); i++) {
        if (Vector2Equals(deque[i], element)) {
            return true;
        }
    }
    return false;
}

bool eventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake {
public:
    deque<Vector2> body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
    Vector2 direction = { 1, 0 };
    bool addSegment = false;

    void Draw() {
        for (unsigned int i = 0; i < body.size(); i++) {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{ offSet + x * cellSize, offSet + y * cellSize, (float)cellSize, (float)cellSize };
            DrawRectangleRounded(segment, 0.5, 6, mediumGreen);
        }
    }

    void Update() {
        body.push_front(Vector2Add(body[0], direction));
        if (addSegment == true) {
            addSegment = false;
        }
        else {
            body.pop_back();
        }
    }

    void Reset() {
        body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
        direction = { 1, 0 };
    }
};

class Food {
public:
    Vector2 position;
    Texture2D texture;

    Food(deque<Vector2> snakeBody) {
        Image image = LoadImage("C:/Users/Parth/Downloads/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = generateRandomPos(snakeBody);
    }

    ~Food() {
        UnloadTexture(texture);
    }

    void Draw() {
        DrawTexture(texture, static_cast<int>(offSet + position.x * cellSize), static_cast<int>(offSet + position.y * cellSize), mediumGreen);
    }

    Vector2 generateRandomCell() {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{ x, y };
    }

    Vector2 generateRandomPos(deque<Vector2> snakeBody) {
        Vector2 position = generateRandomCell();
        while (elementInDeque(position, snakeBody)) {
            position = generateRandomCell();
        }
        return position;
    }
};

class Game {
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;
    Sound eatSound, wallSound;

    Game() {
        InitAudioDevice();
        eatSound = LoadSound("C:/Users/Parth/Downloads/eat.mp3");
        wallSound = LoadSound("C:/Users/Parth/Downloads/wall.mp3");
    }

    ~Game() {
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }

    void Draw() {
        food.Draw();
        snake.Draw();
    }

    void Update() {
        if (running) {
            snake.Update();
            checkCollisionWithFood();
            checkCollisionWithEdge();
            checkCollisionWithTail();
        }
    }

    void checkCollisionWithFood() {
        if (Vector2Equals(snake.body[0], food.position)) {
            food.position = food.generateRandomPos(snake.body);
            snake.addSegment = true;
            score++;
            PlaySound(eatSound);
        }
    }

    void checkCollisionWithEdge() {
        if (snake.body[0].x == cellCount || snake.body[0].x == -1) {
            gameOver();
        }
        if (snake.body[0].y == cellCount || snake.body[0].y == -1) {
            gameOver();
        }
    }

    void checkCollisionWithTail() {
        deque<Vector2> headLessBody = snake.body;
        headLessBody.pop_front();
        if (elementInDeque(snake.body[0], headLessBody)) {
            gameOver();
        }
    }

    void gameOver() {
        snake.Reset();
        food.position = food.generateRandomPos(snake.body);
        running = false;
        score = 0;
        PlaySound(wallSound);
    }

    void Reset() {
        snake.Reset();
        food.position = food.generateRandomPos(snake.body);
        running = true;
        score = 0;
    }
};

int main() {
    InitWindow(2 * offSet + cellSize * cellCount, 2 * offSet + cellSize * cellCount, "The Snake Game");
    SetTargetFPS(60);

    Game game = Game();
    StartMenu menu = StartMenu();
    gameState currentState = MENU;

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(gameboyGreen);

        switch (currentState) {
        case MENU: {
            menu.Update();
            menu.Draw();
            int menuChoice = menu.HandleInput();
            
            if (menuChoice == StartMenu::PLAY) {
                currentState = PLAYING;
                game.Reset();
            }

            else if (menuChoice == StartMenu::QUIT) {
                CloseWindow();
                return 0;
            }
            break;
        }

        case PLAYING: {
            if (eventTriggered(0.18)) {
                game.Update();
            }
            
            if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
                game.snake.direction = { 0, -1 };
                game.running = true;
            }
            
            if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
                game.snake.direction = { 0, 1 };
                game.running = true;
            }
            
            if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
                game.snake.direction = { -1, 0 };
                game.running = true;
            }
            
            if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
                game.snake.direction = { 1, 0 };
                game.running = true;
            }
            
            if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) {
                currentState = PAUSED;
            }
            
            DrawRectangleLinesEx(Rectangle{ offSet - 5, offSet - 5, cellSize * cellCount + 10, cellSize * cellCount + 10 }, 5, mediumGreen);
            DrawText("Retro Snake", offSet - 5, 20, 60, mediumGreen);
            DrawText(TextFormat("Score: %i", game.score), offSet - 5, offSet + cellSize * cellCount + 10, 60, mediumGreen);
            
            game.Draw();
            if (!game.running) {
                currentState = GAME_OVER;
            }
            break;
        }
        case GAME_OVER: {
            DrawRectangleLinesEx(Rectangle{ offSet - 5, offSet - 5, cellSize * cellCount + 10, cellSize * cellCount + 10 }, 5, mediumGreen);
            DrawText("Retro Snake", offSet - 5, 20, 60, mediumGreen);
            DrawText(TextFormat("Score: %i", game.score), offSet - 5, offSet + cellSize * cellCount + 10, 60, mediumGreen);
            
            game.Draw();
            
            int screenWidth = 2 * offSet + cellSize * cellCount;
            int screenHeight = 2 * offSet + cellSize * cellCount;
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));
            
            const char* gameOverText = "GAME OVER";
            int gameOverFontSize = 60;
            int gameOverWidth = MeasureText(gameOverText, gameOverFontSize);
            DrawText(gameOverText, (screenWidth - gameOverWidth) / 2, screenHeight / 2 - 60, gameOverFontSize, RED);
            
            const char* finalScoreText = TextFormat("Final Score: %i", game.score);
            int scoreFontSize = 35;
            int scoreWidth = MeasureText(finalScoreText, scoreFontSize);
            DrawText(finalScoreText, (screenWidth - scoreWidth) / 2, screenHeight / 2 - 10, scoreFontSize, WHITE);
            
            const char* restartText = "Press ENTER to return to menu";
            int restartFontSize = 28;
            int restartWidth = MeasureText(restartText, restartFontSize);
            DrawText(restartText, (screenWidth - restartWidth) / 2, screenHeight / 2 + 40, restartFontSize, WHITE);
            if (IsKeyPressed(KEY_ENTER)) {
                currentState = MENU;
                menu.Reset();
            }
            break;
        }
        case PAUSED: {
            DrawRectangleLinesEx(Rectangle{ offSet - 5, offSet - 5, cellSize * cellCount + 10, cellSize * cellCount + 10 }, 5, mediumGreen);
            DrawText("Retro Snake", offSet - 5, 20, 60, mediumGreen);
            DrawText(TextFormat("Score: %i", game.score), offSet - 5, offSet + cellSize * cellCount + 10, 60, mediumGreen);
            game.Draw();
            
            int screenWidth = 2 * offSet + cellSize * cellCount;
            int screenHeight = 2 * offSet + cellSize * cellCount;
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));
            
            const char* pausedText = "PAUSED";
            int pausedFontSize = 60;
            int pausedWidth = MeasureText(pausedText, pausedFontSize);
            DrawText(pausedText, (screenWidth - pausedWidth) / 2, screenHeight / 2 - 30, pausedFontSize, WHITE);
            
            const char* resumeText = "Press P or ESC to resume";
            int resumeFontSize = 28;
            int resumeWidth = MeasureText(resumeText, resumeFontSize);
            DrawText(resumeText, (screenWidth - resumeWidth) / 2, screenHeight / 2 + 20, resumeFontSize, WHITE);
            
            if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) {
                currentState = PLAYING;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                currentState = MENU;
                menu.Reset();
            }
            break;
        }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}