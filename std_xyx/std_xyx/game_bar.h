#pragma once
//#include "game_obj.h"
#include "game_img.h"

class GameBar :public GameObj
{
public:
	GameBar() = default;
	~GameBar() = default;
	GameBar(const Vector2 pos);

	void on_enter() override;
	void on_update(float delta) override;
	void on_render() override;
	GameImg* get_img_bg();
	GameImg* get_img_pro();
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
	GameImg* img_bg = nullptr;
	// 进度条
	GameImg* img_pro = nullptr;
	// 当前值
	float percent_num = 0.0f;
	// 最大值
	SDL_Point max_value = { 0,0 };
	// 进度条方向
	bool is_horizontal = true;
};

