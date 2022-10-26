#include "../HeaderFiles/pinkBrick.h"
#include <iostream>

PinkBrick::PinkBrick(float _posX, float _posY) 
	: Brick(Configuration::brickWidth, Configuration::brickHeight, Configuration::pinkBrickSpritePath)
{
	posX = _posX;
	posY = _posY;
}

bool PinkBrick::areVisible = false;