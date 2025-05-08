#include "Player.h"
#include "Game.h"
#include "UI.h"

namespace ApplesGame {
	void InitPlayer(Player& player, const Game& game) {
		// Init player state
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };

		// Init player shape
		player.sprite.setTexture(game.playerTexture);
		player.sprite.setPosition(player.position.x, player.position.y);
		setSpriteSize(player.sprite, PLAYER_SIZE);
		setSpriteOrigin(player.sprite, 0.5f, 0.5f);
	}
	void DrawPlayer(Player& player, sf::RenderWindow& window) {
		player.sprite.setPosition(player.position.x, player.position.y);
		window.draw(player.sprite);
	}
	void TurnPlayer(Player& player, const PlayerDirection direction) {
		if (player.direction == direction) return;
		player.direction = direction;

		const sf::Vector2f currentScale = player.sprite.getScale();
		switch (direction) {
		case PlayerDirection::Right:
			setSpriteSize(player.sprite, PLAYER_SIZE);
			player.sprite.setRotation(0.f);
			break;
		case PlayerDirection::Left:
			player.sprite.scale(sf::Vector2f(-1, 1));
			player.sprite.setRotation(0.f);
			break;
		case PlayerDirection::Up:
			setSpriteSize(player.sprite, PLAYER_SIZE);
			player.sprite.setRotation(270.f);
			break;
		case PlayerDirection::Down:
			setSpriteSize(player.sprite, PLAYER_SIZE);
			player.sprite.setRotation(90.f);
			break;
		}
	}
	void MovePlayer(Player& player, const float deltaTime) {
		if (!player.isMoving) return;
		switch (player.direction) {
		case PlayerDirection::Right:
			player.position.x += player.speed * deltaTime;
			break;
		case PlayerDirection::Left:
			player.position.x -= player.speed * deltaTime;
			break;
		case PlayerDirection::Up:
			player.position.y -= player.speed * deltaTime;
			break;
		case PlayerDirection::Down:
			player.position.y += player.speed * deltaTime;
			break;
		}
	}
	bool IsPlayerCollideScreenBound(const Player & player)
	{
		return (player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			player.position.x - PLAYER_SIZE / 2.f < 0.f ||
			player.position.y - PLAYER_SIZE / 2.f < 0.f ||
			player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT);
	}
	void ResetPlayer(Player& player) {
		player.speed = INITIAL_SPEED;
		TurnPlayer(player, PlayerDirection::Right);
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.sprite.setPosition(player.position.x, player.position.y);
		player.isMoving = true;
	}
}