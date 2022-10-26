#pragma once
#include "brick.h"
#include "../../Framework/inc/Framework.h"

class PinkBrick : public Brick
{
public:
	PinkBrick(float _posX, float _posY);
	~PinkBrick() {};

	static bool areVisible;
};
