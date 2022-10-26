#include "../HeaderFiles/brick.h"
#include <iostream>

Brick::Brick(float _posX, float _posY, const char* _spritePath) 
	: Entity(Configuration::brickWidth, Configuration::brickHeight, _spritePath)
{
	posX = _posX;
	posY = _posY;
}