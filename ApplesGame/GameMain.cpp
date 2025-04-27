// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

enum PlayerDirection {
	Up,
	Right,
	Down,
	Left,
};

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);
	// Init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");

	// Init player state
	float playerX = SCREEN_WIDTH / 2.f;
	float playerY = SCREEN_HEIGHT / 2.f;
	float playerSpeed = INITIAL_SPEED;
	PlayerDirection playerDirection = PlayerDirection(Right); // 0-up, 1-right, 2-down, 3-left

	// Init player shape
	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Red);
	playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	playerShape.setPosition(playerX, playerY);

	// Init apples
	float applesX[NUM_APPLES];
	float applesY[NUM_APPLES];
	bool isAppleEaten[NUM_APPLES];
	sf::CircleShape applesShapes[NUM_APPLES];

	// placing apple to random spot
	auto placeApple = [&](int index) {
		applesX[index] = rand() / (float)RAND_MAX * (SCREEN_WIDTH - APPLE_SIZE);
		applesY[index] = rand() / (float)RAND_MAX * (SCREEN_HEIGHT - APPLE_SIZE);
		applesShapes[index].setPosition(applesX[index], applesY[index]);
		};

	for (int i = 0; i < NUM_APPLES; i++) {
		isAppleEaten[i] = false;

		applesShapes[i].setRadius(APPLE_SIZE / 2.f);
		applesShapes[i].setFillColor(sf::Color::Green);
		applesShapes[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		placeApple(i);
	}

	int numEatenApples = 0;

	// Init stones
	float stonesX[NUM_STONES];
	float stonesY[NUM_STONES];
	bool isStoneShown[NUM_STONES];
	sf::CircleShape stonesShapes[NUM_STONES];
	int lastShownStoneIndex = -1;
	int applesBeforeStone = 5 + int(rand() / (float)RAND_MAX * 10.f);
	bool openedCountdownTillNextStone = false; // need to limit showing stones when condition is met

	for (int i = 0; i < NUM_STONES; i++) {
		isStoneShown[i] = false;

		stonesShapes[i].setRadius(STONE_SIZE / 2.f);
		stonesShapes[i].setFillColor(sf::Color::White);
		stonesShapes[i].setOrigin(STONE_SIZE / 2.f, STONE_SIZE / 2.f);
	}


	// loading fonts
	sf::Font font;
	font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Medium.ttf");

	// Apples counter
	sf::Text counterText;
	counterText.setFont(font);
	counterText.setCharacterSize(16);
	counterText.setFillColor(sf::Color::White);
	counterText.setString(std::to_string(numEatenApples));

	// Game over text
	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(20);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setString(std::string(GAME_OVER_TEXT));
	gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2.f, gameOverText.getGlobalBounds().height);
	gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

	// Init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	bool isGameOver = false;

	// Main loop
	while (window.isOpen())
	{
		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		counterText.setPosition(10, 10); // placing score counter

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			break;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			playerDirection = PlayerDirection(Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			playerDirection = PlayerDirection(Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			playerDirection = PlayerDirection(Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			playerDirection = PlayerDirection(Down);
		}

		// Change player position
		switch (playerDirection) {
		case PlayerDirection(Right):
			playerX += playerSpeed * deltaTime;
			break;
		case PlayerDirection(Left):
			playerX -= playerSpeed * deltaTime;
			break;
		case PlayerDirection(Up):
			playerY -= playerSpeed * deltaTime;
			break;
		case PlayerDirection(Down):
			playerY += playerSpeed * deltaTime;
			break;
		}

		for (int i = 0; i < NUM_APPLES; i++) {
			if (!isAppleEaten[i]) {
				float squareDistance = (playerX - applesX[i]) * (playerX - applesX[i]) + (playerY - applesY[i]) * (playerY - applesY[i]);
				float sqareRadiusSum = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4.f;
				if (squareDistance < sqareRadiusSum) {
					// Accelerate player
					playerSpeed += ACCELERATION;

					placeApple(i);
					numEatenApples++;

					openedCountdownTillNextStone = lastShownStoneIndex < NUM_STONES - 1;
				}
			}
		}

		for (int i = 0; i < NUM_STONES; i++) {
			if (isStoneShown[i]) {
				float squareDistance = (playerX - stonesX[i]) * (playerX - stonesX[i]) + (playerY - stonesY[i]) * (playerY - stonesY[i]);
				float sqareRadiusSum = (STONE_SIZE + PLAYER_SIZE) * (STONE_SIZE + PLAYER_SIZE) / 4.f;
				if (squareDistance < sqareRadiusSum) {
					isGameOver = true;
					window.clear();
				}
			}
		}

		// Show stone if enough apples are eaten
		if (openedCountdownTillNextStone && numEatenApples > 0 &&
			numEatenApples % applesBeforeStone == 0) {
			openedCountdownTillNextStone = false;
			++lastShownStoneIndex;
			applesBeforeStone = 5 + int(rand() / (float)RAND_MAX * 10.f);

			stonesX[lastShownStoneIndex] = rand() / (float)RAND_MAX * (SCREEN_WIDTH - STONE_SIZE);
			stonesY[lastShownStoneIndex] = rand() / (float)RAND_MAX * (SCREEN_HEIGHT - STONE_SIZE);
			stonesShapes[lastShownStoneIndex].setPosition(stonesX[lastShownStoneIndex], stonesY[lastShownStoneIndex]);
			isStoneShown[lastShownStoneIndex] = true;
		}

		// Check in bound
		if (
			playerX + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			playerX - PLAYER_SIZE / 2.f < 0.f ||
			playerY - PLAYER_SIZE / 2.f < 0.f ||
			playerY + PLAYER_SIZE / 2.f > SCREEN_HEIGHT
			) {
			isGameOver = true;
			window.clear();
		}

		if (!isGameOver) {
			// Redraw scene
			window.clear();
			playerShape.setPosition(playerX, playerY);
			window.draw(playerShape);
			for (int i = 0; i < NUM_APPLES; i++) {
				if (!isAppleEaten[i]) window.draw(applesShapes[i]);
			}
			for (int i = 0; i < NUM_STONES; i++) {
				if (isStoneShown[i]) window.draw(stonesShapes[i]);
			}
			counterText.setString(("Score: " + std::to_string(numEatenApples)).c_str()); // update score counter
			window.draw(counterText);
			window.display();
		}
		else {
			counterText.setCharacterSize(20);
			counterText.setPosition(SCREEN_WIDTH / 2.f - counterText.getLocalBounds().width, gameOverText.getGlobalBounds().top + gameOverText.getGlobalBounds().height + 20);
			window.draw(gameOverText);
			window.draw(counterText);
			window.display();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				// reset game state
				playerDirection = PlayerDirection(Right);
				playerX = SCREEN_WIDTH / 2.f;
				playerY = SCREEN_HEIGHT / 2.f;
				playerSpeed = INITIAL_SPEED;
				playerShape.setPosition(playerX, playerY);

				for (int i = 0; i < NUM_APPLES; i++) {
					numEatenApples = 0;
					placeApple(i);
				}
				for (int i = 0; i < NUM_STONES; i++) {
					lastShownStoneIndex = -1;
					isStoneShown[i] = false;
				}
				isGameOver = false;
			}
		}
	}

	return 0;
}
