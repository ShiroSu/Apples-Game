#include "Stone.h"
#include "Game.h"

namespace ApplesGame {
	void SetVisible(Stone& stone) {
		const Position2D newPosition = getRandomPosition(SCREEN_WIDTH, SCREEN_HEIGHT, STONE_SIZE);
		stone.position = newPosition;
		stone.sprite.setPosition(newPosition.x, newPosition.y);
		stone.isShown = true;
	}
	void InitStone(Stone& stone, const Game& game) {
		stone.isShown = !bool(game.selectedModes & 1 << GameModes::Infinite);
		stone.sprite.setTexture(game.stoneTexture);
		setSpriteSize(stone.sprite, STONE_SIZE);
		setSpriteOrigin(stone.sprite, 0.5f, 0.5f);
	}
	bool IsStoneCooldownReached(const Game & game) {
		return (game.openedCountdownTillNextStone && game.ui.numEatenApples > 0 &&
			game.ui.numEatenApples % game.applesBeforeNextStone == 0);
	}
	void ShowStone(Game& game) {
		if (game.selectedModes & 1 << GameModes::Infinite) {
			game.openedCountdownTillNextStone = false;
			game.applesBeforeNextStone = 5 + int(rand() / (float)RAND_MAX * 10.f);
		}
		SetVisible(game.stones[++game.lastShownStoneIndex]);
	}
}
