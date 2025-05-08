#pragma once

namespace sf {
	class Sprite;
	class Text;
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
}
