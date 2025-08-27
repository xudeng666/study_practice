#pragma once
#include "game_obj.h"

#include <SDL_ttf.h>

class GameLable :public GameObj
{
public:
	GameLable() = default;
	~GameLable();
	GameLable(const Vector2 pos);

	void on_enter() override;
	void on_update(float delta) override;
	void on_render() override;
	/*设置尺寸*/
	virtual void set_size();
	/*设置文本内容*/
	void set_lable_text(const std::string str);
	/*设置正文颜色*/
	void set_lable_color(const int value);
	/*设置阴影开启*/
	void set_is_shade(bool is);
	/*设置阴影颜色*/
	void set_shade_color(const int value);
	/*设置阴影位置*/
	void set_pos_shade(const SDL_Point pos);
	/*设置字体*/
	void set_font(std::string font);
	/*获取字体*/
	TTF_Font* get_font();

protected:
	// 文本内容
	std::string lable_text = "";
	// 正文颜色
	int color_lable = 0xFFFFFFFF;		//ARGB
	// 是否显示阴影
	bool is_shade = false;	// 是否有阴影
	// 阴影颜色
	int color_shade = 0xFFFFFFFF;		//ARGB
	// 阴影相对于正文的位置
	SDL_Point pos_shade = { -1,1 };
	// 字体指针
	TTF_Font* font = nullptr;
};

/*
* TTF_RenderUTF8_Blended(font, str_score.c_str(), { 55, 55, 55, 255 });
TTF_RenderUTF8_Blended(font, str_score.c_str(), { 255, 255, 255, 255 });
SDL_CreateTextureFromSurface(renderer, suf_score_bg);
SDL_CreateTextureFromSurface(renderer, suf_score_fg);
*/