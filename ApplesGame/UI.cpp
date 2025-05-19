#include "UI.h"
#include <cassert>

namespace ApplesGame {
	void InitUI(UI& ui) {
		// Sound on/off icons
		assert(ui.soundOnTexture.loadFromFile(RESOURCES_PATH + "Sound_on.png"));
		assert(ui.soundOffTexture.loadFromFile(RESOURCES_PATH + "Sound_off.png"));
		ui.soundOffTexture.setSmooth(true);
		ui.soundOnTexture.setSmooth(true);
		SetMuteStatus(ui);
		setSpriteSize(ui.muteStatusIconSprite, SOUND_ICON_SIZE);
		ui.muteStatusIconSprite.setPosition(SCREEN_WIDTH - 10 - ui.muteStatusIconSprite.getGlobalBounds().width, 10);

		ui.mainThemeMusic.setLoop(true);

		// Apples counter
		ui.counterText.setCharacterSize(16);
		ui.counterText.setFillColor(sf::Color::White);
		ui.counterText.setPosition(10, 10);
		ui.counterText.setString(("Score: " + std::to_string(ui.numEatenApples)).c_str());

		// Main menu texts
		// Mode
		ui.modeText.setCharacterSize(20);
		ui.modeText.setFillColor(sf::Color::White);
		ui.modeText.setString(MAIN_MENU_INFINITE_MODE_TEXT);

		// Yes
		ui.yesText.setCharacterSize(20);
		ui.yesText.setFillColor(sf::Color::White);
		ui.yesText.setString(YES_TEXT);
		ui.yesText.setPosition(SCREEN_WIDTH / 2.f - 200, 2.f * SCREEN_HEIGHT / 3.f);
		// No
		ui.noText.setCharacterSize(20);
		ui.noText.setFillColor(sf::Color::White);
		ui.noText.setString(NO_TEXT);
		ui.noText.setPosition(SCREEN_WIDTH / 2.f + 130, 2.f * SCREEN_HEIGHT / 3.f);

		// Game over text
		ui.gameOverText.setCharacterSize(30);
		ui.gameOverText.setFillColor(sf::Color::White);
		ui.gameOverText.setString(GAME_OVER_TEXT);

		// Game over menu text
		// Restart
		ui.gameOverMenuRestartText.setCharacterSize(20);
		ui.gameOverMenuRestartText.setFillColor(sf::Color::White);
		ui.gameOverMenuRestartText.setString(GAME_OVER_MENU_RESTART_TEXT);
		// "Main menu" mode select
		ui.gameOverMenuModeSelectText.setCharacterSize(20);
		ui.gameOverMenuModeSelectText.setFillColor(sf::Color::White);
		ui.gameOverMenuModeSelectText.setString(GAME_OVER_MENU_MODE_SELECT_TEXT);
		// Close
		ui.gameOverMenuCloseText.setCharacterSize(20);
		ui.gameOverMenuCloseText.setFillColor(sf::Color::White);
		ui.gameOverMenuCloseText.setString(GAME_OVER_MENU_CLOSE_TEXT);
	}
	GameModes SelectMode(UI & ui, const bool selected, short& selectedModes) {
		selectedModes = selectedModes | short(selected) << short(ui.menuState);
		ui.menuState = GameModes(ui.menuState + 1);
		if (ui.menuState != GameModes::End) SetMainMenuUI(ui);
		return ui.menuState;
	}
	void RecalculateCounter(UI& ui) {
		ui.numEatenApples++;
		ui.counterText.setString(("Score: " + std::to_string(ui.numEatenApples)).c_str()); // update score counter
	}
	void DrawUI(UI& ui, sf::RenderWindow& window) {
		if (ui.gameState == GameStates::Menu) {
			window.draw(ui.modeText);
			window.draw(ui.yesText);
			window.draw(ui.noText);
		}
		if (ui.gameState == GameStates::GamePlay) window.draw(ui.counterText);
		if (ui.gameState == GameStates::GameOver) {
			if (!ui.isGameWon) window.draw(ui.counterText);
			window.draw(ui.gameOverText);
			window.draw(ui.gameOverMenuRestartText);
			window.draw(ui.gameOverMenuModeSelectText);
			window.draw(ui.gameOverMenuCloseText);
		}

		window.draw(ui.muteStatusIconSprite);
	}
	void SetMainMenuUI(UI& ui) {
		if (ui.mainThemeMusic.getStatus() != sf::SoundSource::Playing) {
			ui.mainThemeMusic.play();
		}
		if (ui.mainThemeMusic.getVolume() != 100.f)
			ui.mainThemeMusic.setVolume(80.f); // change behaviour to variable

		switch (ui.menuState) {
		case GameModes::Infinite:
			ui.modeText.setString(MAIN_MENU_INFINITE_MODE_TEXT);
			break;
		case GameModes::AccelWorld:
			ui.modeText.setString(MAIN_MENU_ACCEL_WORLD_MODE_TEXT);
			break;
		case GameModes::OpenSpace:
			ui.modeText.setString(MAIN_MENU_OPEN_SPACE_MODE_TEXT);
			break;
		default:
			break;
		}

		ui.modeText.setOrigin(ui.modeText.getLocalBounds().width / 2.f, ui.modeText.getLocalBounds().height);
		ui.modeText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
	}
	void SetGameOverUI(UI& ui) {
		ui.gameState = GameStates::GameOver;

		if (ui.isGameWon) ui.gameOverText.setString(GAME_WON_TEXT);
		else ui.gameOverText.setString(GAME_OVER_TEXT);

		ui.gameOverText.setOrigin(ui.gameOverText.getLocalBounds().width / 2.f, ui.gameOverText.getLocalBounds().height);
		ui.gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

		ui.counterText.setCharacterSize(20);
		ui.counterText.setPosition(SCREEN_WIDTH / 2.f - ui.counterText.getGlobalBounds().width / 2.f, ui.gameOverText.getGlobalBounds().top + ui.gameOverText.getGlobalBounds().height + 10);

		ui.gameOverMenuRestartText.setOrigin(ui.gameOverMenuRestartText.getLocalBounds().width / 2.f, 0);
		ui.gameOverMenuRestartText.setPosition(SCREEN_WIDTH / 2.f, 2.f * SCREEN_HEIGHT / 3.f);
		ui.gameOverMenuModeSelectText.setOrigin(ui.gameOverMenuModeSelectText.getLocalBounds().width / 2.f, 0);
		ui.gameOverMenuModeSelectText.setPosition(SCREEN_WIDTH / 2.f, ui.gameOverMenuRestartText.getGlobalBounds().top + ui.gameOverMenuRestartText.getGlobalBounds().height + 15);
		ui.gameOverMenuCloseText.setOrigin(ui.gameOverMenuCloseText.getLocalBounds().width / 2.f, 0);
		ui.gameOverMenuCloseText.setPosition(SCREEN_WIDTH / 2.f, ui.gameOverMenuModeSelectText.getGlobalBounds().top + ui.gameOverMenuModeSelectText.getGlobalBounds().height + 15);
	}
	void ResetUI(UI& ui) {
		ui.isGameWon = false;
		ui.numEatenApples = 0;
		ui.counterText.setPosition(10, 10);
		ui.counterText.setCharacterSize(16);
		ui.counterText.setString(("Score: " + std::to_string(ui.numEatenApples)).c_str());
	}
	void ChangeMuteStatus(UI& ui) {
		ui.isMute = !ui.isMute;
		SetMuteStatus(ui);
	}
	void SetMuteStatus(UI& ui) {
		if (ui.isMute) {
			// change behaviour to variable
			ui.mainThemeMusic.setVolume(0.f);
			ui.gameWonSound.setVolume(0.f);
			ui.gameOverSound.setVolume(0.f);
			ui.appleEatenSound.setVolume(0.f);
			ui.muteStatusIconSprite.setTexture(ui.soundOffTexture);
		}
		else {
			// change behaviour to variable
			ui.mainThemeMusic.setVolume(80.f);
			ui.gameWonSound.setVolume(80.f);
			ui.gameOverSound.setVolume(80.f);
			ui.appleEatenSound.setVolume(80.f);
			ui.muteStatusIconSprite.setTexture(ui.soundOnTexture);
		}
	}
}