#pragma once
#include "configuration.h"
#include "entity.h"
#include "../../Framework/inc/Framework.h"

class Brick : public Entity
{
public:
   	Brick(float _posX, float _pos, const char* _spritePath);
	~Brick() {};
};
