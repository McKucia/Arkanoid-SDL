#pragma once
#include "configuration.h"
#include "../../Framework/inc/Framework.h"

#include <iostream>

class Entity
{
protected:
	float width { 0 }, height { 0 };
	float posX { 0 }, posY { 0 };
	Sprite* sprite { };

public:
	Entity(int _width, int _height, const char* spritePath) : width(_width), height(_height) {
		sprite = createSprite(spritePath);
		setSpriteSize(sprite, _width, _height);
	}

    virtual ~Entity() {
		destroySprite(sprite);
	}

	void draw() {
		drawSprite(sprite, posX, posY);
	}

    const float& getWidth()  	const { return width; }
	const float& getHeight() 	const { return height; }
	const float& getPositionX() const { return posX; }
	const float& getPositionY() const { return posY; }

    void setPositionX(const float& _posX) { posX = _posX; }
	void setPositionY(const float& _posY) { posY = _posY; }
};