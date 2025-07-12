#include "UI.h"
#include <cassert>

namespace ApplesGame {
	void InitUI(UI& ui) {
		// Loading fonts
		assert(ui.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf"));

		// Check icon
		assert(ui.checkTexture.loadFromFile(RESOURCES_PATH + "Check.png"));
		ui.checkTexture.setSmooth(true);

		// Sound on/off icons
		assert(ui.soundOnTexture.loadFromFile(RESOURCES_PATH + "Sound_on.png"));
		assert(ui.soundOffTexture.loadFromFile(RESOURCES_PATH + "Sound_off.png"));
		ui.soundOffTexture.setSmooth(true);
		ui.soundOnTexture.setSmooth(true);
		SetMuteStatus(ui);
		setSpriteSize(ui.muteStatusIconSprite, SOUND_ICON_SIZE);
		ui.muteStatusIconSprite.setPosition(SCREEN_WIDTH - 10 - ui.muteStatusIconSprite.getGlobalBounds().width, 10);

		ui.mainThemeMusic.setLoop(true);

		// UI texts
		InitMainMenuUI(ui);
		InitModeMenuUI(ui);
		InitGameOverUI(ui);

		// Yes
		ui.yesText.setFont(ui.font);
		ui.yesText.setCharacterSize(20);
		ui.yesText.setFillColor(sf::Color::White);
		ui.yesText.setString(YES_TEXT);
		ui.yesText.setPosition(SCREEN_WIDTH / 2.f - 200, 2.f * SCREEN_HEIGHT / 3.f);
		// No
		ui.noText.setFont(ui.font);
		ui.noText.setCharacterSize(20);
		ui.noText.setFillColor(sf::Color::White);
		ui.noText.setString(NO_TEXT);
		ui.noText.setPosition(SCREEN_WIDTH / 2.f + 130, 2.f * SCREEN_HEIGHT / 3.f);

		// Apples counter
		ui.userScoreText.setFont(ui.font);
		ui.userScoreText.setCharacterSize(16);
		ui.userScoreText.setFillColor(sf::Color::White);
		ui.userScoreText.setPosition(10, 10);
		ui.userScoreText.setString(("Score: " + std::to_string(ui.numEatenApples)).c_str());
	}
	void InitMainMenuUI(UI& ui) {
		// Game name
		ui.gameNameText.setFont(ui.font);
		ui.gameNameText.setCharacterSize(54);
		ui.gameNameText.setFillColor(sf::Color::Color(123456));
		ui.gameNameText.setString(GAME_NAME_TEXT);
		ui.gameNameText.setOrigin(ui.gameNameText.getLocalBounds().width / 2.f, ui.gameNameText.getLocalBounds().height);
		ui.gameNameText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 4.f);

		// Main menu texts
		// Play
		ui.mainMenuPlayText.setFont(ui.font);
		ui.mainMenuPlayText.setCharacterSize(30);
		ui.mainMenuPlayText.setFillColor(sf::Color::White);
		ui.mainMenuPlayText.setString(MAIN_MENU_PLAY_TEXT);
		ui.mainMenuPlayText.setOrigin(ui.mainMenuPlayText.getLocalBounds().width / 2.f, ui.mainMenuPlayText.getLocalBounds().top);
		ui.mainMenuPlayText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		ui.mainMenu[0].text = ui.mainMenuPlayText;
		// Controls
		ui.mainMenuControlsText.setFont(ui.font);
		ui.mainMenuControlsText.setCharacterSize(30);
		ui.mainMenuControlsText.setFillColor(sf::Color::White);
		ui.mainMenuControlsText.setString(MAIN_MENU_CONTROLS_TEXT);
		ui.mainMenuControlsText.setOrigin(ui.mainMenuControlsText.getLocalBounds().width / 2.f, ui.mainMenuControlsText.getLocalBounds().top);
		ui.mainMenuControlsText.setPosition(SCREEN_WIDTH / 2.f, ui.mainMenuPlayText.getGlobalBounds().top + 45.f);
		ui.mainMenu[1].text = ui.mainMenuControlsText;
		// Quit
		ui.mainMenuQuitText.setFont(ui.font);
		ui.mainMenuQuitText.setCharacterSize(30);
		ui.mainMenuQuitText.setFillColor(sf::Color::White);
		ui.mainMenuQuitText.setString(MAIN_MENU_QUIT_TEXT);
		ui.mainMenuQuitText.setOrigin(ui.mainMenuQuitText.getLocalBounds().width / 2.f, ui.mainMenuQuitText.getLocalBounds().top);
		ui.mainMenuQuitText.setPosition(SCREEN_WIDTH / 2.f, ui.mainMenuControlsText.getGlobalBounds().top + 45.f);
		ui.mainMenu[2].text = ui.mainMenuQuitText;
	}
	void InitModeMenuUI(UI& ui) {
		// Mode menu texts
		ui.modeSelectText.setFont(ui.font);
		ui.modeSelectText.setCharacterSize(40);
		ui.modeSelectText.setFillColor(sf::Color::White);
		ui.modeSelectText.setString(MODE_SELECT_TEXT);
		ui.modeSelectText.setOrigin(ui.modeSelectText.getLocalBounds().width / 2.f, ui.modeSelectText.getLocalBounds().height);
		ui.modeSelectText.setPosition(SCREEN_WIDTH / 2.f, 2.f * SCREEN_HEIGHT / 7.f);
		// Infinite mode
		ui.modeSelectMenuInfiniteText.setFont(ui.font);
		ui.modeSelectMenuInfiniteText.setCharacterSize(20);
		ui.modeSelectMenuInfiniteText.setFillColor(sf::Color::White);
		ui.modeSelectMenuInfiniteText.setString(MODE_SELECT_INFINITE_MODE_TEXT);
		ui.modeSelectMenuInfiniteText.setPosition(30.f, SCREEN_HEIGHT / 2.f);
		ui.modeMenu[GameModes::Infinite].text = ui.modeSelectMenuInfiniteText;
		// Accel world
		ui.modeSelectMenuAccelWorldText.setFont(ui.font);
		ui.modeSelectMenuAccelWorldText.setCharacterSize(20);
		ui.modeSelectMenuAccelWorldText.setFillColor(sf::Color::White);
		ui.modeSelectMenuAccelWorldText.setString(MODE_SELECT_ACCEL_WORLD_MODE_TEXT);
		ui.modeSelectMenuAccelWorldText.setPosition(30.f, ui.modeSelectMenuInfiniteText.getGlobalBounds().top + 45.f);
		ui.modeMenu[GameModes::AccelWorld].text = ui.modeSelectMenuAccelWorldText;
		// Open space
		ui.modeSelectMenuOpenSpaceText.setFont(ui.font);
		ui.modeSelectMenuOpenSpaceText.setCharacterSize(20);
		ui.modeSelectMenuOpenSpaceText.setFillColor(sf::Color::White);
		ui.modeSelectMenuOpenSpaceText.setString(MODE_SELECT_OPEN_SPACE_MODE_TEXT);
		ui.modeSelectMenuOpenSpaceText.setPosition(30.f, ui.modeSelectMenuAccelWorldText.getGlobalBounds().top + 45.f);
		ui.modeMenu[GameModes::OpenSpace].text = ui.modeSelectMenuOpenSpaceText;
		// Start
		ui.modeSelectStartText.setFont(ui.font);
		ui.modeSelectStartText.setCharacterSize(27);
		ui.modeSelectStartText.setFillColor(sf::Color::White);
		ui.modeSelectStartText.setString(MODE_SELECT_START_TEXT);
		ui.modeSelectStartText.setOrigin(ui.modeSelectStartText.getLocalBounds().width / 2.f, ui.modeSelectStartText.getLocalBounds().top);
		ui.modeSelectStartText.setPosition(SCREEN_WIDTH / 2.f, ui.modeSelectMenuOpenSpaceText.getGlobalBounds().top + 120.f);
		ui.modeMenu[GameModes::End].text = ui.modeSelectStartText;

	}
	void InitGameOverUI(UI& ui) {
		// Game over text
		ui.gameOverText.setFont(ui.font);
		ui.gameOverText.setCharacterSize(30);
		ui.gameOverText.setFillColor(sf::Color::White);
		ui.gameOverText.setString(GAME_OVER_TEXT);

		// Game over menu text
		// Restart
		ui.gameOverMenuRestartText.setFont(ui.font);
		ui.gameOverMenuRestartText.setCharacterSize(20);
		ui.gameOverMenuRestartText.setFillColor(sf::Color::White);
		ui.gameOverMenuRestartText.setString(GAME_OVER_MENU_RESTART_TEXT);
		ui.gameOverMenuRestartText.setOrigin(ui.gameOverMenuRestartText.getLocalBounds().width / 2.f, 0);
		ui.gameOverMenuRestartText.setPosition(SCREEN_WIDTH / 2.f, 2.f * SCREEN_HEIGHT / 3.f);
		ui.gameOverMenu[0].text = ui.gameOverMenuRestartText;
		// To mode select
		ui.gameOverMenuModeSelectText.setFont(ui.font);
		ui.gameOverMenuModeSelectText.setCharacterSize(20);
		ui.gameOverMenuModeSelectText.setFillColor(sf::Color::White);
		ui.gameOverMenuModeSelectText.setString(GAME_OVER_MENU_MODE_SELECT_TEXT);
		ui.gameOverMenuModeSelectText.setOrigin(ui.gameOverMenuModeSelectText.getLocalBounds().width / 2.f, 0);
		ui.gameOverMenuModeSelectText.setPosition(SCREEN_WIDTH / 2.f, ui.gameOverMenuRestartText.getGlobalBounds().top + ui.gameOverMenuRestartText.getGlobalBounds().height + 15);
		ui.gameOverMenu[1].text = ui.gameOverMenuModeSelectText;
		// To main menu
		ui.gameOverMenuToMainMenuText.setFont(ui.font);
		ui.gameOverMenuToMainMenuText.setCharacterSize(20);
		ui.gameOverMenuToMainMenuText.setFillColor(sf::Color::White);
		ui.gameOverMenuToMainMenuText.setString(GAME_OVER_MENU_TO_MAIN_MENU_TEXT);
		ui.gameOverMenuToMainMenuText.setOrigin(ui.gameOverMenuToMainMenuText.getLocalBounds().width / 2.f, 0);
		ui.gameOverMenuToMainMenuText.setPosition(SCREEN_WIDTH / 2.f, ui.gameOverMenuModeSelectText.getGlobalBounds().top + ui.gameOverMenuModeSelectText.getGlobalBounds().height + 15);
		ui.gameOverMenu[2].text = ui.gameOverMenuToMainMenuText;
		// Close
		ui.gameOverMenuCloseText.setFont(ui.font);
		ui.gameOverMenuCloseText.setCharacterSize(20);
		ui.gameOverMenuCloseText.setFillColor(sf::Color::White);
		ui.gameOverMenuCloseText.setString(GAME_OVER_MENU_CLOSE_TEXT);
		ui.gameOverMenuCloseText.setOrigin(ui.gameOverMenuCloseText.getLocalBounds().width / 2.f, 0);
		ui.gameOverMenuCloseText.setPosition(SCREEN_WIDTH / 2.f, ui.gameOverMenuToMainMenuText.getGlobalBounds().top + ui.gameOverMenuToMainMenuText.getGlobalBounds().height + 15);
		ui.gameOverMenu[3].text = ui.gameOverMenuCloseText;
	}
	void SetMainMenuItemActive(UI& ui, const MenuItem& activeMenuItem) {
		SetActiveMenuItem("mainMenu", ui, activeMenuItem);
	}
	void SetModeMenuItemActive(UI& ui, const MenuItem& activeMenuItem) {
		SetActiveMenuItem("modeMenu", ui, activeMenuItem);
	}
	void SetGameOverMenuItemActive(UI& ui, const MenuItem& activeMenuItem) {
		SetActiveMenuItem("gameOverMenu", ui, activeMenuItem);
	}
	void SetActiveMenuItem(const std::string menuName, UI& ui, const MenuItem& selectedMenuItem) {
		if (menuName == "mainMenu") {
			for (auto item = ui.mainMenu; item < ui.mainMenu + ui.mainMenuLength; item++) {
				if (item->name == selectedMenuItem.name) item->isActive = true;
				else item->isActive = false;
			}
		}
		else if (menuName == "modeMenu") {
			for (auto item = ui.modeMenu; item < ui.modeMenu + ui.modeMenuLength; item++) {
				if (item->name == selectedMenuItem.name) item->isActive = true;
				else item->isActive = false;
			}
		}
		else if (menuName == "gameOverMenu") {
			for (auto item = ui.gameOverMenu; item < ui.gameOverMenu + ui.gameOverMenuLength; item++) {
				if (item->name == selectedMenuItem.name) item->isActive = true;
				else item->isActive = false;
			}
		}
	}
	void SetMenuItemsInactive(const std::string menuName, UI& ui) {
		if (menuName == "mainMenu") {
			for (auto item = ui.mainMenu; item < ui.mainMenu + ui.mainMenuLength; item++) {
				item->isActive = false;
			}
		}
		else if (menuName == "modeMenu") {
			for (auto item = ui.modeMenu; item < ui.modeMenu + ui.modeMenuLength; item++) {
				item->isActive = false;
			}
		}
		else if (menuName == "gameOverMenu") {
			for (auto item = ui.gameOverMenu; item < ui.gameOverMenu + ui.gameOverMenuLength; item++) {
				item->isActive = false;
			}
		}
	}
	void SetUIFonts(UI& ui) {
		// Main menu texts
		ui.mainMenuPlayText.setFont(ui.font);
		ui.mainMenuControlsText.setFont(ui.font);
		ui.mainMenuQuitText.setFont(ui.font);
		// Menu mode texts
		ui.modeSelectMenuInfiniteText.setFont(ui.font);
		ui.modeSelectMenuAccelWorldText.setFont(ui.font);
		ui.modeSelectMenuOpenSpaceText.setFont(ui.font);
		ui.modeSelectStartText.setFont(ui.font);
		ui.yesText.setFont(ui.font);
		ui.noText.setFont(ui.font);
		// Apples counter
		ui.userScoreText.setFont(ui.font);
		// Game over text
		ui.gameOverText.setFont(ui.font);
		// Gameover menu text
		ui.gameOverMenuRestartText.setFont(ui.font);
		ui.gameOverMenuModeSelectText.setFont(ui.font);
		ui.gameOverMenuCloseText.setFont(ui.font);
		
		return;
	}
	void SelectMode(UI& ui, const int modeIndex) {
		ui.selectedModes = ui.selectedModes ^ 1 << modeIndex;
	}
	void RecalculateCounter(UI& ui) {
		ui.numEatenApples++;
		if (ui.selectedModes & 1 << GameModes::Infinite)
			ui.userScoreText.setString("Score: " + std::to_string(ui.numEatenApples)); // update score counter
	}
	void DrawUI(UI& ui, Records* recordsList, sf::RenderWindow& window) {
		switch (ui.gameState) {
			case GameStates::MainMenu:
				window.draw(ui.gameNameText);
				for (auto item = std::begin(ui.mainMenu); item < std::end(ui.mainMenu); item++) {
					if (item->isActive) item->text.setFillColor(sf::Color::Red);
					else item->text.setFillColor(sf::Color::White);
					ui.mainMenu[1].text.setFillColor(sf::Color::Color(50, 50, 50));
					window.draw(item->text);
				}
				break;
			case GameStates::ModeSelect: {
				DrawModeSelectUI(ui, window);
				break;
			}
			case GameStates::GamePlay:
				window.draw(ui.userScoreText);
				break;
			case GameStates::GameOver:
				DrawGameOverUI(ui, recordsList, window);
				break;
		}

		window.draw(ui.muteStatusIconSprite);
	}
	void DrawModeSelectUI(UI& ui, sf::RenderWindow& window) {
		window.draw(ui.modeSelectText);
		for (auto item = std::begin(ui.modeMenu); item < std::end(ui.modeMenu); item++) {
			if (item->isActive) item->text.setFillColor(sf::Color::Red);
			else item->text.setFillColor(sf::Color::White);
			window.draw(item->text);
			if (item->name != "mode_menu_start") {
				sf::RectangleShape afterModeCheckRectShape;
				afterModeCheckRectShape.setOutlineThickness(1.f);
				afterModeCheckRectShape.setOutlineColor(sf::Color::White);
				if (ui.selectedModes & 1 << item->order) afterModeCheckRectShape.setTexture(&ui.checkTexture);
				else afterModeCheckRectShape.setFillColor(sf::Color::Black);
				afterModeCheckRectShape.setSize(sf::Vector2f(30.f, 30.f));
				afterModeCheckRectShape.setOrigin(afterModeCheckRectShape.getLocalBounds().width, afterModeCheckRectShape.getLocalBounds().height);
				afterModeCheckRectShape.setPosition(SCREEN_WIDTH - 30.f, item->text.getGlobalBounds().top + item->text.getGlobalBounds().height);
				window.draw(afterModeCheckRectShape);
			}
		}
	}
	void DrawGameOverUI(UI& ui, Records* recordsList, sf::RenderWindow& window) {
		//if (!ui.isGameWon) window.draw(ui.userScoreText);
		window.draw(ui.gameOverText);

		// records
		const float rowGap = 30.f;
		for (int i = 0; i < NUM_RECORDS; i++) {
			const Position2D nameTextPosition = { float(i / (NUM_RECORDS / 2)) * SCREEN_WIDTH / 2.f + 20.f, float(i % (NUM_RECORDS / 2)) * rowGap + ui.gameOverText.getPosition().y + 70.f};
			sf::Text nameText;
			nameText.setFont(ui.font);
			nameText.setCharacterSize(20);
			nameText.setString(std::to_string(i + 1) + ". " + recordsList[i].userName);
			nameText.setFillColor(recordsList[i].isMe ? sf::Color::Green : sf::Color::White);
			nameText.setPosition(nameTextPosition.x, nameTextPosition.y);

			const Position2D valueTextPosition = { nameTextPosition.x + SCREEN_WIDTH / 2.f - 70.f, nameTextPosition.y };
			sf::Text valueText;
			valueText.setFont(ui.font);
			valueText.setCharacterSize(20);
			if (ui.selectedModes & 1 << GameModes::Infinite) valueText.setString(std::to_string(recordsList[i].userScore));
			else valueText.setString(GetNormalizedTime(recordsList[i].userTime));
			valueText.setFillColor(recordsList[i].isMe ? sf::Color::Green : sf::Color::White);
			valueText.setPosition(valueTextPosition.x, valueTextPosition.y);

			window.draw(nameText);
			window.draw(valueText);
		}
		sf::RectangleShape separator;
		separator.setOutlineColor(sf::Color::White);
		separator.setSize(sf::Vector2f(2.f, rowGap * float(NUM_RECORDS / 2)));
		separator.setPosition(SCREEN_WIDTH / 2.f, ui.gameOverText.getPosition().y + 70.f);
		window.draw(separator);

		for (auto item = std::begin(ui.gameOverMenu); item < std::end(ui.gameOverMenu); item++) {
			if (item->isActive) item->text.setFillColor(sf::Color::Red);
			else item->text.setFillColor(sf::Color::White);
			window.draw(item->text);
		}
	}
	void SetMainMenuUI(UI& ui) {
		if (ui.mainThemeMusic.getStatus() != sf::SoundSource::Playing) {
			ui.mainThemeMusic.play();
		}
		if (!ui.isMute) {
			if (ui.mainThemeMusic.getVolume() != 80.f)
				ui.mainThemeMusic.setVolume(80.f); // change behaviour to variable
		}
	}
	void SetModeSelectUI(UI& ui) {
		if (ui.mainThemeMusic.getStatus() != sf::SoundSource::Playing) {
			ui.mainThemeMusic.play();
		}
		if (!ui.isMute) {
			if (ui.mainThemeMusic.getVolume() != 80.f)
				ui.mainThemeMusic.setVolume(80.f); // change behaviour to variable
		}
	}
	void SetGameOverUI(UI& ui) {
		ui.gameState = GameStates::GameOver;
		if (ui.appleEatenSound.getStatus() == sf::SoundSource::Playing) ui.appleEatenSound.stop();
		if (ui.isGameWon) ui.gameWonSound.play();
		else ui.gameOverSound.play();

		if (ui.isGameWon) ui.gameOverText.setString(GAME_WON_TEXT);
		else ui.gameOverText.setString(GAME_OVER_TEXT);

		ui.gameOverText.setOrigin(ui.gameOverText.getLocalBounds().width / 2.f, ui.gameOverText.getLocalBounds().height);
		ui.gameOverText.setPosition(SCREEN_WIDTH / 2.f, 60.f);
	}
	void ResetUI(UI& ui) {
		ui.isGameWon = false;
		ui.numEatenApples = 0;
		ui.playTime = 0.f;
		ui.userScoreText.setPosition(10, 10);
		ui.userScoreText.setCharacterSize(16);
		if (ui.selectedModes & 1 << GameModes::Infinite) ui.userScoreText.setString(("Score: " + std::to_string(ui.numEatenApples)).c_str());
		else ui.userScoreText.setString("Time: " + GetNormalizedTime(ui.playTime));
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