#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame {
	enum class PlayerDirection : int {
		Up,
		Right,
		Down,
		Left,
	};

	struct Player {
		Position2D position;
		float speed = INITIAL_SPEED;
		PlayerDirection direction = PlayerDirection::Right;
		sf::Sprite sprite;
		bool isMoving = true;
	};

	struct Game;
	struct UI;

	void InitPlayer(Player& player, const Game& game);
	void DrawPlayer(Player& player, sf::RenderWindow& window);
	void TurnPlayer(Player& player, const PlayerDirection direction);
	void MovePlayer(Player& player, const float deltaTime);
	bool IsPlayerCollideScreenBound(const Player & player);
	void ResetPlayer(Player& player);
}