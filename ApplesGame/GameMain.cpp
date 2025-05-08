// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include <cassert>

int main()
{
	using namespace ApplesGame;

	int seed = (int)time(nullptr);
	srand(seed);
	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
	// Init game clocks
	sf::Clock gameClock;
	// Init game
	Game game;
	InitGame(game);
	game.lastTime = gameClock.getElapsedTime().asSeconds();

	// Init player state
	float playerX = SCREEN_WIDTH / 2.f;
	float playerY = SCREEN_HEIGHT / 2.f;
	float playerSpeed = INITIAL_SPEED;
	PlayerDirection playerDirection = PlayerDirection(Right); // 0-up, 1-right, 2-down, 3-left

	// Init player shape
	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Red);
	playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	playerShape.setPosition(playerX, playerY);

	// Init apples
	float applesX[NUM_APPLES];
	float applesY[NUM_APPLES];
	bool isAppleEaten[NUM_APPLES];
	sf::CircleShape applesShapes[NUM_APPLES];

	// placing apple to random spot
	auto placeApple = [&](int index) {
		applesX[index] = rand() / (float)RAND_MAX * (SCREEN_WIDTH - APPLE_SIZE);
		applesY[index] = rand() / (float)RAND_MAX * (SCREEN_HEIGHT - APPLE_SIZE);
		applesShapes[index].setPosition(applesX[index], applesY[index]);
		};

	for (int i = 0; i < NUM_APPLES; i++) {
		isAppleEaten[i] = false;

		applesShapes[i].setRadius(APPLE_SIZE / 2.f);
		applesShapes[i].setFillColor(sf::Color::Green);
		applesShapes[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		placeApple(i);
	}

	int numEatenApples = 0;

	// Init stones
	float stonesX[NUM_STONES];
	float stonesY[NUM_STONES];
	bool isStoneShown[NUM_STONES];
	sf::CircleShape stonesShapes[NUM_STONES];
	int lastShownStoneIndex = -1;
	int applesBeforeStone = 5 + int(rand() / (float)RAND_MAX * 10.f);
	bool openedCountdownTillNextStone = false; // need to limit showing stones when condition is met

	for (int i = 0; i < NUM_STONES; i++) {
		isStoneShown[i] = false;

		stonesShapes[i].setRadius(STONE_SIZE / 2.f);
		stonesShapes[i].setFillColor(sf::Color::White);
		stonesShapes[i].setOrigin(STONE_SIZE / 2.f, STONE_SIZE / 2.f);
	}


	// loading fonts


	// loading fonts


	// loading fonts


	// loading fonts


	// loading fonts
	sf::Font font;
	assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf"));

	// Apples counter
	game.ui.counterText.setFont(font);
	// Game over text
	game.ui.gameOverText.setFont(font);

	// Main loop
	while (window.isOpen()) {
		sf::sleep(sf::milliseconds(16));
		UpdateGame(game, window, gameClock);
		DrawGameScene(game, window);
	}

	return 0;
}
