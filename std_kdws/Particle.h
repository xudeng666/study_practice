#pragma once
#include "util.h"
#include "Vector2.h"
#include "Atlas.h"


/*粒子类*/
class Particle
{
public:
	Particle() = default;
	Particle(const Vector2& position, Atlas* atlas, int lifespan)
		: position(position), atlas(atlas), lifespan(lifespan) {}
	~Particle() = default;

	void set_atlas(Atlas* atl)
	{
		atlas = atl;
	}

	void set_position(const Vector2& pos)
	{
		position = pos;
	}

	void set_lifespan(int lif)
	{
		lifespan = lif;
	}

	const bool check_valid()const
	{
		return valid;
	}

	void on_updata(int delta)
	{
		timer += delta;
		if (timer >= lifespan)
		{
			timer = 0;
			if (++idx_frame >= atlas->get_imglist_size())
			{
				idx_frame = atlas->get_imglist_size() - 1;
				valid = false;
			}
		}
	}

	void on_draw(const Camera& camera) const
	{
		putimage_alpha(camera, position.x, position.y, atlas->getImageByIndex(idx_frame));
	}

private:
	int timer = 0;		//动画播放定时器
	int lifespan = 0;	//单帧动画时长
	int idx_frame = 0;	//当前动画帧
	Vector2 position;	//世界坐标
	bool valid = true;	//是否有效
	Atlas* atlas = nullptr;//图集
};

