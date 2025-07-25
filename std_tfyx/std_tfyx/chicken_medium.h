#pragma once

#include "chicken.h"

extern Atlas atlas_chicken_medium;

class ChickenMedium :public Chicken
{
public:
	ChickenMedium()
	{
		ani_run.add_frame(&atlas_chicken_medium);

		speed = 50.0f;
	}
	~ChickenMedium() = default;
};
