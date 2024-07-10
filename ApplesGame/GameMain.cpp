// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>

const enum PlayerDirection {
	Right,
	Up,
	Left,
	Down
};

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float INITIAL_SPEED = 100.f;
const float PLAYER_SIZE = 20.f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");
	float playerX = SCREEN_WIDTH / 2.f;
	float playerY = SCREEN_HEIGHT / 2.f;
	float playerSpeed = INITIAL_SPEED;
	PlayerDirection playerDirection = Right; // 0 - Right, 1 - Up, 2 - Left, 3 - Down

	sf::Text currentPositionText;
	//currentPositionText.setCharacterSize(10);
	currentPositionText.setOutlineColor(sf::Color::White);
	currentPositionText.setPosition(5, 5);

	sf::RectangleShape playerShape;
	playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	playerShape.setFillColor(sf::Color::Blue);
	playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	playerShape.setPosition(playerX, playerY);

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			) {
					playerDirection = Right;
		} else if (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::W)
			) {
					playerDirection = Up;
		} else if (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::A)
			) {
					playerDirection = Left;
		} else if (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::S)
			) {
					playerDirection = Down;
		}
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

		switch (playerDirection) {
		case Right:
			playerX += playerSpeed * deltaTime;
			break;
		case Up:
			playerY -= playerSpeed * deltaTime;
			break;
		case Left:
			playerX -= playerSpeed * deltaTime;
			break;
		case Down:
			playerY += playerSpeed * deltaTime;
			break;
		default:
			break;
		}


		window.clear();
		playerShape.setPosition(playerX, playerY);
		currentPositionText.setString("x: ");
		if ((playerX - PLAYER_SIZE / 2.f < 0 || playerX + PLAYER_SIZE / 2.f > SCREEN_WIDTH) || (playerY - PLAYER_SIZE / 2.f < 0 || playerY + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)) {
			break;
		//	sf::Text gameOverText;
		//	gameOverText.setString("GAME_OVER");
		//	//gameOverText.setStyle(sf::Color::Red);
		//	gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		//	window.draw(gameOverText);
		}
		else {
			window.draw(playerShape);
			window.draw(currentPositionText);
		}
		window.display();
	}

	return 0;
}
