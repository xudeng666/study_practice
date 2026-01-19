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
	int w = 0;
	int h = 0;

	int r = ranks < 1 ? len : ranks;

	int wn = 0;
	int hn = 0;
	int x = 0;
	int y = 0;

	for (size_t i = 0; i < len; i++)
	{
		auto child = children[i];
		if (!child->get_display())
		{
			continue;
		}

		child->set_anchor_mode(AnchorMode::TOPLEFT);
		child->set_anchor_referent_mode(AnchorMode::TOPLEFT);
		child->set_anchor_referent_node(get_self_node());
		child->set_enable_angle(false);

		SDL_Point c_size = child->get_size();

		child->set_position(wn + sub_interval.x * x, h + sub_interval.y * y);

		wn += c_size.x;
		hn = hn > c_size.y ? hn : c_size.y;

		x++;

		if (x >= r)
		{
			wn += (x - 1) * sub_interval.x;
			w = w > wn ? w : wn;
			h += hn;
			x = 0;
			wn = 0;
			hn = 0;
			y++;
		}
	}

	if (x > 0)
	{
		wn += (x - 1) * sub_interval.x;
	}
	w = w > wn ? w : wn;

	if (x == 0)
	{
		y--;
	}
	h += hn;
	h += sub_interval.y * y;

	set_size(w, h);
}