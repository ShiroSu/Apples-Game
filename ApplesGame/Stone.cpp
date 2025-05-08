#include "Stone.h"
#include "Game.h"

namespace ApplesGame {
	void InitStone(Stone& stone, const Game& game) {
		stone.isShown = false;
		stone.sprite.setTexture(game.stoneTexture);
		setSpriteSize(stone.sprite, STONE_SIZE);
		setSpriteOrigin(stone.sprite, 0.5f, 0.5f);
	}
	bool IsStoneCooldownReached(const Game & game) {
		return (game.openedCountdownTillNextStone && game.ui.numEatenApples > 0 &&
			game.ui.numEatenApples % game.applesBeforeNextStone == 0);
	}
	void ShowStone(Game& game) {
		game.openedCountdownTillNextStone = false;
		game.applesBeforeNextStone = 5 + int(rand() / (float)RAND_MAX * 10.f);
		game.stones[++game.lastShownStoneIndex].setVisible();
	}
}
