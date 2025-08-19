#pragma once

#include "res_mgr.h"
#include "game_img.h"

class GameAni : public GameImg
{
public:
	GameAni() = default;
	~GameAni() = default;
	GameAni(const Vector2 pos, const std::string name, const int num);

	void on_update(float delta) override;
	void on_render() override;
	/*重置动画状态*/
	void reset();
	/*设置循环*/
	void set_loop(bool loop);
	/*设置帧间隔*/
	void set_interval(float val);
	/*获取当前帧索引*/
	int get_idx_frame();
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
	std::function<void()> on_finished;
	// 资源名
	const std::string name;
	// 资源数量
	const int num;
};

