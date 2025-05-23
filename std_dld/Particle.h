#pragma once
#include "util.h"
#include "Vector2.h"
#include "Atlas.h"


/*������*/
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
	int timer = 0;		//�������Ŷ�ʱ��
	int lifespan = 0;	//��֡����ʱ��
	int idx_frame = 0;	//��ǰ����֡
	Vector2 position;	//��������
	bool valid = true;	//�Ƿ���Ч
	Atlas* atlas = nullptr;//ͼ��
};

