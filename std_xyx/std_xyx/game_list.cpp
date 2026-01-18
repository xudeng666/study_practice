#include "game_list.h"

INIT_TYPE_NAME(GameList);

GameList::~GameList()
{
}

void GameList::on_init()
{
	GameObj::on_init();
}

void GameList::on_enter()
{
	GameObj::on_enter();
}

void GameList::on_update(float delta)
{
	GameObj::on_update(delta);
}

void GameList::on_render()
{
	if (!is_display ) return;
	GameObj::on_render();
}

void GameList::on_exit()
{
	GameObj::on_exit();
}

void GameList::on_input(const SDL_Event& event)
{
	GameObj::on_input(event);
}

const SDL_Point& GameList::get_size() const
{
	if (map_type == TextureMapType::AUTO)
	{
		SDL_Point s = size;

		return s;
	}
	return size;
}

void GameList::children_change()
{
	int len = children.size();
	int undisplay = 0;
	int w = 0;
	int h = 0;
	for (size_t i = 0; i < len; i++)
	{
		auto child = children[i];
		if (!child->get_display())
		{
			undisplay++;
			continue;
		}

		child->set_anchor_mode(AnchorMode::TOPLEFT);
		child->set_anchor_referent_mode(AnchorMode::TOPLEFT);
		child->set_anchor_referent_node(get_self_node());
		child->set_enable_angle(false);

		SDL_Point c_size = child->get_size();

		int x = i - undisplay;

		if (ranks < 1)// 列数无限
		{
			child->set_position(w,0);
			w += c_size.x;
			h = h > c_size.y ? h : c_size.y;
			continue;
		}
		else
		{
			for (size_t j = 0; j < ranks; j++)// 列数有限
			{
				/*需要分层计算
				* 1、新增层数变量n=0,x/ranks就是当前元素所在层数
				* 2、新增wn，统计当前层目前宽度,wn += c_size.x;w = w > wn ? w : wn;
				* 3、新增hn,统计每层最高元素，然后同w和wn的计算
				*/
			}
		}

	}
	set_size(w, h);
}