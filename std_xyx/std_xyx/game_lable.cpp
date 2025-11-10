#include "game_lable.h"
#include "res_mgr.h"
#include "game_wnd.h"
#include "SDL_util.h"

INIT_TYPE_NAME(GameLable);

GameLable::~GameLable()
{
	font = nullptr;
	anchor_node.reset();
}

void GameLable::on_init()
{
	GameObj::on_init();
	anchor_node = TreeNode::create_obj<GameObj>("anchor_node");
	anchor_node->set_anchor_mode(lable_anchor_mode);
	anchor_node->set_anchor_referent_mode(lable_anchor_mode);
	anchor_node->set_anchor_referent_node(self_node);
}

void GameLable::on_enter()
{
	GameObj::on_enter();
}

void GameLable::on_update(float delta)
{
	GameObj::on_update(delta);
}

void GameLable::on_render()
{
	if (!is_display || !font) return;
	if (is_shade)
	{
		SDL_Color color_s = get_SDLColor_ARGB(color_shade);
		SDL_Surface* suf_shade = TTF_RenderUTF8_Blended(font, lable_text.c_str(), color_s);
		SDL_Texture* tex_shade = SDL_CreateTextureFromSurface(GameWnd::instance()->get_renderer(), suf_shade);

		anchor_node->set_size({ suf_shade->w,suf_shade->h });
		anchor_node->set_position(pos_lable + pos_shade);
		SDL_Rect rect_shade = anchor_node->get_Rect();

		GameWnd::instance()->render_texture(tex_shade, nullptr, &rect_shade);
		SDL_DestroyTexture(tex_shade);
		SDL_FreeSurface(suf_shade);

	}
	SDL_Color color_l = get_SDLColor_ARGB(color_lable);
	SDL_Surface* suf_lable = TTF_RenderUTF8_Blended(font, lable_text.c_str(), color_l);
	SDL_Texture* tex_lable = SDL_CreateTextureFromSurface(GameWnd::instance()->get_renderer(), suf_lable);

	anchor_node->set_size({ suf_lable->w,suf_lable->h });
	anchor_node->set_position(pos_lable);
	SDL_Rect rect_lable = anchor_node->get_Rect();

	GameWnd::instance()->render_texture(tex_lable, nullptr, &rect_lable);
	SDL_DestroyTexture(tex_lable);
	SDL_FreeSurface(suf_lable);

	GameObj::on_render();
}

void GameLable::set_lable_text(const std::string str)
{
	lable_text = str;
}

void GameLable::set_lable_color(const int value)
{
	color_lable = value;
}

void GameLable::set_is_shade(bool is)
{
	is_shade = is;
}

void GameLable::set_shade_color(const int value)
{
	color_shade = value;
}

void GameLable::set_pos_lable(const Vector2 pos)
{
	pos_lable = pos;
}

void GameLable::set_pos_shade(const Vector2 pos)
{
	pos_shade = pos;
}

/*设置字体*/
void GameLable::set_font(std::string name)
{
	font = ResMgr::instance()->find_ttf(name);
}
/*获取字体*/
TTF_Font* GameLable::get_font()
{
	return font;
}

void GameLable::set_lable_anchor_mode(AnchorMode mode)
{
	if (lable_anchor_mode == mode) return;
	lable_anchor_mode = mode;
}

AnchorMode GameLable::get_lable_anchor_mode()
{
	return lable_anchor_mode;
}