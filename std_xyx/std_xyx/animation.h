#pragma once

#include "res_mgr.h"
#include "camera.h"

#include <vector>

/*������*/
class Animation
{
public:
	Animation(const std::string name, const int num) :name(name), num(num)
	{
		timer.set_one_shot(false);
		timer.set_on_timeout([&]()
			{
				++idx_frame;
				if (idx_frame > num)
				{
					idx_frame = is_loop ? 1 : num;
					if (!is_loop && on_finished)
					{
						on_finished();
					}
				}
			}
		);
	}
	~Animation() = default;

	/*���ö���״̬*/
	void reset()
	{
		timer.restart();
		idx_frame = 0;
	}

	/*����ê��*/
	void set_anchor_mode(AnchorMode mode)
	{
		anchor_mode = mode;
	}
	/*����ѭ��*/
	void set_loop(bool loop)
	{
		is_loop = loop;
	}
	/*����֡���*/
	void set_interval(float val)
	{
		timer.set_wait_time(val);
	}
	/*����λ��*/
	void set_position(const Vector2& pos)
	{
		position = pos;
	}
	/*��������*/
	void set_center(const SDL_FPoint& pos)
	{
		center = pos;
	}
	/*���ýǶ�*/
	void set_rotation(double val)
	{
		angle = val;
	}

	/*��ȡ��ǰ֡����*/
	int get_idx_frame()
	{
		return idx_frame;
	}
	/*��ȡ��ǰ֡����*/
	SDL_Texture* get_Texture()
	{
		return ResMgr::instance()->find_texture(name + std::to_string(idx_frame));
	}
	/*�����Ƿ񲥷����*/
	bool check_finished()
	{
		if (is_loop)
		{
			return false;
		}
		return (idx_frame == num);
	}
	/*��������*/
	void on_update(float delta)
	{
		timer.on_update(delta);
	}
	/*���ƶ���*/
	void on_render(const Camera& camera) //const
	{
		SDL_Texture* texture = get_Texture();

		int w, h;
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

		SDL_Rect src = { 0,0,w,h };

		float x, y;

		switch (anchor_mode)
		{
		case AnchorMode::TOPLEFT:
			x = position.x;
			y = position.y;
			break;
		case AnchorMode::TOPCENTER:
			x = position.x - w / 2;
			y = position.y;
			break;
		case AnchorMode::TOPRIGHT:
			x = position.x - w;
			y = position.y;
			break;
		case AnchorMode::LEFTCENTER:
			x = position.x;
			y = position.y - h / 2;
			break;
		case AnchorMode::CENTER:
			x = position.x - w / 2;
			y = position.y - h / 2;
			break;
		case AnchorMode::RIGHTCENTER:
			x = position.x - w;
			y = position.y - h / 2;
			break;
		case AnchorMode::BOTTOMLEFT:
			x = position.x;
			y = position.y - h;
			break;
		case AnchorMode::BOTTOMCENTER:
			x = position.x - w / 2;
			y = position.y - h;
			break;
		case AnchorMode::BOTTOMRIGHT:
			x = position.x - w;
			y = position.y - h;
			break;
		}

		SDL_FRect dst = { x, y, (float)w, (float)h };

		camera.render_texture(texture, &src, &dst, angle, &center);
	}
	/*���ûص�����*/
	void set_on_finished(std::function<void()> func)
	{
		on_finished = func;
	}

private:
	/*��ʱ��*/
	Timer timer;
	/*λ��*/
	Vector2 position;
	// ��ת
	double angle = 0;
	// ���ĵ�
	SDL_FPoint center = { 0 };
	// ֡����
	size_t idx_frame = 0;
	// �Ƿ�ѭ��
	bool is_loop = true;
	// ����������Ļص�����
	std::function<void()> on_finished;
	// ��Դ��
	const std::string name;
	// ��Դ����
	const int num;
	// ê������
	AnchorMode anchor_mode = AnchorMode::CENTER;
};

