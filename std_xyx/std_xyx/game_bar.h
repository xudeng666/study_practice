#pragma once

#include "game_img.h"

class GameBar :public GameObj
{
public:
	GameBar() = default;
	virtual ~GameBar() = default;

	virtual void on_init() override;
	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;

	DEFINE_TYPE_NAME(GameBar);

	TreeNode_SP get_img_bg();
	TreeNode_SP get_img_pro();
	/// <summary>
	/// 设置进度条百分比
	/// </summary>
	/// <param name="num">0.0~1.0</param>
	void set_percent_num(float num);
	/// <summary>
	/// 设置进度条最大值
	/// </summary>
	/// <param name="value">SDL_Point</param>
	void set_max_value(SDL_Point value);
	/// <summary>
	/// 设置进度条方向
	/// </summary>
	/// <param name="is_h">true 横向 false 纵向</param>
	void set_is_horizontal(bool is_h);

protected:
	// 背景
	TreeNode_WP img_bg;
	// 进度条
	TreeNode_WP img_pro;
	// 当前值
	float percent_num = 0.0f;
	// 最大值
	SDL_Point max_value = { 0,0 };
	// 进度条方向
	bool is_horizontal = true;
};

INIT_TYPE_NAME(GameBar);