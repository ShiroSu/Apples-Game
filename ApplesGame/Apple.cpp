#include "Apple.h"
#include "Game.h"

namespace ApplesGame {
	void InitApple(Apple& apple, const Game& game) {
		apple.sprite.setTexture(game.appleTexture);
		setSpriteSize(apple.sprite, APPLE_SIZE);
		setSpriteOrigin(apple.sprite, 0.5f, 0.5f);
		apple.placeApple();
	}
	void EatApple(Apple& apple, Game& game) {
		RecalculateCounter(game.ui);

		game.player.speed += ACCELERATION;
		game.openedCountdownTillNextStone = game.lastShownStoneIndex < NUM_STONES - 1;
		game.ui.appleEatenSound.play();

		apple.placeApple();
	}
}
