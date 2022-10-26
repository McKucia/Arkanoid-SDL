#include "../HeaderFiles/ball.h"
#include <iostream>
#include <cmath>

Ball::Ball() 
	: Entity(Configuration::ballDiameter, Configuration::ballDiameter, Configuration::ballSpritePath)
{
	resetPosition();
}

void Ball::launch(const Paddle& paddle, const float& initialVelocityX, const float& initialVelocityY, float deltaTime)
{
	velocityX = initialVelocityX;
	velocityY = initialVelocityY;

	released = true;

	move(paddle, deltaTime);
}

void Ball::move(const Paddle& paddle, const float& deltaTime)
{
	if(!released) {
		posX = paddle.getPositionX() + (Configuration::paddleWidth - width) / 2;
		posY = paddle.getPositionY() - height;
		return;
	}

	double relativeVelocity = speed / sqrt(velocityX * velocityX + velocityY * velocityY);
	posX += relativeVelocity * velocityX * deltaTime;
	posY += relativeVelocity * velocityY * deltaTime;
}

bool Ball::checkCollisions(const Paddle& paddle) {
	checkPaddleCollision(paddle);
	return checkWallCollision();
}

bool Ball::checkWallCollision()
{
	if(posX + width >= Configuration::screenWidth || posX <= 0) {
		velocityX *= -1;
	}
	else if(posY <= 0) {
		velocityY *= -1;
	}
	else if(posY + height >= Configuration::screenHeight) {
		return true;
	}
	else {
		return false;
	}

	lastCollision = LastCollision::WALL; // if any of conditions were true
	return false;
}

void Ball::checkPaddleCollision(const Paddle& paddle)
{
	if(lastCollision == LastCollision::PADDLE) return;

	if (posX >= paddle.getPositionX() + paddle.getWidth() ||
		posX + width <= paddle.getPositionX() ||
		posY >= paddle.getPositionY() + paddle.getHeight() ||
		posY + height <= paddle.getPositionY())
	{
		return;
	}

	float paddleRangeLeft = paddle.getPositionX() + paddle.getWidth() - (2.0f / 3.0f * paddle.getWidth());
	float paddleRangeMiddle = paddle.getPositionX() + paddle.getWidth() - (paddle.getWidth() / 3.0f);

	// left edge of paddle
	if ((posX + width > paddle.getPositionX())
	    && (posX + width / 2 < paddleRangeLeft))
	{
		velocityY -= edgeHitAdder;
		velocityX -= edgeHitAdder;
	}
	// right edge of paddle
	else if ((posX <= paddle.getPositionX() + paddle.getWidth())
	    && (posX > paddleRangeMiddle))
	{
		velocityY -= edgeHitAdder;
		velocityX += edgeHitAdder;
	}
	velocityY *= -1;
	setSpeed(speed * speedUpMultiplier);
	
	lastCollision = LastCollision::PADDLE;
}

void Ball::resetPosition()
{
	posX = (Configuration::screenWidth - Configuration::ballDiameter) / 2;
	posY = Configuration::screenHeight - Configuration::ballDiameter - Configuration::paddleHeight - Configuration::paddleMarginBottom;
}