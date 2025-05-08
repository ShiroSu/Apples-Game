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

const std::string GAME_OVER_TEXT = "Game over! Press \"Space\" to play again or \"Escape\" to close.";
const float SOUND_ICON_SIZE = 25.f;
}
