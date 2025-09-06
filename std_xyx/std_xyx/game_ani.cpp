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

/*重置动画状态*/
void GameAni::reset()
{
	timer.restart();
	idx_frame = 0;
}
/*设置循环*/
void GameAni::set_loop(bool loop)
{
	is_loop = loop;
}
/*设置帧间隔*/
void GameAni::set_interval(float val)
{
	timer.set_wait_time(val);
}
/*设置资源起始序号*/
void GameAni::set_res_int_val(int val)
{
	res_int_val = val;
}

/*获取当前帧索引*/
int GameAni::get_idx_frame()
{
	return idx_frame;
}

/*获取帧数量*/
int GameAni::get_res_num()
{
	return res_num;
}

void GameAni::set_res_name(const Ani_Res& res)
{
	res_name = res.name;
	res_num = res.num;
}

/*设置当前帧纹理*/
void GameAni::set_texture()
{
	texture = ResMgr::instance()->find_texture(res_name + std::to_string(static_cast<int>(idx_frame + res_int_val)));
	if (!texture)
	{
		std::cout << ID << " texture null" << std::endl;
	}
}

/*获取当前帧纹理*/
//SDL_Texture* GameAni::get_texture()
//{
//	if (!texture)
//	{
//		set_texture();
//	}
//	return texture;
//}

/*动画是否播放完毕*/
bool GameAni::check_finished()
{
	if (is_loop)
	{
		return false;
	}
	return (idx_frame == res_num - 1);
}

/*设置回调函数*/
void GameAni::set_on_finished(std::function<void()> func)
{
	on_finished = func;
}
