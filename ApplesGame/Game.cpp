#include "Game.h"
#include <cassert>
#include <iostream>

namespace ApplesGame {
	void InitGame(Game& game) {
		InitUI(game.ui);

		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
		assert(game.stoneTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));

		assert(game.ui.mainThemeMusic.openFromFile(RESOURCES_PATH + "MainTheme.wav"));

		assert(game.ui.appleEatenSoundSource.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(game.ui.gameOverSoundSource.loadFromFile(RESOURCES_PATH + "Death.wav"));
		assert(game.ui.gameWonSoundSource.loadFromFile(RESOURCES_PATH + "GameWon.wav"));
		game.ui.appleEatenSound.setBuffer(game.ui.appleEatenSoundSource);
		game.ui.gameOverSound.setBuffer(game.ui.gameOverSoundSource);
		game.ui.gameWonSound.setBuffer(game.ui.gameWonSoundSource);

		game.lastShownStoneIndex = -1;
		game.applesBeforeNextStone = 5 + int(rand() / (float)RAND_MAX * 10.f);
		game.openedCountdownTillNextStone = false; // need to limit showing stones when condition is met

		InitPlayer(game.player, game);

		SetMainMenuUI(game.ui);
	}
	void InitGameplay(Game& game) {
		game.ui.gameState = GameStates::GamePlay;

		const int minApplesCount = game.ui.selectedModes & 1 << GameModes::Infinite ? MIN_NUM_APPLES_INFINITE : MIN_NUM_APPLES_FINITE;
		const int maxApplesCount = game.ui.selectedModes & 1 << GameModes::Infinite ? MAX_NUM_APPLES_INFINITE : MAX_NUM_APPLES_FINITE;
		game.numApples = minApplesCount + int(rand() / (float)RAND_MAX * (maxApplesCount - minApplesCount));

		if (!game.ui.isMute)
			game.ui.mainThemeMusic.setVolume(30.f); // change behaviour to variable

		game.player.isMoving = true;

		for (int i = 0; i < game.numApples; i++) {
			InitApple(game.apples[i], game);
		}
		game.lastShownStoneIndex = -1;
		for (int i = 0; i < NUM_STONES; i++) {
			InitStone(game.stones[i], game);
			if (!(game.ui.selectedModes & 1 << GameModes::Infinite)) ShowStone(game);
		}
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

		// Keyboard button press handler
		KeyboardButtonsPressHandler(game, window);
		// Mouse hover event handler
		MouseHoverHandler(game, window);
		// Click event handler
		MouseClickHandler(game, window);

		// Change player position
		if (game.player.isMoving) {
			MovePlayer(game.player, deltaTime, game.ui.selectedModes);
			// Eat apple check
			for (int i = 0; i < game.numApples; i++) {
				if (isCirclesCollide(game.apples[i].position, game.player.position, APPLE_SIZE, PLAYER_SIZE) &&
					!game.apples[i].isEaten) {
					EatApple(game.apples[i], game);
					if (!(game.ui.selectedModes & 1 << GameModes::Infinite) && game.ui.numEatenApples == game.numApples) {
						game.ui.isGameWon = true;
						SetGameOver(game);
					}
				}
			}
			// Stone collide check
			for (int i = 0; i < NUM_STONES; i++) {
				if (isCirclesCollide(game.stones[i].position, game.player.position, STONE_SIZE, PLAYER_SIZE) &&
					(game.stones[i].isShown)) {
 					SetGameOver(game);
				}
			}
		}

		// Show stone if enough apples are eaten
		if (IsStoneCooldownReached(game)) {
			ShowStone(game);
		}
		// Check in bound
		if (IsPlayerCollideScreenBound(game.player)) {
			if (!(game.ui.selectedModes & 1 << GameModes::OpenSpace)) SetGameOver(game);
		}
	}

