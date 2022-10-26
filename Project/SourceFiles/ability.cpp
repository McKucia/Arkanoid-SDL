#include "../HeaderFiles/ability.h"
#include <iostream>
#include <cmath>

Ability::Ability() 
	: Entity(Configuration::abilityWidth, Configuration::abilityHeight, Configuration::abilitySpritePath)
{
	posX = (Configuration::screenWidth - Configuration::abilityHeight) / 2;
	posY = (Configuration::screenHeight - Configuration::abilityWidth) / 2;

	// random number between -5 and 5 exclude 0 and 1
	// in order not to move vertically
	int randomDirections[8]{ -5, -4, -3, -2, 2, 3, 4, 5 };

	velocityX = randomDirections[rand() % 8];
	velocityY = randomDirections[rand() % 8];
}

void Ability::move(const float& deltaTime)
{
	double relativeVelocity = speed / sqrt(velocityX * velocityX + velocityY * velocityY);
	posX += relativeVelocity * velocityX * deltaTime;
	posY += relativeVelocity * velocityY * deltaTime;
}

bool Ability::checkWallCollision()
{
	if(posX + width >= Configuration::screenWidth || posX <= 0) {
		velocityX *= -1;
	}
	else if(posY <= 0) {
		velocityY *= -1;
	}
	else if(posY + height >= Configuration::screenHeight) {
		// true if hit bottom wall - die
		return true;
	}
}

bool Ability::checkPaddleCollision(Paddle& paddle)
{
	if (posX >= paddle.getPositionX() + paddle.getWidth() ||
		posX + width <= paddle.getPositionX() ||
		posY >= paddle.getPositionY() + paddle.getHeight() ||
		posY + height <= paddle.getPositionY())
	{
		return false;
	}

	paddle.setSpeed(paddle.getSpeed() * speedUpMultiplier);
	return true;
}