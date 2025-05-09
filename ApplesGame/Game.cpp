#include "Game.h"
#include <cassert>

namespace ApplesGame {
	void InitGame(Game& game) {
		InitUI(game.ui);

		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(game.stoneTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));

		assert(game.ui.appleEatenSoundSource.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(game.ui.gameOverSoundSource.loadFromFile(RESOURCES_PATH + "Death.wav"));
		game.ui.appleEatenSound.setBuffer(game.ui.appleEatenSoundSource);
		game.ui.gameOverSound.setBuffer(game.ui.gameOverSoundSource);

		InitPlayer(game.player, game);

		for (int i = 0; i < NUM_APPLES; i++) {
			InitApple(game.apples[i], game);
		}
		for (int i = 0; i < NUM_STONES; i++) {
			InitStone(game.stones[i], game);
		}

		game.lastShownStoneIndex = -1;
		game.applesBeforeNextStone = 5 + int(rand() / (float)RAND_MAX * 10.f);
		game.openedCountdownTillNextStone = false; // need to limit showing stones when condition is met

	}

	void UpdateGame(Game& game, sf::RenderWindow& window, sf::Clock& gameClock) {
		// Calculate time delta
		const float deltaTime = RecalculateTime(game, gameClock);

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && game.ui.isGameOver) {
			ResetGame(game);
		}

		// Restart button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::R]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::R] = true;
				ResetGame(game);
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::R] = false;

		// Mute button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::M]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::M] = true;
				ChangeMuteStatus(game.ui);
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::M] = false;

		// Player control buttons handler
		if (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			) {
			TurnPlayer(game.player, PlayerDirection::Right);
		}
		else if (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::W)
			) {
			TurnPlayer(game.player, PlayerDirection::Up);
		}
		else if (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::A)
			) {
			TurnPlayer(game.player, PlayerDirection::Left);
		}
		else if (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::S)
			) {
			TurnPlayer(game.player, PlayerDirection::Down);
		}

		// Click event handler
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			// Check if mouse is clicked because of using in loop
			if (!game.ui.isMouseClicked) {
				game.ui.isMouseClicked = true;

				// Click on mute/unmute icon
				const sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				sf::FloatRect spriteBounds = game.ui.muteStatusIconSprite.getLocalBounds();
				const float rangeX[2] = { spriteBounds.left, spriteBounds.left + spriteBounds.width };
				const float rangeY[2] = { spriteBounds.top, spriteBounds.top + spriteBounds.height };
				if (
					((float)rangeX[0] < localPosition.x && localPosition.x < (float)rangeX[1]) &&
					((float)rangeY[0] < localPosition.y && localPosition.y < (float)rangeY[1])
					) ChangeMuteStatus(game.ui);
			}
		}
		else game.ui.isMouseClicked = false;

		// Change player position
		MovePlayer(game.player, deltaTime);

		for (int i = 0; i < NUM_APPLES; i++) {
			if (game.apples[i].isCollide(game.player.position)) {
				EatApple(game.apples[i], game);
			}
		}

		for (int i = 0; i < NUM_STONES; i++) {
			if (game.stones[i].isCollide(game.player.position)) {
				SetGameOver(game);
			}
		}

		// Show stone if enough apples are eaten
		if (IsStoneCooldownReached(game)) {
			ShowStone(game);
		}

		// Check in bound
		if (IsPlayerCollideScreenBound(game.player)) {
			SetGameOver(game);
		}
	}

	void DrawGameScene(Game& game, sf::RenderWindow& window) {
		window.clear();
		if (!game.ui.isGameOver) {
			// Redraw scene
			DrawPlayer(game.player, window);
			for (int i = 0; i < NUM_APPLES; i++) {
				window.draw(game.apples[i].sprite);
			}
			for (int i = 0; i < NUM_STONES; i++) {
				if (game.stones[i].isShown) window.draw(game.stones[i].sprite);
			}
		}
		DrawUI(game.ui, window);
		window.display();
	}
	void SetGameOver(Game& game) {
		if (game.ui.isGameOver) return;

		if (game.ui.appleEatenSound.getStatus() == sf::SoundSource::Playing) game.ui.appleEatenSound.stop();
		game.ui.gameOverSound.play();
		game.player.isMoving = false;
		SetGameOverUI(game.ui);
	}
	void ResetGame(Game& game) {
		if (game.ui.gameOverSound.getStatus() == sf::SoundSource::Playing) game.ui.gameOverSound.stop();

		game.lastShownStoneIndex = -1;
		game.applesBeforeNextStone = 5 + int(rand() / (float)RAND_MAX * 10.f);
		game.openedCountdownTillNextStone = false;
		ResetUI(game.ui);
		ResetPlayer(game.player);

		for (int i = 0; i < NUM_APPLES; i++) {
			game.apples[i].placeApple();
		}
		for (int i = 0; i < NUM_STONES; i++) {
			game.stones[i].isShown = false;
		}
		game.ui.isGameOver = false;
	}
	float RecalculateTime(Game& game, const sf::Clock & gameClock) {
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - game.lastTime;
		game.lastTime = currentTime;
		return deltaTime;
	}
}