	void DrawGameScene(Game& game, sf::RenderWindow& window) {
		window.clear();
		if (game.ui.gameState == GameStates::GamePlay) {
			// Redraw scene
			DrawPlayer(game.player, window);
			for (int i = 0; i < game.numApples; i++) {
				if (!game.apples[i].isEaten && game.apples[i].isVisible) window.draw(game.apples[i].sprite);
			}
			for (int i = 0; i < NUM_STONES; i++) {
				if (game.stones[i].isShown || !(game.ui.selectedModes & 1 << GameModes::Infinite)) window.draw(game.stones[i].sprite);
			}
		}
		DrawUI(game.ui, window);
		window.display();
	}
	void SetGameOver(Game& game) {
		if (game.ui.gameState == GameStates::GameOver) return;

		if (game.ui.appleEatenSound.getStatus() == sf::SoundSource::Playing) game.ui.appleEatenSound.stop();
		if (game.ui.isGameWon) game.ui.gameWonSound.play();
		else game.ui.gameOverSound.play();
		game.player.isMoving = false;
		SetGameOverUI(game.ui);
	}
	void ResetGame(Game& game) {
		if (game.ui.gameOverSound.getStatus() == sf::SoundSource::Playing) game.ui.gameOverSound.stop();

		for (int i = 0; i < game.numApples; i++) {
			game.apples[i].isVisible = false;
		}

		ResetUI(game.ui);
		ResetPlayer(game.player);
		InitGameplay(game);
	}
	void ToMainMenu(Game& game) {
		game.ui.menuState = GameModes::Infinite;
		game.ui.selectedModes = 0;
		game.ui.gameState = GameStates::MainMenu;
		ResetUI(game.ui);
		ResetPlayer(game.player);
		SetMainMenuUI(game.ui);
	}
	void ToModeSelect(Game& game) {
		game.ui.menuState = GameModes::Infinite;
		game.ui.selectedModes = 0;
		game.ui.gameState = GameStates::ModeSelect;
		ResetUI(game.ui);
		ResetPlayer(game.player);
		SetModeSelectUI(game.ui);
	}
	void ToControls(Game& game) {
	}
	float RecalculateTime(Game& game, const sf::Clock & gameClock) {
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - game.lastTime;
		game.lastTime = currentTime;
		return deltaTime;
	}
	void CloseGame(sf::RenderWindow& window) {
		window.close();
	}

	void KeyboardButtonsPressHandler(Game& game, sf::RenderWindow& window) {
		// "Escape" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Escape]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Escape] = true;
				if (game.ui.gameState == GameStates::ModeSelect) ToMainMenu(game);
				else if (game.ui.gameState == GameStates::GameOver) ToMainMenu(game);
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Escape] = false;

