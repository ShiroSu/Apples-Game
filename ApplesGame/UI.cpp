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

		// Apples counter
		ui.counterText.setCharacterSize(16);
		ui.counterText.setFillColor(sf::Color::White);
		//ui.counterText.setString(("Score: " + std::to_string(ui.numEatenApples)).c_str());
		ui.counterText.setPosition(10, 10);

		// Game over text
		ui.gameOverText.setCharacterSize(20);
		ui.gameOverText.setFillColor(sf::Color::White);
		ui.gameOverText.setString(GAME_OVER_TEXT);
	}
	void RecalculateCounter(UI& ui) {
		ui.numEatenApples++;
		ui.counterText.setString(("Score: " + std::to_string(ui.numEatenApples)).c_str()); // update score counter
	}
	void DrawUI(UI& ui, sf::RenderWindow& window) {
		if (ui.isGameOver) window.draw(ui.gameOverText);

		window.draw(ui.muteStatusIconSprite);
		window.draw(ui.counterText);
	}
	void SetGameOverUI(UI& ui) {
		ui.isGameOver = true;

		ui.gameOverText.setOrigin(ui.gameOverText.getGlobalBounds().width / 2.f, ui.gameOverText.getGlobalBounds().height);
		ui.gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

		ui.counterText.setCharacterSize(20);
		ui.counterText.setPosition(SCREEN_WIDTH / 2.f - ui.counterText.getGlobalBounds().width / 2.f, ui.gameOverText.getGlobalBounds().top + ui.gameOverText.getGlobalBounds().height + 10);
	}
	void ResetUI(UI& ui) {
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
			ui.gameOverSound.setVolume(0);
			ui.appleEatenSound.setVolume(0);
			ui.muteStatusIconSprite.setTexture(ui.soundOffTexture);
		}
		else {
			ui.gameOverSound.setVolume(100);
			ui.appleEatenSound.setVolume(100);
			ui.muteStatusIconSprite.setTexture(ui.soundOnTexture);
		}
	}
}