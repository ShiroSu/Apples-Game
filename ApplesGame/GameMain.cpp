﻿// ©2023, XYZ School. All rights reserved.
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

	// loading fonts
	sf::Font font;
	assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf"));

	// Menu mode texts
	game.ui.modeText.setFont(font);
	game.ui.yesText.setFont(font);
	game.ui.noText.setFont(font);
	// Apples counter
	game.ui.counterText.setFont(font);
	// Game over text
	game.ui.gameOverText.setFont(font);
	// Gameover menu text
	game.ui.gameOverMenuRestartText.setFont(font);
	game.ui.gameOverMenuModeSelectText.setFont(font);
	game.ui.gameOverMenuCloseText.setFont(font);

	// Setting game settings
	InitGame(game);
	game.lastTime = gameClock.getElapsedTime().asSeconds();

	// Main loop
	while (window.isOpen()) {
		sf::sleep(sf::milliseconds(16));
		UpdateGame(game, window, gameClock);
		DrawGameScene(game, window);
	}

	return 0;
}
