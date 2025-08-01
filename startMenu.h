#pragma once
#include "raylib.h"

enum gameState {
	MENU,
	PLAYING,
	GAME_OVER,
	PAUSED
};

class StartMenu {

private:
	int selectedOption;
	float titleScale, pulseTimer;

public:
	StartMenu();
	~StartMenu();

	void Update();
	void Draw();
	int HandleInput();
	void Reset();

	enum MenuOption {
		PLAY = 0,
		QUIT = 1,
		MENU_OPTIONS_COUNT = 2
	};

};