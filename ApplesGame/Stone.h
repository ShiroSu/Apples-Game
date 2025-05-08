#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame {
	struct Stone {
		Position2D position;
		bool isShown;
		sf::Sprite sprite;

		void setVisible() {
			const Position2D newPosition = getRandomPosition(SCREEN_WIDTH, SCREEN_HEIGHT, STONE_SIZE);
			position = newPosition;
			sprite.setPosition(newPosition.x, newPosition.y);
			isShown = true;
		}
		bool isCollide(Position2D& playerPosition) const {
			if (!isShown) return false;

			float squareDistance = (playerPosition.x - position.x) * (playerPosition.x - position.x) + (playerPosition.y - position.y) * (playerPosition.y - position.y);
			float sqareRadiusSum = (STONE_SIZE + PLAYER_SIZE) * (STONE_SIZE + PLAYER_SIZE) / 4.f;
			return squareDistance < sqareRadiusSum;
		}
	};

	struct Game;

	void InitStone(Stone& stone, const Game& game);
	bool IsStoneCooldownReached(const Game & game);
	void ShowStone(Game& game);
}