		// "Space" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Space]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Space] = true;
				// Mode select menu action perform
				if (game.ui.gameState == GameStates::ModeSelect) {
					if (game.ui.modeMenu[0].isActive) {
						SelectMode(game.ui, 0);
					}
					else if (game.ui.modeMenu[1].isActive) {
						SelectMode(game.ui, 1);
					}
					else if (game.ui.modeMenu[2].isActive) {
						SelectMode(game.ui, 2);
					}
					else if (game.ui.modeMenu[3].isActive) {
						InitGameplay(game);
						game.ui.modeMenu[3].isActive = false;
					}
					else {
						SelectMode(game.ui, 0);
					}
				}
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Space] = false;

		// "Enter" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Enter]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Enter] = true;
				// Main menu action perform
				if (game.ui.gameState == GameStates::MainMenu) {
					if (game.ui.mainMenu[0].isActive) {
						ToModeSelect(game);
						game.ui.mainMenu[0].isActive = false;
					}
					else if (game.ui.mainMenu[1].isActive) {
						ToControls(game);
						game.ui.mainMenu[1].isActive = false;
					}
					else if (game.ui.mainMenu[2].isActive) CloseGame(window);
				}
				// Mode select menu action perform
				else if (game.ui.gameState == GameStates::ModeSelect) {
					if (game.ui.modeMenu[0].isActive) {
						SelectMode(game.ui, 0);
					}
					else if (game.ui.modeMenu[1].isActive) {
						SelectMode(game.ui, 1);
					}
					else if (game.ui.modeMenu[2].isActive) {
						SelectMode(game.ui, 2);
					}
					else if (game.ui.modeMenu[3].isActive) {
						InitGameplay(game);
						game.ui.modeMenu[3].isActive = false;
					}
					else {
						SelectMode(game.ui, 0);
					}
				}
				// Game over menu action perform
				else if (game.ui.gameState == GameStates::GameOver) {
					if (game.ui.gameOverMenu[0].isActive) {
						ResetGame(game);
						game.ui.gameOverMenu[0].isActive = false;
					}
					else if (game.ui.gameOverMenu[1].isActive) {
						ToModeSelect(game);
						game.ui.gameOverMenu[1].isActive = false;
					}
					else if (game.ui.gameOverMenu[2].isActive) {
						ToMainMenu(game);
						game.ui.gameOverMenu[2].isActive = false;
					}
					else if (game.ui.gameOverMenu[3].isActive) CloseGame(window);
				}
				// To main menu
				else if (game.ui.gameState == GameStates::GameOver) ToMainMenu(game);
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Enter] = false;

		// "R" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::R]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::R] = true;
				// Restart game
				if (game.ui.gameState == GameStates::GamePlay) ResetGame(game);
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::R] = false;

		// "M" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::M]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::M] = true;
				ChangeMuteStatus(game.ui); // Mute game
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::M] = false;

		// "Y" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Y]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Y] = true;
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Y] = false;

		// "N" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::N]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::N] = true;
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::N] = false;

		// "Num1" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Num1]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Num1] = true;
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Num1] = false;

		// "Num2" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Num2]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Num2] = true;
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Num2] = false;

		// "Numpad1" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Numpad1]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Numpad1] = true;
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Numpad1] = false;

		// "Numpad2" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Numpad2]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Numpad2] = true;
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Numpad2] = false;

		// "Up arrow" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Up]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Up] = true;
				// Main menu prev
				if (game.ui.gameState == GameStates::MainMenu) {
					if (game.ui.mainMenu[0].isActive) {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[2]);
					}
					/*else if (game.ui.mainMenu[1].isActive) {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[0]);
					}*/
					else if (game.ui.mainMenu[2].isActive) {
						// Change to this after "Controls page will be prepared"
						//SetMainMenuItemActive(game.ui, game.ui.mainMenu[1]);
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[0]);
					}
					else {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[0]);
					}
				}
				// Mode menu prev
				else if (game.ui.gameState == GameStates::ModeSelect) {
					if (game.ui.modeMenu[0].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[3]);
					}
					else if (game.ui.modeMenu[1].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[0]);
					}
					else if (game.ui.modeMenu[2].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[1]);
					}
					else if (game.ui.modeMenu[3].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[2]);
					}
					else {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[0]);
					}
				}
				// Turn player up
				else if (game.ui.gameState == GameStates::GamePlay) TurnPlayer(game.player, PlayerDirection::Up);
				// Game over menu prev
				else if (game.ui.gameState == GameStates::GameOver) {
					if (game.ui.gameOverMenu[0].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[3]);
					}
					else if (game.ui.gameOverMenu[1].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[0]);
					}
					else if (game.ui.gameOverMenu[2].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[1]);
					}
					else if (game.ui.gameOverMenu[3].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[2]);
					}
					else {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[0]);
					}
				}
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Up] = false;

		// "Left arrow" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Left]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Left] = true;
				// Turn player left
				if (game.ui.gameState == GameStates::GamePlay) TurnPlayer(game.player, PlayerDirection::Left);
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Left] = false;

		// "Down arrow" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Down]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Down] = true;
				// Main menu next
				if (game.ui.gameState == GameStates::MainMenu) {
					if (game.ui.mainMenu[0].isActive) {
						// Change to this after "Controls page will be prepared"
						//SetMainMenuItemActive(game.ui, game.ui.mainMenu[1]);
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[2]);
					}
					/*else if (game.ui.mainMenu[1].isActive) {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[2]);
					}*/
					else if (game.ui.mainMenu[2].isActive) {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[0]);
					}
					else {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[0]);
					}
				}
				// Mode menu next
				else if (game.ui.gameState == GameStates::ModeSelect) {
					if (game.ui.modeMenu[0].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[1]);
					}
					else if (game.ui.modeMenu[1].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[2]);
					}
					else if (game.ui.modeMenu[2].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[3]);
					}
					else if (game.ui.modeMenu[3].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[0]);
					}
					else {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[0]);
					}
				}
				// Turn player down
				else if (game.ui.gameState == GameStates::GamePlay) TurnPlayer(game.player, PlayerDirection::Down);
				// Game over menu next
				else if (game.ui.gameState == GameStates::GameOver) {
					if (game.ui.gameOverMenu[0].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[1]);
					}
					else if (game.ui.gameOverMenu[1].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[2]);
					}
					else if (game.ui.gameOverMenu[2].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[3]);
					}
					else if (game.ui.gameOverMenu[3].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[0]);
					}
					else {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[0]);
					}
				}
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Down] = false;

		// "Right arrow" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::Right]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::Right] = true;
				// Turn player right
				if (game.ui.gameState == GameStates::GamePlay) TurnPlayer(game.player, PlayerDirection::Right);
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::Right] = false;

		// "W" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::W]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::W] = true;
				// Main menu prev
				if (game.ui.gameState == GameStates::MainMenu) {
					if (game.ui.mainMenu[0].isActive) {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[2]);
					}
					else if (game.ui.mainMenu[1].isActive) {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[0]);
					}
					else if (game.ui.mainMenu[2].isActive) {
						// Change to this after "Controls page will be prepared"
						//SetMainMenuItemActive(game.ui, game.ui.mainMenu[1]);
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[0]);
					}
					else {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[0]);
					}
				}
				// Mode menu prev
				else if (game.ui.gameState == GameStates::ModeSelect) {
					if (game.ui.modeMenu[0].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[3]);
					}
					else if (game.ui.modeMenu[1].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[0]);
					}
					else if (game.ui.modeMenu[2].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[1]);
					}
					else if (game.ui.modeMenu[3].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[2]);
					}
					else {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[0]);
					}
				}
				// Turn player up
				else if (game.ui.gameState == GameStates::GamePlay) TurnPlayer(game.player, PlayerDirection::Up);
				// Game over menu prev
				else if (game.ui.gameState == GameStates::GameOver) {
					if (game.ui.gameOverMenu[0].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[3]);
					}
					else if (game.ui.gameOverMenu[1].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[0]);
					}
					else if (game.ui.gameOverMenu[2].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[1]);
					}
					else if (game.ui.gameOverMenu[3].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[2]);
					}
					else {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[0]);
					}
				}
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::W] = false;

		// "A" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::A]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::A] = true;
				// Turn player left
				if (game.ui.gameState == GameStates::GamePlay) TurnPlayer(game.player, PlayerDirection::Left);
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::A] = false;

		// "S" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::S]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::S] = true;
				// Main menu next
				if (game.ui.gameState == GameStates::MainMenu) {
					if (game.ui.mainMenu[0].isActive) {
						// Change to this after "Controls page will be prepared"
						//SetMainMenuItemActive(game.ui, game.ui.mainMenu[1]);
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[2]);
					}
					/*else if (game.ui.mainMenu[1].isActive) {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[2]);
					}*/
					else if (game.ui.mainMenu[2].isActive) {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[0]);
					}
					else {
						SetMainMenuItemActive(game.ui, game.ui.mainMenu[0]);
					}
				}
				// Mode menu next
				else if (game.ui.gameState == GameStates::ModeSelect) {
					if (game.ui.modeMenu[0].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[1]);
					}
					else if (game.ui.modeMenu[1].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[2]);
					}
					else if (game.ui.modeMenu[2].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[3]);
					}
					else if (game.ui.modeMenu[3].isActive) {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[0]);
					}
					else {
						SetModeMenuItemActive(game.ui, game.ui.modeMenu[0]);
					}
				}
				// Turn player down
				else if (game.ui.gameState == GameStates::GamePlay) TurnPlayer(game.player, PlayerDirection::Down);
				// Game over menu next
				else if (game.ui.gameState == GameStates::GameOver) {
					if (game.ui.gameOverMenu[0].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[1]);
					}
					else if (game.ui.gameOverMenu[1].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[2]);
					}
					else if (game.ui.gameOverMenu[2].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[3]);
					}
					else if (game.ui.gameOverMenu[3].isActive) {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[0]);
					}
					else {
						SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[0]);
					}
				}
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::S] = false;

		// "D" button handler
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (!game.ui.keyboardButtonStatus[sf::Keyboard::D]) {
				game.ui.keyboardButtonStatus[sf::Keyboard::D] = true;
				// Turn player right
				if (game.ui.gameState == GameStates::GamePlay) TurnPlayer(game.player, PlayerDirection::Right);
			}
		}
		else game.ui.keyboardButtonStatus[sf::Keyboard::D] = false;
	}
	void MouseHoverHandler(Game& game, sf::RenderWindow& window) {
		const sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		if (game.ui.gameState == GameStates::MainMenu) {
			if (CheckPointerOnItem(localPosition, game.ui.mainMenu[0].text.getGlobalBounds()) && !game.ui.mainMenu[0].isActive) {
				SetMainMenuItemActive(game.ui, game.ui.mainMenu[0]);
			}
			/*else if (CheckPointerOnItem(localPosition, game.ui.mainMenu[1].text.getGlobalBounds()) && !game.ui.mainMenu[1].isActive) {
				SetMainMenuItemActive(game.ui, game.ui.mainMenu[1]);
			}*/
			else if (CheckPointerOnItem(localPosition, game.ui.mainMenu[2].text.getGlobalBounds()) && !game.ui.mainMenu[2].isActive) {
				SetMainMenuItemActive(game.ui, game.ui.mainMenu[2]);
			}
		}
		else if (game.ui.gameState == GameStates::ModeSelect) {
			if (CheckPointerOnItem(localPosition, game.ui.modeMenu[0].text.getGlobalBounds()) && !game.ui.modeMenu[0].isActive) {
				SetModeMenuItemActive(game.ui, game.ui.modeMenu[0]);
			}
			else if (CheckPointerOnItem(localPosition, game.ui.modeMenu[1].text.getGlobalBounds()) && !game.ui.modeMenu[1].isActive) {
				SetModeMenuItemActive(game.ui, game.ui.modeMenu[1]);
			}
			else if (CheckPointerOnItem(localPosition, game.ui.modeMenu[2].text.getGlobalBounds()) && !game.ui.modeMenu[2].isActive) {
				SetModeMenuItemActive(game.ui, game.ui.modeMenu[2]);
			}
			else if (CheckPointerOnItem(localPosition, game.ui.modeMenu[3].text.getGlobalBounds()) && !game.ui.modeMenu[3].isActive) {
				SetModeMenuItemActive(game.ui, game.ui.modeMenu[3]);
			}
		}
		if (game.ui.gameState == GameStates::GameOver) {
			if (CheckPointerOnItem(localPosition, game.ui.gameOverMenu[0].text.getGlobalBounds()) && !game.ui.gameOverMenu[0].isActive) {
				SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[0]);
			}
			else if (CheckPointerOnItem(localPosition, game.ui.gameOverMenu[1].text.getGlobalBounds()) && !game.ui.gameOverMenu[1].isActive) {
				SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[1]);
			}
			else if (CheckPointerOnItem(localPosition, game.ui.gameOverMenu[2].text.getGlobalBounds()) && !game.ui.gameOverMenu[2].isActive) {
				SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[2]);
			}
			else if (CheckPointerOnItem(localPosition, game.ui.gameOverMenu[3].text.getGlobalBounds()) && !game.ui.gameOverMenu[3].isActive) {
				SetGameOverMenuItemActive(game.ui, game.ui.gameOverMenu[3]);
			}
		}
	}
	void MouseClickHandler(Game& game, sf::RenderWindow& window) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			// Check if mouse is clicked because of using in loop
			if (!game.ui.isMouseClicked) {
				game.ui.isMouseClicked = true;
				const sf::Vector2i localPosition = sf::Mouse::getPosition(window);

				// Click on mute/unmute icon
				if (CheckPointerOnItem(localPosition, game.ui.muteStatusIconSprite.getGlobalBounds())) ChangeMuteStatus(game.ui);

				// Main menu actions
				if (game.ui.gameState == GameStates::MainMenu) {
					if (game.ui.mainMenu[0].isActive) {
						ToModeSelect(game);
						game.ui.mainMenu[0].isActive = false;
					}
					else if (game.ui.mainMenu[1].isActive) {
						ToControls(game);
						game.ui.mainMenu[1].isActive = false;
					}
					else if (game.ui.mainMenu[2].isActive) {
						CloseGame(window);
					}
				}
				// Select game modes in menu
				if (game.ui.gameState == GameStates::ModeSelect) {
					if (game.ui.modeMenu[0].isActive) {
						SelectMode(game.ui, 0);
					}
					else if (game.ui.modeMenu[1].isActive) {
						SelectMode(game.ui, 1);
					}
					else if (game.ui.modeMenu[2].isActive) {
						SelectMode(game.ui, 2);
					}
					else if (game.ui.modeMenu[3].isActive) {
						InitGameplay(game);
						game.ui.modeMenu[3].isActive = false;
					}
				}
				// Menu after game over
				if (game.ui.gameState == GameStates::GameOver) {
					if (game.ui.gameOverMenu[0].isActive) {
						ResetGame(game);
						game.ui.gameOverMenu[0].isActive = false;
					}
					else if (game.ui.gameOverMenu[1].isActive) {
						ToModeSelect(game);
						game.ui.gameOverMenu[1].isActive = false;
					}
					else if (game.ui.gameOverMenu[2].isActive) {
						ToMainMenu(game);
						game.ui.gameOverMenu[2].isActive = false;
					}
					else if (game.ui.gameOverMenu[3].isActive) window.close();
				}
			}
		}
		else game.ui.isMouseClicked = false;
	}

	void PauseGame(Game& game) {
		game.isGamePaused = !game.isGamePaused;
		game.player.isMoving = !game.player.isMoving;
	}
}
