#pragma once

namespace sf {
	class Sprite;
	class Text;
	template <typename T>
	class Vector2;
	template <typename T>
	class Rect;
}

namespace ApplesGame {
	struct Vector2D {
		float x = 0.f;
		float y = 0.f;
	};
	typedef Vector2D Position2D;

	Position2D getRandomPosition(const float screenWidth, const float screenHeight, const float spriteSize);

	void setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void setSpriteSize(sf::Sprite& sprite, float desiredSize);
	void setSpriteOrigin(sf::Sprite& sprite, float desiredOriginX, float desiredOriginY);
	void setTextOrigin(sf::Text& text, float desiredOriginX, float desiredOriginY);

	bool isCirclesCollide(Position2D circle1Position, Position2D circle2Position, float circle1Radius, float circle2Radius);
	bool CheckClick(const sf::Vector2<int> mousePosition, const sf::Rect<float> elemRect);
}
