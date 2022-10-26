#pragma once
#include "configuration.h"
#include "entity.h"
#include "paddle.h"
#include "../../Framework/inc/Framework.h"

class Ability : public Entity
{
private:
	float velocityX { 0 }, velocityY { 0 };
	float speed { Configuration::abilitySpeed };
	float speedUpMultiplier { 1.4f };

public:
   	Ability();
	~Ability() {};

	void move(const float& deltaTime);
	void checkUpdate(const int& elapsedTime);
	bool checkWallCollision();
	bool checkPaddleCollision(Paddle& paddle);
};
