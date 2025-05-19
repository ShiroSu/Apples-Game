#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame {
	struct Stone {
		bool isShown = false;
		Position2D position;
		sf::Sprite sprite;
	};

	struct Game;

	void SetVisible(Stone& stone);

	void InitStone(Stone& stone, const Game& game);
	bool IsStoneCooldownReached(const Game & game);
	void ShowStone(Game& game);
}
