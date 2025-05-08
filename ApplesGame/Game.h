#pragma once
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Stone.h"
#include "UI.h"

namespace ApplesGame {
	struct Game {
		UI ui;
		// player data
		Player player;
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture stoneTexture;

		// apples data
		Apple apples[NUM_APPLES];

		// stones data
		Stone stones[NUM_STONES];
		int lastShownStoneIndex = -1;
		int applesBeforeNextStone = 5 + int(rand() / (float)RAND_MAX * 10.f);
		bool openedCountdownTillNextStone = false; // need to limit showing stones when condition is met

		float lastTime = 0.0f;
	};

	void InitGame(Game& game);
	void UpdateGame(Game& game, sf::RenderWindow& window, sf::Clock& gameClock);
	void DrawGameScene(Game& game, sf::RenderWindow& window);
	void SetGameOver(Game& game);
	void ResetGame(Game& game);
	float RecalculateTime(Game& game, const sf::Clock & gameClock);
}