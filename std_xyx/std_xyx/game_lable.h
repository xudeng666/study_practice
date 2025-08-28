#pragma once

#include <SDL_ttf.h>

#include "game_obj.h"

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
	void set_pos_lable(const Vector2 pos);
	/*设置阴影位置*/
	void set_pos_shade(const Vector2 pos);
	/*设置字体*/
	void set_font(std::string name);
	/*获取字体*/
	TTF_Font* get_font();
	/*设置锚点*/
	void set_anchor_mode(AnchorMode mode);
	/*获取锚点*/
	AnchorMode get_anchor_mode();

protected:
	// 文本内容
	std::string lable_text = "";
	// 正文颜色
	int color_lable = 0xFFFFFFFF;		//ARGB
	// 是否显示阴影
	bool is_shade = false;	// 是否有阴影
	// 阴影颜色
	int color_shade = 0x55555555;		//ARGB
	// 正文的位置
	Vector2 pos_lable = { 0,0 };
	// 阴影相对于正文的位置
	Vector2 pos_shade = { -2,2 };
	// 字体指针
	TTF_Font* font = nullptr;
	// 文本锚点
	AnchorMode anchor_mode = AnchorMode::TOPLEFT;
};