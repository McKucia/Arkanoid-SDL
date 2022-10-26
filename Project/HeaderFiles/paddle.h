#pragma once
#include "configuration.h"
#include "entity.h"
#include "../../Framework/inc/Framework.h"
#include "../HeaderFiles/direction.h"

class Paddle : public Entity
{
private:
	float speed { Configuration::paddleSpeed };
	float maxSpeed { Configuration::paddleSpeed * 2.0f };
	float minSpeed { Configuration::paddleSpeed * 0.5f };

public:
	Paddle();
	~Paddle() {};

	void move(Direction direction, float deltaTime);
	void resetPosition();

	const float& getSpeed() const { return speed; }
	void setSpeed(const float& _speed) { speed = std::max(minSpeed, std::min(_speed, maxSpeed)); }
};