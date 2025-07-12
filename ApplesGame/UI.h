#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include <map>
#include <iostream>
#include "Records.h"

namespace ApplesGame {
	enum class GameStates : int {
		MainMenu,
		ModeSelect,
		GamePlay,
		GameOver,
	};

	enum GameModes : short {
		Infinite,
		AccelWorld,
		OpenSpace,
		End,
	};

	struct MenuItem {
		bool isActive = false;
		int order;
		std::string name;
		sf::Text text;
	};


	struct UI {
		bool isGameWon = false;
		short selectedModes = 0;
		int numEatenApples = 0;
		float playTime = 0.f;
		GameStates gameState = GameStates::MainMenu;
		GameModes menuState = GameModes::Infinite;

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

		sf::Texture checkTexture;

		sf::Font font;

		// texts
		// game name
		sf::Text gameNameText;
		// apples counter
		sf::Text userScoreText;

		// main menu
		sf::Text mainMenuPlayText;
		sf::Text mainMenuControlsText;
		sf::Text mainMenuQuitText;

		// mode
		sf::Text modeSelectText;
		sf::Text modeSelectMenuInfiniteText;
		sf::Text modeSelectMenuAccelWorldText;
		sf::Text modeSelectMenuOpenSpaceText;
		sf::Text modeSelectStartText;
		sf::Text yesText;
		sf::Text noText;

		// gameover
		sf::Text gameOverText;
		// gameover menu
		sf::Text gameOverMenuRestartText;
		sf::Text gameOverMenuModeSelectText;
		sf::Text gameOverMenuToMainMenuText;
		sf::Text gameOverMenuCloseText;

		// active text in menu
		sf::Text activeMenuText;

		// menus
		// main menu
		static const int mainMenuLength = 3;
		MenuItem mainMenu[mainMenuLength] = {
			{ false, 0, "main_menu_play" },
			{ false, 1, "main_menu_controls" },
			{ false, 2, "main_menu_quit" },
		};
		// mode select menu
		static const int modeMenuLength = GameModes::End + 1;
		MenuItem modeMenu[modeMenuLength] = {
			{ false, 0, "mode_menu_infinite" },
			{ false, 1, "mode_menu_accel_world" },
			{ false, 2, "mode_menu_open_space" },
			{ false, 3, "mode_menu_start" },
		};
		// gameover menu
		static const int gameOverMenuLength = 4;
		MenuItem gameOverMenu[gameOverMenuLength] = {
			{ false, 0, "game_over_menu_restart" },
			{ false, 1, "game_over_menu_mode_select" },
			{ false, 2, "game_over_menu_to_main_menu" },
			{ false, 3, "game_over_menu_quit" },
		};

		// Game mute status
		bool isMute = true;

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
			{ sf::Keyboard::Up, false },
			{ sf::Keyboard::Left, false },
			{ sf::Keyboard::Down, false },
			{ sf::Keyboard::Right, false },
		};
	};

	struct Game;

	void InitUI(UI& ui);
	void InitMainMenuUI(UI& ui);
	void InitModeMenuUI(UI& ui);
	void InitGameOverUI(UI& ui);
	void SetMainMenuItemActive(UI& ui, const MenuItem& activeMenuItem);
	void SetModeMenuItemActive(UI& ui, const MenuItem& activeMenuItem);
	void SetGameOverMenuItemActive(UI& ui, const MenuItem& activeMenuItem);
	void SetActiveMenuItem(const std::string menuName, UI& ui, const MenuItem& selectedMenuItem);
	void SetMenuItemsInactive(const std::string menuName, UI& ui);
	void SetUIFonts(UI& ui);
	void SelectMode(UI& ui, const int modeIndex);
	void RecalculateCounter(UI& ui);
	void DrawUI(UI& ui, Records* recordsList, sf::RenderWindow& window);
	void DrawModeSelectUI(UI& ui, sf::RenderWindow& window);
	void DrawGameOverUI(UI& ui, Records* recordsList, sf::RenderWindow& window);
	void SetMainMenuUI(UI& ui);
	void SetModeSelectUI(UI& ui);
	void SetGameOverUI(UI& ui);
	void ResetUI(UI& ui);
	void ChangeMuteStatus(UI& ui);
	void SetMuteStatus(UI& ui);
}