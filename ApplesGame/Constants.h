#pragma once
#include <string>

namespace ApplesGame {
const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float INITIAL_SPEED = 100.f;
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 10.f;

const int MIN_NUM_APPLES_INFINITE = 20;
const int MAX_NUM_APPLES_INFINITE = 40;
const int MIN_NUM_APPLES_FINITE = 50;
const int MAX_NUM_APPLES_FINITE = 80;
const float APPLE_SIZE = 20.f;

const int NUM_STONES = 10;
const float STONE_SIZE = 24.f;

const float SOUND_ICON_SIZE = 25.f;

const std::string GAME_NAME_TEXT = "Apples game";
const std::string MAIN_MENU_PLAY_TEXT = "Start game";
const std::string MAIN_MENU_CONTROLS_TEXT = "Controls";
const std::string MAIN_MENU_OPTIONS_TEXT = "Options";
const std::string MAIN_MENU_QUIT_TEXT = "Close game";
const std::string MODE_SELECT_TEXT = "Game modes";
const std::string MODE_SELECT_INFINITE_MODE_TEXT = "Inifinite mode (infinite apples)";
const std::string MODE_SELECT_ACCEL_WORLD_MODE_TEXT = "Accel world mode (accelerate player on apple eaten)";
const std::string MODE_SELECT_OPEN_SPACE_MODE_TEXT = "Open space mode (player goes through walls)";
const std::string MODE_SELECT_START_TEXT = "Start";
const std::string ARE_YOU_SURE_TEXT = "Are you sure?";
const std::string YES_TEXT = "Yes (y/1)";
const std::string NO_TEXT = "No (n/2)";
const std::string GAME_OVER_TEXT = "Game over!";
const std::string GAME_WON_TEXT = "Congratulations!";
const std::string GAME_OVER_MENU_RESTART_TEXT = "Play again";
const std::string GAME_OVER_MENU_MODE_SELECT_TEXT = "To mode select";
const std::string GAME_OVER_MENU_TO_MAIN_MENU_TEXT = "To main menu";
const std::string GAME_OVER_MENU_CLOSE_TEXT = "Close";

const int NUM_RECORDS = 10;
const int NAME_BASE_LENGTH = 40;
const std::string FAKE_USERS_NAME[NAME_BASE_LENGTH] = {
	"Adrienne",
	"Leilah",
	"Raffaela",
	"Dolph",
	"Layton",
	"Charlotte",
	"Brody",
	"Mitya",
	"Jocelyn",
	"Connor",
	"Roman",
	"Jefferson",
	"Denholm",
	"Rosabel",
	"Marusya",
	"Osbourne",
	"Bruce",
	"Trudi",
	"Illarion",
	"Kane",
	"Marianna",
	"Luana",
	"Kali",
	"Victoire",
	"Michelle",
	"Marlène",
	"Suzanne",
	"Hewie",
	"Bailee",
	"Marilynn",
	"Makar",
	"Rosmarie",
	"Mike",
	"Agniya",
	"Jochen",
	"Millard",
	"Boris",
	"Roslyn",
	"Marshall",
	"Kristia",
};
}
