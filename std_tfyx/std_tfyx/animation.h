#pragma once
#include "atlas.h"
#include "camera.h"

#include <vector>

/*������*/
class Animation
{
public:
	Animation()
	{
		timer.set_one_shot(false);
		timer.set_on_timeout([&]()
			{
				++idx_frame;
				if (idx_frame >= frame_list.size())
				{
					idx_frame = is_loop ? 0 : frame_list.size() - 1;
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

	/**
	* ���֡����
	* @param texture ͼ����Դ
	* @param num ����
	*/
	void add_frame(SDL_Texture* texture, int num)
	{
		int w, h;
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

		int wf = w / num;

		for (int i = 0; i < num; i++)
		{
			SDL_Rect src = { i * wf, 0, wf, h };
			frame_list.emplace_back(texture, src);
		}
	}
	/*
	* ���֡����
	* @param atl ͼ����Դ
	*/
	void add_frame(Atlas* atl)
	{
		for (int i = 0; i < atl->get_size(); i++)
		{
			SDL_Texture* texture = atl->get_texture(i);

			int w, h;
			SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

			SDL_Rect src = { 0,0,w,h };
			frame_list.emplace_back(texture, src);
		}
	}

	/*��ȡ��ǰ֡����*/
	int get_idx_frame()
	{
		return idx_frame;
	}
	/*��ȡ��ǰ֡����*/
	SDL_Texture* get_frame()
	{
		return frame_list[idx_frame].texture;
	}
	/*�����Ƿ񲥷����*/
	bool check_finished()
	{
		if (is_loop)
		{
			return false;
		}
		return (idx_frame == frame_list.size() - 1);
	}
	/*��������*/
	void on_update(float delta)
	{
		timer.on_update(delta);
	}
	/*���ƶ���*/
	void on_render(const Camera& camera) const
	{
		const Frame& frame = frame_list[idx_frame];

		SDL_FRect dst = { position.x - frame.rect_src.w / 2, position.y - frame.rect_src.h / 2, (float)frame.rect_src.w, (float)frame.rect_src.h };
		camera.render_texture(frame.texture, &frame.rect_src, &dst, angle, &center);
	}
	/*���ûص�����*/
	void set_on_finished(std::function<void()> func)
	{
		on_finished = func;
	}

private:
	struct Frame
	{
		/*�ü�����*/
		SDL_Rect rect_src;
		/*����*/
		SDL_Texture* texture = nullptr;
		Frame() = default;
		Frame(SDL_Texture* texture, const SDL_Rect& src) :texture(texture), rect_src(src) {}
		~Frame() = default;
	};
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
	/*��Դ�б�*/
	std::vector<Frame> frame_list;
	// ����������Ļص�����
	std::function<void()> on_finished;
};

