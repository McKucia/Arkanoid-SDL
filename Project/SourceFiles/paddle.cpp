#include "../HeaderFiles/paddle.h"
#include <iostream>

Paddle::Paddle()
	: Entity(Configuration::paddleWidth, Configuration::paddleHeight, Configuration::paddleSpritePath)
{
	resetPosition();
}

void Paddle::move(Direction direction, float deltaTime) {
	switch (direction) {
		case Direction::NONE:
			break;
		case Direction::RIGHT:
			if(posX + Configuration::paddleWidth < Configuration::screenWidth) 
				posX += speed * deltaTime;
			break;
		case Direction::LEFT:
			if(posX > 0) 
				posX -= speed * deltaTime;
			break;
		default:
			break;
	}
}

void Paddle::resetPosition() {
	posX = (Configuration::screenWidth - Configuration::paddleWidth) / 2; // center
	posY = Configuration::screenHeight - Configuration::paddleHeight - Configuration::paddleMarginBottom; // little bit above bottom
}