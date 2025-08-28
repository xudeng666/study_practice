#include "game_ani.h"
#include "res_mgr.h"


GameAni::GameAni(const Vector2 pos, const std::string name, const int num): GameImg(pos, name), num(num)
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

void GameAni::on_enter()
{
	reset();
	GameImg::on_enter();
}

void GameAni::on_update(float delta)
{
	timer.on_update(delta);
	set_Texture();
	set_size();
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
	idx_frame = 1;
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

/*��ȡ��ǰ֡����*/
int GameAni::get_idx_frame()
{
	return idx_frame;
}

/*���õ�ǰ֡����*/
void GameAni::set_Texture()
{
	texture = ResMgr::instance()->find_texture(res_name + std::to_string(static_cast<int>(idx_frame)));
}

/*��ȡ��ǰ֡����*/
SDL_Texture* GameAni::get_Texture()
{
	return texture;
}

/*�����Ƿ񲥷����*/
bool GameAni::check_finished()
{
	if (is_loop)
	{
		return false;
	}
	return (idx_frame == num);
}

/*���ûص�����*/
void GameAni::set_on_finished(std::function<void()> func)
{
	on_finished = func;
}
