#include "game_lable.h"

GameLable::GameLable(const Vector2 pos)
{
}

GameLable::~GameLable()
{
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
	/*SDL_Surface* suf_shade = TTF_RenderUTF8_Blended(font, lable_text.c_str(), { 55, 55, 55, 255 });
	SDL_Surface* suf_lable = TTF_RenderUTF8_Blended(font, lable_text.c_str(), { 255, 255, 255, 255 });
	SDL_Texture* tex_shade = SDL_CreateTextureFromSurface(GameWnd::instance()->get_renderer(), suf_shade);
	SDL_Texture* tex_lable = SDL_CreateTextureFromSurface(GameWnd::instance()->get_renderer(), suf_lable);
	SDL_Rect rect_dst_score = { _W_ - suf_shade->w - 15, 15, suf_shade->w, suf_shade->h };
	SDL_RenderCopy(GameWnd::instance()->get_renderer(), tex_shade, nullptr, &rect_dst_score);
	rect_dst_score.x -= 2; rect_dst_score.y -= 2;
	SDL_RenderCopy(GameWnd::instance()->get_renderer(), tex_lable, nullptr, &rect_dst_score);
	SDL_DestroyTexture(tex_shade); SDL_DestroyTexture(tex_lable);
	SDL_FreeSurface(suf_shade); SDL_FreeSurface(suf_lable);
	GameObj::on_render();*/
}

void GameLable::set_size()
{
	// 暂定尺寸自动适应
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

void GameLable::set_pos_shade(const SDL_Point pos)
{
	pos_shade = pos;
}

/*设置字体*/
void GameLable::set_font(std::string font)
{
}
/*获取字体*/
TTF_Font* GameLable::get_font()
{
}