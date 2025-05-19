#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame {
	struct Apple {
		bool isEaten = false;
		Position2D position;
		sf::Sprite sprite;
	};

	struct Game;

	void InitApple(Apple& apple, const Game& game);
	void EatApple(Apple& apple, Game& game);
	void placeApple(Apple& apple);
}
