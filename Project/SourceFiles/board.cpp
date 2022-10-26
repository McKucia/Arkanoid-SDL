#include "../HeaderFiles/board.h"

#include <cmath>
#include <algorithm>

Board::Board()
{
	float centerPosX = (Configuration::screenWidth - Configuration::boardColumns * Configuration::brickWidth) / 2;

   	for (int y = 0; y < Configuration::boardRows; y++) {
		for (int x = 0; x < Configuration::boardColumns; x++) {
			const float brickPosX = centerPosX + x * Configuration::brickWidth;
			const float brickPosY = Configuration::boardUpperLeftPosY + y * Configuration::brickHeight;

			Brick* brick;
			if(x % 2 == 0)
				brick = new PinkBrick(brickPosX, brickPosY);
			else
				brick = new RedBrick(brickPosX, brickPosY);
			bricks.push_back(brick);
      	}
   	}
}

Board::~Board()
{
	for (auto brick : bricks)
    	delete brick;

   	bricks.clear();
}

void Board::draw()
{
	for(auto& brick : bricks)
	{
		auto pinkBrick = dynamic_cast<PinkBrick*>(brick);
		if (pinkBrick != nullptr && !PinkBrick::areVisible)
			continue;
			
		brick->draw();
	}
}

void Board::checkBricksCollision(Ball& ball)
{
    float closestBrickDistance = -1;
	float ballCenterX = ball.getPositionX() + ball.getWidth() / 2;
	float ballCenterY = ball.getPositionY() + ball.getHeight() / 2;

	Brick* closestBrick = nullptr;
	for(const auto& brick : bricks)
	{
		// check if brick is pink brick
		auto pinkBrick = dynamic_cast<PinkBrick*>(brick);
		if (pinkBrick != nullptr && !PinkBrick::areVisible)
			continue;

		if (checkBrickCollision(*brick, ball))
        {
			float brickCenterX = brick->getPositionX() + brick->getWidth() / 2;
			float brickCenterY = brick->getPositionY() + brick->getHeight() / 2;
			const float distance = getDistance(ballCenterX, ballCenterY, brickCenterX, brickCenterY);

			if (closestBrickDistance == -1 || distance < closestBrickDistance)
			{
				closestBrickDistance = distance;
				closestBrick = brick;
			}
        }
	}

	if(closestBrick != nullptr)
	{
		ball.setLastCollision(Ball::LastCollision::BRICK);
		ball.setSpeed(ball.getSpeed() * ball.getSpeedDownMultiplier());
		bricks.remove(closestBrick);

		// if hit from top or bottom
		if (ball.getPositionX() >= closestBrick->getPositionX() || ball.getPositionX() <= closestBrick->getPositionX() + closestBrick->getWidth())
			ball.setVelocityY(-ball.getVelocityY());
		// if hit from left or right
		else
			ball.setVelocityX(-ball.getVelocityX());
	}
}

bool Board::checkBrickCollision(const Brick& brick, const Ball& ball)
{
	float ballCenterX = ball.getPositionX() + ball.getWidth() / 2;
	float ballCenterY = ball.getPositionY() + ball.getHeight() / 2;
	
	int nearestX = std::max(brick.getPositionX(), std::min(ballCenterX, brick.getPositionX() + brick.getWidth()));
    int nearestY = std::max(brick.getPositionY() + brick.getHeight(), std::min(ballCenterY, brick.getPositionY()));

    int distanceX = nearestX - ballCenterX;
    int distanceY = nearestY - ballCenterY;
    return getDistance(ballCenterX, ballCenterY, nearestX, nearestY) <= Configuration::ballDiameter;
}

float Board::getDistance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

void Board::checkUpdateAbilites(const int& elapsedTime)
{
	if(PinkBrick::areVisible && elapsedTime - lastVIsibilityChange == visibleInterval) {
		lastVIsibilityChange = elapsedTime;
		PinkBrick::areVisible = false;
	}
	else if(!PinkBrick::areVisible && elapsedTime - lastVIsibilityChange == invisibleInterval) {
		lastVIsibilityChange = elapsedTime;
		PinkBrick::areVisible = true;
	}
}