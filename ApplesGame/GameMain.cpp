// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include "Game.h"

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
