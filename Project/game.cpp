#include "../Framework/inc/Framework.h"
#include "../Framework/src/launch.cpp"
#include "HeaderFiles/paddle.h"
#include "HeaderFiles/brick.h"
#include "HeaderFiles/board.h"
#include "HeaderFiles/cursor.h"
#include "HeaderFiles/ball.h"
#include "HeaderFiles/ability.h"
#include "HeaderFiles/direction.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <memory>
#include <stdio.h>
#include <string>

// g++ SourceFiles/configuration.cpp SourceFiles/ability.cpp SourceFiles/redBrick.cpp SourceFiles/pinkBrick.cpp SourceFiles/cursor.cpp SourceFiles/ball.cpp SourceFiles/board.cpp SourceFiles/paddle.cpp SourceFiles/brick.cpp game.cpp -std=c++17 -I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2 -lSDL2_image -w

class MyFramework : public Framework {

private:
	const int screenWidthDefault { 800 };
	const int screenHeightDefault { 600 };
	bool isCursorVisible { true };
	Sprite* background {};
	Paddle* paddle {};
	Board* board {};
	Ball* ball {};
	std::list<std::unique_ptr<Ability>> abilities {};
	Cursor* cursor {};
	Direction direction = Direction::NONE;
	float mouseX {}, mouseY {};
	std::chrono::steady_clock::time_point lastUpdate {}, startTime {};
	float deltaTime {};
	float lastAbilitySpawn { 0 };
	// seconds
	float abilitySpawnInterval { 20 };

	int getElapsedTime() 
	{
		auto now = std::chrono::steady_clock::now();
		int elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(now - startTime).count() / 1000000.0f;
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 100000.0f;
		lastUpdate = now;

		return elapsedTime;
	}

	void resetGame() {
		isCursorVisible = true;
		ball->setReleased(false);
		ball->resetPosition();
		paddle->resetPosition();
		board = new Board();
		startTime = std::chrono::steady_clock::now();
	}

public:
	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = Configuration::screenWidth;
		height = Configuration::screenHeight;
		fullscreen = false;
	}

	virtual bool Init() {
		startTime = std::chrono::steady_clock::now();
		showCursor(false);
		background = createSprite("./data/background.jpg");
		setSpriteSize(background, Configuration::screenWidth, Configuration::screenHeight);
		
		paddle = new Paddle();
		board = new Board();
		ball = new Ball();
		cursor = new Cursor();

		return true;
	}

	virtual void Close() {		
		delete board;
		delete ball;
		delete cursor;
		delete paddle;

		abilities.clear();
		destroySprite(background);
	}

	virtual bool Tick() {
		auto elapsedTime = getElapsedTime();

        drawTestBackground();
		drawSprite(background, 0, 0);

		if(elapsedTime - lastAbilitySpawn == abilitySpawnInterval) {
			lastAbilitySpawn = elapsedTime;
			abilities.push_back(std::make_unique<Ability>());
		}

		// move
		paddle->move(direction, deltaTime);
		ball->move(*paddle, deltaTime);
		

		// collisions
		board->checkUpdateAbilites(elapsedTime);
		board->checkBricksCollision(*ball);
		bool ballHitBottom = ball->checkCollisions(*paddle);

		// draw
		paddle->draw();
		board->draw();
		ball->draw();
		if(isCursorVisible) 
			cursor->draw();

		for (auto& ability : abilities) {
			ability->move(deltaTime);
			ability->draw();
			bool collidedWithBottomWall = ability->checkWallCollision();
			bool collidedWithPaddle = ability->checkPaddleCollision(*paddle);

			// remove ability object
			if(collidedWithPaddle || collidedWithBottomWall) {
				auto it = abilities.begin();
				auto endIt = abilities.end();
				while (it != endIt)
				{
					if (ability == *it) 
						it = abilities.erase(it);
					else
						++it;
				}
			}
		}
		
		if(ballHitBottom)
			resetGame();
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		mouseX = x - cursor->getWidth() / 2;
		mouseY = y - cursor->getHeight() / 2;

		cursor->setPositionX(mouseX);
		cursor->setPositionY(mouseY);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if (!ball->isReleased())
            ball->launch(*paddle, mouseX - ball->getPositionX(), mouseY - ball->getPositionY(), deltaTime);
		isCursorVisible = false;
	}

	virtual void onKeyPressed(FRKey k) {
		direction = (Direction)k;
	}

	virtual void onKeyReleased(FRKey k) {
		if(direction == (Direction)k)
			direction = Direction::NONE;
	}
	
	virtual const char* GetTitle() override
	{
		return "Arcanoid";
	}

	void setScreenSize(int argc, char *argv[])
	{
		int screenWidth = 0, screenHeight = 0;

		for (int i = 0; i < argc; ++i) 
		{	
			if(argc < 4) break;
			if (std::string(argv[i]) == "-window") {
				screenWidth = atoi(argv[i + 1]);
				screenHeight = atoi(argv[i + 2]);
			}
		}

		Configuration::screenWidth = screenWidth <= 500 || screenWidth >= 1000? screenWidthDefault : screenWidth;
		Configuration::screenHeight = screenHeight <= 300 || screenHeight >= 1000? screenHeightDefault : screenHeight;
	}
};

int main(int argc, char *argv[])
{
	MyFramework* myFramework = new MyFramework();
	myFramework->setScreenSize(argc, argv);
	return run(myFramework);
}
