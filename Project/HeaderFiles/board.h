#pragma once

#include "pinkBrick.h"
#include "redBrick.h"
#include "ball.h"
#include "paddle.h"

#include <list>

class Board
{
private:
   std::list<Brick*> bricks { };
   float lastVIsibilityChange { 0 };
	float visibleInterval { 10 };
   float invisibleInterval { 3 };

   bool checkBrickCollision(const Brick& brick, const Ball& ball);
	float getDistance(float x1, float y1, float x2, float y2);

public:
   Board();
   ~Board();

   void draw();
   void checkBricksCollision(Ball& ball);
   void checkUpdateAbilites(const int& elapsedTime);

   const std::list<Brick*>& getBricks() const { return bricks; }
};