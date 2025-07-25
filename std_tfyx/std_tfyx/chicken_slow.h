#pragma once

#include "chicken.h"

extern Atlas atlas_chicken_slow;

class ChickenSlow :public Chicken
{
public:
	ChickenSlow()
	{
		ani_run.add_frame(&atlas_chicken_slow);

		speed = 30.0f;
	}
	~ChickenSlow() = default;
};
