#pragma once
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "UI.h"

namespace ApplesGame {
	struct Game {
		bool isGamePaused = false;

		bool openedCountdownTillNextStone = false; // need to limit showing stones when condition is met
		int lastShownStoneIndex = -1;
		int applesBeforeNextStone = 5 + int(rand() / (float)RAND_MAX * 10.f);

		short selectedModes = 0;
		float lastTime = 0.0f;

		UI ui;
		// player data
		Player player;
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;

		// apples data
		int numApples = 0;
		Apple apples[MAX_NUM_APPLES_FINITE];

		// stones data
		Stone stones[NUM_STONES];
	};

	void InitGame(Game& game);
	void InitGameplay(Game& game);
	void UpdateGame(Game& game, sf::RenderWindow& window, sf::Clock& gameClock);
	void DrawGameScene(Game& game, sf::RenderWindow& window);
	void ChangeMenuState(Game& game, const bool response);
	void SetGameOver(Game& game);
	void ResetGame(Game& game);
	void ToMainMenu(Game& game);
	float RecalculateTime(Game& game, const sf::Clock & gameClock);
	void CloseGame(sf::RenderWindow& window);
	void KeyboardButtonsPressHandler(Game& game, sf::RenderWindow& window);
	void MouseClickHandler(Game& game, sf::RenderWindow& window);
	void PauseGame(Game& game);
}