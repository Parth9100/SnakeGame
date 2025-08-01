#include "StartMenu.h"
#include <iostream>
#include <raymath.h>

extern Color gameboyGreen;
extern Color mediumGreen;
extern float cellSize, cellCount, offSet;

StartMenu::StartMenu() {
    selectedOption = 0;
    titleScale = 1.0f;
    pulseTimer = 0.0f;
}

StartMenu::~StartMenu() {
}

void StartMenu::Update() {
    pulseTimer += GetFrameTime();
    titleScale = 1.0f + 0.1f * sinf(pulseTimer * 3.0f);

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        selectedOption--;
        if (selectedOption < 0) {
            selectedOption = MENU_OPTIONS_COUNT - 1;
        }
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        selectedOption++;
        if (selectedOption >= MENU_OPTIONS_COUNT) {
            selectedOption = 0;
        }
    }
}

void StartMenu::Draw() {
    int screenWidth = 2 * offSet + cellSize * cellCount;
    int screenHeight = 2 * offSet + cellSize * cellCount;

    const char* title = "RETRO SNAKE";
    int titleFontSize = 80;
    int titleWidth = MeasureText(title, titleFontSize * titleScale);
    DrawText(title, (screenWidth - titleWidth) / 2, screenHeight / 4, titleFontSize * titleScale, mediumGreen);

    const char* subtitle = "Classic Snake Game";
    int subtitleFontSize = 35;
    int subtitleWidth = MeasureText(subtitle, subtitleFontSize);
    DrawText(subtitle, (screenWidth - subtitleWidth) / 2, screenHeight / 4 + 120, subtitleFontSize, mediumGreen);

    const char* menuOptions[] = { "PLAY", "QUIT" };
    int menuFontSize = 50;
    int menuStartY = screenHeight / 2 + 80;
    int menuSpacing = 80;

    for (int i = 0; i < MENU_OPTIONS_COUNT; i++) {
        Color textColor = (i == selectedOption) ? gameboyGreen : mediumGreen;
        int optionWidth = MeasureText(menuOptions[i], menuFontSize);

        if (i == selectedOption) {
            DrawRectangle((screenWidth - optionWidth) / 2 - 30, menuStartY + i * menuSpacing - 8, optionWidth + 60, menuFontSize + 16, mediumGreen);
        }

        DrawText(menuOptions[i], (screenWidth - optionWidth) / 2, menuStartY + i * menuSpacing, menuFontSize, textColor);
    }

    const char* controls = "Use ARROW KEYS to navigate, ENTER to select";
    int controlsFontSize = 24;
    int controlsWidth = MeasureText(controls, controlsFontSize);
    DrawText(controls, (screenWidth - controlsWidth) / 2, screenHeight - 120, controlsFontSize, mediumGreen);
}

int StartMenu::HandleInput() {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        return selectedOption;
    }
    return -1;
}

void StartMenu::Reset() {
    selectedOption = 0;
    titleScale = 1.0f;
    pulseTimer = 0.0f;
}