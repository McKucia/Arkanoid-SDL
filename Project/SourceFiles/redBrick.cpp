#include "../HeaderFiles/redBrick.h"
#include <iostream>

RedBrick::RedBrick(float _posX, float _posY) 
	: Brick(Configuration::brickWidth, Configuration::brickHeight, Configuration::redBrickSpritePath)
{
	posX = _posX;
	posY = _posY;
}