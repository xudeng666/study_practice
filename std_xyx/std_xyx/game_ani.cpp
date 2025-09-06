#include "game_ani.h"
#include "res_mgr.h"

GameAni::GameAni()
{
	timer.set_one_shot(false);
	timer.set_on_timeout([&]()
		{
			++idx_frame;
			if (idx_frame >= res_num)
			{
				idx_frame = is_loop ? 0 : res_num - 1;
				if (!is_loop && on_finished)
				{
					on_finished();
				}
			}
		}
	);
}

GameAni::~GameAni()
{
}

void GameAni::on_enter()
{
	reset();
	//set_texture();
	//set_size();
}

void GameAni::on_update(float delta)
{
	timer.on_update(delta);
	GameImg::on_update(delta);
}

void GameAni::on_render()
{
	GameImg::on_render();
}

/*���ö���״̬*/
void GameAni::reset()
{
	timer.restart();
	idx_frame = 0;
}
/*����ѭ��*/
void GameAni::set_loop(bool loop)
{
	is_loop = loop;
}
/*����֡���*/
void GameAni::set_interval(float val)
{
	timer.set_wait_time(val);
}
/*������Դ��ʼ���*/
void GameAni::set_res_int_val(int val)
{
	res_int_val = val;
}

/*��ȡ��ǰ֡����*/
int GameAni::get_idx_frame()
{
	return idx_frame;
}

/*��ȡ֡����*/
int GameAni::get_res_num()
{
	return res_num;
}

void GameAni::set_res_name(const Ani_Res& res)
{
	res_name = res.name;
	res_num = res.num;
}

/*���õ�ǰ֡����*/
void GameAni::set_texture()
{
	texture = ResMgr::instance()->find_texture(res_name + std::to_string(static_cast<int>(idx_frame + res_int_val)));
	if (!texture)
	{
		std::cout << ID << " texture null" << std::endl;
	}
}

/*��ȡ��ǰ֡����*/
//SDL_Texture* GameAni::get_texture()
//{
//	if (!texture)
//	{
//		set_texture();
//	}
//	return texture;
//}

/*�����Ƿ񲥷����*/
bool GameAni::check_finished()
{
	if (is_loop)
	{
		return false;
	}
	return (idx_frame == res_num - 1);
}

/*���ûص�����*/
void GameAni::set_on_finished(std::function<void()> func)
{
	on_finished = func;
}
