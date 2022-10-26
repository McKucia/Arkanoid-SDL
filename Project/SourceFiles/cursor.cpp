#include "../HeaderFiles/cursor.h"
#include <iostream>

Cursor::Cursor() 
	: Entity(Configuration::cursorWidth, Configuration::cursorHeight, Configuration::cursorSpritePath)
{
	posX = (Configuration::screenWidth - Configuration::cursorWidth) / 2;
	posY = (Configuration::screenHeight - Configuration::cursorHeight) / 2;
}