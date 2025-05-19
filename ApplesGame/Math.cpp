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
	bool isCirclesCollide(Position2D circle1Position, Position2D circle2Position, float circle1Radius, float circle2Radius) {
		float circleDistance = (circle1Position.x - circle2Position.x) * (circle1Position.x - circle2Position.x) + (circle1Position.y - circle2Position.y) * (circle1Position.y - circle2Position.y);
		float circleRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius) / 4.f;
		return circleDistance < circleRadiusSum;
	}
	bool CheckClick(const sf::Vector2<int> mousePosition, const sf::Rect<float> elemRect) {
		const float rangeX[2] = { elemRect.left, elemRect.left + elemRect.width };
		const float rangeY[2] = { elemRect.top, elemRect.top + elemRect.height };
		return (
			((float)rangeX[0] < mousePosition.x && mousePosition.x < (float)rangeX[1]) &&
			((float)rangeY[0] < mousePosition.y && mousePosition.y < (float)rangeY[1])
			);
	}
}
