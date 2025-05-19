#pragma once
#include <string>

namespace ApplesGame {
const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float INITIAL_SPEED = 100.f;
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 10.f;

const int NUM_APPLES = 20;
const float APPLE_SIZE = 20.f;

const int NUM_STONES = 10;
const float STONE_SIZE = 24.f;

const std::string MAIN_MENU_INFINITE_MODE_TEXT = "Inifinite mode (infinite apples)";
const std::string MAIN_MENU_ACCEL_WORLD_MODE_TEXT = "Accel world mode (accelerate player on apple eaten)";
const std::string MAIN_MENU_OPEN_SPACE_MODE_TEXT = "Open space mode (player goes through walls)";
const std::string YES_TEXT = "Yes (y/1)";
const std::string NO_TEXT = "No (n/2)";
const std::string GAME_OVER_TEXT = "Game over!";
const std::string GAME_WON_TEXT = "Congratulations!";
const std::string GAME_OVER_MENU_RESTART_TEXT = "Play again (\"Space\")";
const std::string GAME_OVER_MENU_MODE_SELECT_TEXT = "To main menu (\"Enter\")";
const std::string GAME_OVER_MENU_CLOSE_TEXT = "Close (\"Escape\")";
const float SOUND_ICON_SIZE = 25.f;
}
