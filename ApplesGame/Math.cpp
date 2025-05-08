#include <cstdlib>
#include "Math.h"
#include <SFML/Graphics.hpp>

namespace ApplesGame {
	Position2D getRandomPosition(const float screenWidth, const float screenHeight, const float spriteSize) {
		return {
			spriteSize /2.f + rand() / (float)RAND_MAX * (screenWidth - spriteSize),
			spriteSize /2.f + rand() / (float)RAND_MAX * (screenHeight - spriteSize)
		};
	}
	void setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight) {
		const sf::FloatRect spriteBounds = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteBounds.width, desiredHeight / spriteBounds.height };
		sprite.setScale(scale);
	}
	void setSpriteSize(sf::Sprite& sprite, float desiredSize) {
		setSpriteSize(sprite, desiredSize, desiredSize);
	}
	void setSpriteOrigin(sf::Sprite& sprite, float originX, float originY) {
		const sf::FloatRect spriteBounds = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteBounds.width, originY * spriteBounds.height);
	}
	void setTextOrigin(sf::Text& text, float originX, float originY) {
		const sf::FloatRect textBounds = text.getLocalBounds();
		text.setOrigin(originX * textBounds.width, originY * textBounds.height);
	}
}
