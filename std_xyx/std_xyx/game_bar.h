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
	/*设置背景纹理*/
	void set_img_bg_texture(const std::string name);
	/*设置资源*/
	void set_img_pro_texture(const std::string name);
	/*设置当前值*/
	void set_point_num(int num);
	/*设置初始值值*/
	void set_init_point(int num);
	/// <summary>
	/// 设置进度条百分比
	/// </summary>
	/// <param name="num">0.0~1.0</param>
	void set_percent_num(float num);
	void set_is_point(bool point);

protected:
	// 背景
	GameImg* img_bg = nullptr;
	// 进度条
	GameImg* img_pro = nullptr;
	// 当前值
	float percent_num = 0.0f;
	// 是否点状进度条
	int is_point = false;
	// 点数
	int point_num = 0;
	// 初始点数
	int init_point = 0;
};

