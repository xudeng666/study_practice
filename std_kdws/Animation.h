#pragma once
#include "util.h"
#include "Atlas.h"
#include <functional>

/*������*/
class Animation
{
public:
	enum class AnchorMode
	{
		CENTER,
		BOTTOMCENTER
	};
public:
	Animation()
	{
		timer.set_one_shot(false);
		timer.set_callback([&]()
			{
				if (++idx_frame>=frame_list.size())
				{
					idx_frame = is_loop ? 0 : frame_list.size() - 1;
					if (!is_loop && callback)
					{
						callback();
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
	void set_interval(int val)
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
		int h = img->getwidth();
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
		for (size_t i = 0; i < atl->get_size(); i++)
		{
			IMAGE* img = atl->getImage(i);
			Rect src = {0, 0, img->getwidth(), img->getheight()};
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
	void on_update(int delta)
	{
		timer.on_update(delta);
	}
	/*���ƶ���*/
	void on_draw()
	{
		const Frame fm = frame_list[idx_frame];
		Rect dst;
		dst.x = position.x - fm.rect_src.w / 2;
		dst.y = (anchor_mode == AnchorMode::CENTER) ? position.y - fm.rect_src.h / 2 : position.y - fm.rect_src.h;
		dst.w = fm.rect_src.w;
		dst.h = fm.rect_src.h;
		putimage_alpha_ex(fm.img, &dst, &fm.rect_src);
	}
	/*���ûص�����*/
	void set_callback(std::function<void()> callback)
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
	// ê������
	AnchorMode anchor_mode = AnchorMode::CENTER;
};

