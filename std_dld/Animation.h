#pragma once
#include "util.h"
#include "Atlas.h"
#include <functional>

/*������*/
class Animation :
    public Atlas
{
public:
	Animation() = default;
	~Animation() = default;

	/*���ö���״̬*/
	void reset()
	{
		timer = 0;
		idx_frame = 0;
	}
	/*����ͼ��*/
	void set_atlas(Atlas* atl)
	{
		reset();
		atlas = atl;
	}
	/*����ѭ��*/
	void set_loop(bool loop)
	{
		is_loop = loop;
	}
	/*����֡���*/
	void set_interval(int val)
	{
		interval = val;
	}
	/*��ȡ��ǰ֡����*/
	int get_idx_frame()
	{
		return idx_frame;
	}
	/*��ȡ��ǰ֡ͼƬ*/
	IMAGE* get_frame()
	{
		return atlas->getImageByIndex(idx_frame);
	}
	/*�����Ƿ񲥷����*/
	bool check_finished()
	{
		if (is_loop)
		{
			return false;
		}
		return (idx_frame == atlas->get_imglist_size() - 1);
	}
	/*��������*/
	void on_updata(int delta)
	{
		timer += delta;
		if (timer >= interval)
		{
			timer = 0;
			if (++idx_frame >= atlas->get_imglist_size())
			{
				idx_frame = is_loop ? 0 : atlas->get_imglist_size() - 1;
				if (!is_loop && callback)
				{
					callback();
				}
			}
		}
	}
	/*���ƶ���*/
	void on_draw(int x, int y) const
	{
		putimage_alpha(x, y, atlas->getImageByIndex(idx_frame));
		//putimage_alpha(x, y, get_frame());
	}
	/*���ûص�����*/
	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}

private:
	/*��ʱ��*/
	int timer = 0;
	// ֡���
	int interval = 0;
	// ֡����
	int idx_frame = 0;
	// �Ƿ�ѭ��
	bool is_loop = true;
	// ͼ��
	Atlas* atlas = nullptr;
	// �ص�����
	std::function<void()> callback;
};

