#pragma once

#include "game_img.h"
#include "timer.h"

struct Ani_Res
{
	std::string name;
	int num;

	Ani_Res() = default;
	Ani_Res(const std::string name, const int num) :name(name), num(num) {}
	~Ani_Res() = default;
};

class GameAni : public GameImg
{
public:
	GameAni() = default;
	virtual ~GameAni() = default;

	GameAni(const std::string& id) : GameImg(id) {}
	GameAni(const std::string& id, int num) : GameImg(id, num) {}

	DEFINE_TYPE_NAME(GameAni);

	virtual void on_init() override;
	virtual void on_enter() override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;
	/*重置动画状态*/
	void reset();
	/*设置循环*/
	void set_loop(bool loop);
	/*设置帧间隔*/
	void set_interval(float val);
	/*设置资源起始序号*/
	void set_res_int_val(int val);
	/*获取当前帧索引*/
	int get_idx_frame();
	/*获取帧数量*/
	int get_res_num();
	/*设置动画资源*/
	void set_res_name(const Ani_Res& res);
	/*设置当前帧纹理*/
	void set_texture();
	/*获取当前帧纹理*/
	//SDL_Texture* get_texture();
	/*动画是否播放完毕*/
	bool check_finished();
	/*设置回调函数*/
	void set_on_finished(std::function<void()> func);

private:
	/*定时器*/
	Timer timer;
	// 帧索引
	int idx_frame = 0;
	// 是否循环
	bool is_loop = true;
	// 资源起始序号
	int res_int_val = 0;
	// 动画播放完的回调函数
	std::function<void()> on_finished = nullptr;
	// 资源数量
	int res_num = 0;
};