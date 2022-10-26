#pragma once
#include "configuration.h"
#include "entity.h"
#include "paddle.h"
#include "brick.h"

#include <list>

class Ball : public Entity
{
public:
   	Ball();
	~Ball() {};

	enum class LastCollision
	{
		WALL,
		PADDLE,
		BRICK
	};

	void launch(const Paddle& paddle, const float& initialVelocityX, const float& initialVelocityY, float deltaTime);
	void move(const Paddle& paddle, const float& deltaTime);
	// true is lose
	bool checkCollisions(const Paddle& paddle);
	void resetPosition();

	const bool& isReleased() 				const { return released; }
	const float& getVelocityX() 			const { return velocityX; }
	const float& getVelocityY() 			const { return velocityY; }
	const float& getSpeed() 				const { return speed; }
	const float& getSpeedDownMultiplier() 	const { return speedDownMultiplier; }

	void setSpeed(const float& _speed) { speed = std::max(minSpeed, std::min(_speed, maxSpeed)); }
	void setVelocityX(const float& _velocityX) { velocityX = _velocityX; }
	void setVelocityY(const float& _velocityY) { velocityY = _velocityY; }
	void setReleased(const bool& _released) { released = _released; }
	void setLastCollision(const LastCollision& _lastCollision) { lastCollision = _lastCollision; }

private:
	bool released { false };
	float speed { Configuration::ballSpeed };
	float minSpeed { Configuration::ballSpeed * 0.4f };
	float maxSpeed { Configuration::ballSpeed * 3.0f };
	float speedUpMultiplier { 1.15f };
	float speedDownMultiplier { 0.9f };
	float velocityX { 0 }, velocityY { 0 };
	// if ball hit right or left edge of paddle, change angle
	float edgeHitAdder { 25.0f };

	LastCollision lastCollision { LastCollision::PADDLE };

	bool checkWallCollision();
	void checkPaddleCollision(const Paddle& paddle);
};
