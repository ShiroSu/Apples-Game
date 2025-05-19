#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include <map>

namespace ApplesGame {
	enum class GameStates : int {
		Menu,
		GamePlay,
		GameOver,
	};

	enum GameModes : short {
		Infinite,
		AccelWorld,
		OpenSpace,
		End,
	};

	struct UI {
		bool isGameWon = false;
		GameStates gameState = GameStates::Menu;
		GameModes menuState = GameModes::Infinite;
		int numEatenApples = 0;

		sf::Music mainThemeMusic;

		// Sound files
		sf::SoundBuffer appleEatenSoundSource;
		sf::SoundBuffer gameOverSoundSource;
		sf::SoundBuffer gameWonSoundSource;
		// Game sounds
		sf::Sound appleEatenSound;
		sf::Sound gameOverSound;
		sf::Sound gameWonSound;

		// Sound on/off icons
		sf::Texture soundOnTexture;
		sf::Texture soundOffTexture;
		sf::Sprite muteStatusIconSprite;

		// apples counter
		sf::Text counterText;
		// gameover text
		sf::Text gameOverText;
		// gameover menu
		sf::Text gameOverMenuRestartText;
		sf::Text gameOverMenuModeSelectText;
		sf::Text gameOverMenuCloseText;  

		// mode texts
		sf::Text modeText;
		sf::Text yesText;
		sf::Text noText;

		// Game mute status
		bool isMute = false;

		bool isMouseClicked = false;
		std::map<sf::Keyboard::Key, bool> keyboardButtonStatus = {
			{ sf::Keyboard::A, false },
			{ sf::Keyboard::D, false },
			{ sf::Keyboard::M, false },
			{ sf::Keyboard::N, false },
			{ sf::Keyboard::R, false },
			{ sf::Keyboard::S, false },
			{ sf::Keyboard::Y, false },
			{ sf::Keyboard::W, false },
			{ sf::Keyboard::Num1, false },
			{ sf::Keyboard::Num2, false },
			{ sf::Keyboard::Numpad1, false },
			{ sf::Keyboard::Numpad2, false },
			{ sf::Keyboard::Enter, false },
			{ sf::Keyboard::Space, false },
		};
	};

	struct Game;

	void InitUI(UI& ui);
	GameModes SelectMode(UI & ui, const bool selected, short& selectedModes);
	void RecalculateCounter(UI& ui);
	void DrawUI(UI& ui, sf::RenderWindow& window);
	void SetMainMenuUI(UI& ui);
	void SetGameOverUI(UI& ui);
	void ResetUI(UI& ui);
	void ChangeMuteStatus(UI& ui);
	void SetMuteStatus(UI& ui);
}