#pragma once

#include "util.h"
#include "Timer.h"
#include "Atlas.h"
#include "Vector2.h"

#include <vector>
#include <functional>

class Animation
{
public:
	Animation()
	{
		timer.set_one_shot(false);
		timer.set_callback([&]()
			{
				++idx_frame;
				if (idx_frame >= frame_list.size())
				{
					idx_frame = is_loop ? 0 : frame_list.size() - 1;
					if (!is_loop && callback)
					{
						callback();
					}
				}
			});
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

	/**
	* ���֡����
	* @param img ͼ����Դ
	* @param num ����
	*/
	void add_frame(IMAGE* img, int num)
	{
		int w = img->getwidth();
		int h = img->getheight();
		int wf = w / num;
		for (int i = 0; i < num; i++)
		{
			Rect src = { i * wf, 0, wf, h };
			frame_list.emplace_back(img, src);
		}
	}

	/*
	* ���֡����
	* @param atl ͼ����Դ
	*/
	void add_frame(Atlas* atl)
	{
		for (int i = 0; i < atl->get_imglist_size(); i++)
		{
			IMAGE* img = atl->getImage(i);
			Rect src = { 0, 0, img->getwidth(), img->getheight() };
			frame_list.emplace_back(img, src);
		}
	}

	/*��ȡ��ǰ֡����*/
	int get_idx_frame()
	{
		return idx_frame;
	}
	/*��ȡ��ǰ֡ͼƬ*/
	IMAGE* get_frame()
	{
		return frame_list[idx_frame].img;
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
	void on_draw(const Camera& camera)
	{
		const Frame& fm = frame_list[idx_frame];
		Rect dst = { (int)position.x - fm.rect_src.w / 2,(int)position.y - fm.rect_src.h / 2,fm.rect_src.w, fm.rect_src.h };
		putimage_ex(camera, fm.img, &dst, &fm.rect_src);
	}
	/*���ûص�����*/
	void set_call_back(std::function<void()> callback)
	{
		this->callback = callback;
	}

private:
	struct Frame
	{
		/*�ü�����*/
		Rect rect_src;
		/*ͼ����Դ*/
		IMAGE* img = nullptr;
		Frame() = default;
		Frame(IMAGE* image, const Rect& src) :img(image), rect_src(src) {}
		~Frame() = default;
	};
private:
	/*��ʱ��*/
	Timer timer;
	/*λ��*/
	Vector2 position;
	// ֡����
	size_t idx_frame = 0;
	// �Ƿ�ѭ��
	bool is_loop = true;
	/*��Դ�б�*/
	std::vector<Frame> frame_list;
	// ����������Ļص�����
	std::function<void()> callback;
};