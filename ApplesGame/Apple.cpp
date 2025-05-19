#include "Apple.h"
#include "Game.h"

namespace ApplesGame {
	void placeApple(Apple& apple) {
		const Position2D newPosition = getRandomPosition(SCREEN_WIDTH, SCREEN_HEIGHT, APPLE_SIZE);
		apple.position = newPosition;
		apple.sprite.setPosition(newPosition.x, newPosition.y);
	}
	void InitApple(Apple& apple, const Game& game) {
		apple.sprite.setTexture(game.appleTexture);
		setSpriteSize(apple.sprite, APPLE_SIZE);
		setSpriteOrigin(apple.sprite, 0.5f, 0.5f);
		placeApple(apple);
		apple.isEaten = false;
	}
	void EatApple(Apple& apple, Game& game) {
		RecalculateCounter(game.ui);

		if (game.selectedModes & 1 << GameModes::AccelWorld) game.player.speed += ACCELERATION;

		if (game.selectedModes & 1 << GameModes::Infinite) {
			game.openedCountdownTillNextStone = game.lastShownStoneIndex < NUM_STONES - 1;
			placeApple(apple);
		}
		else apple.isEaten = true;

		game.ui.appleEatenSound.play();
	}
}
