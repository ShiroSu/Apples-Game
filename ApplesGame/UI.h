#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include <map>

namespace ApplesGame {
	struct UI {
		bool isGameOver = false;
		int numEatenApples = 0;

		// Sound files
		sf::SoundBuffer appleEatenSoundSource;
		sf::SoundBuffer gameOverSoundSource;
		// Game sounds
		sf::Sound appleEatenSound;
		sf::Sound gameOverSound;

		// Sound on/off icons
		sf::Texture soundOnTexture;
		sf::Texture soundOffTexture;
		sf::Sprite muteStatusIconSprite;

		// apples counter
		sf::Text counterText;
		// gameover text
		sf::Text gameOverText;

		// Game mute status
		bool isMute = false;

		bool isMouseClicked = false;
		std::map<sf::Keyboard::Key, bool> keyboardButtonStatus = {
			{ sf::Keyboard::M, false },
			{ sf::Keyboard::R, false },
		};
	};

	struct Game;

	void InitUI(UI& ui);
	void RecalculateCounter(UI& ui);
	void DrawUI(UI& ui, sf::RenderWindow& window);
	void SetGameOverUI(UI& ui);
	void ResetUI(UI& ui);
	void ChangeMuteStatus(UI& ui);
	void SetMuteStatus(UI& ui);
}