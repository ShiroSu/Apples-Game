#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame {
	struct Apple {
		Position2D position;
		sf::Sprite sprite;

		void placeApple() {
			const Position2D newPosition = getRandomPosition(SCREEN_WIDTH, SCREEN_HEIGHT, APPLE_SIZE);
			position = newPosition;
			sprite.setPosition(newPosition.x, newPosition.y);
		}
		bool isCollide(Position2D& playerPosition) const {
			float squareDistance = (playerPosition.x - position.x) * (playerPosition.x - position.x) + (playerPosition.y - position.y) * (playerPosition.y - position.y);
			float sqareRadiusSum = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4.f;
			return squareDistance < sqareRadiusSum;
		}
	};

	struct Game;

	void InitApple(Apple& apple, const Game& game);
	void EatApple(Apple& apple, Game& game);
}
