#pragma once

#include "game_img.h"
#include "timer.h"

struct Ani_Res
{
	std::string name;
	int num;
};

class GameAni : public GameImg
{
public:
	GameAni() = default;
	~GameAni() = default;
	GameAni(const Vector2 pos, const Ani_Res res);

	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;
	/*重置动画状态*/
	void reset();
	/*设置循环*/
	void set_loop(bool loop);
	/*设置帧间隔*/
	void set_interval(float val);
	/*获取当前帧索引*/
	int get_idx_frame();
	/*设置动画资源*/
	void set_res_name(const Ani_Res res);
	/*设置当前帧纹理*/
	void set_Texture();
	/*获取当前帧纹理*/
	SDL_Texture* get_Texture();
	/*动画是否播放完毕*/
	bool check_finished();
	/*设置回调函数*/
	void set_on_finished(std::function<void()> func);

private:
	/*定时器*/
	Timer timer;
	// 帧索引
	int idx_frame = 1;
	// 是否循环
	bool is_loop = true;
	// 动画播放完的回调函数
	std::function<void()> on_finished = nullptr;
	// 资源数量
	int res_num;
};

