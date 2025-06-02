#pragma once
#include "Character.h"

/*玩家类*/
class Player:public Character
{
public:
	/*标记攻击方向*/
	enum class AttackDir
	{
		Up,Down,Left,Right
	};
private:
	/*翻滚状态*/
	//翻滚冷却时间
	Timer timer_roll_cd;
	//标记当前是否为翻滚状态
	bool is_rolling = false;
	//标记翻滚冷却时间是否结束
	bool is_roll_cd_comp = true;

	/*攻击状态*/
	//攻击冷却时间
	Timer timer_attack_cd;
	//标记当前是否为攻击状态
	bool is_attacking = false;
	//标记攻击冷却时间是否结束
	bool is_attack_cd_comp = true;

	//标记当前上下左右和攻击按钮按下状态（上是跳跃，下是翻滚）
	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_roll_key_down = false;
	bool is_attack_key_down = false;
	//斩击动画（上下左右）
	Animation animation_slash_up;
	Animation animation_slash_down;
	Animation animation_slash_left;
	Animation animation_slash_right;
	//标记当前攻击方向（默认右）
	AttackDir attack_dir = AttackDir::Right;
	//当前斩击动画
	Animation* current_slash_ani = nullptr;
	// 标记起跳状态
	bool is_jump_vfx_visible = false;
	Animation animation_jump_vfx;//起跳动画
	//标记落地状态
	bool is_land_vfx_visible = false;
	Animation animation_land_vfx;//落地动画
private:
	const float CD_ROLL = 0.75f;//翻滚冷却时间
	const float CD_ATTACK = 0.5f;//攻击冷却时间
	const float SPEED_RUN = 300.0f;//奔跑速度
	const float SPEED_JUMP = 780.0f;//起跳速度
	const float SPEED_ROLL = 800.0f;//翻滚速度、

public:
	Player();
    ~Player();

	void on_input(const ExMessage& msg) override;//对重写的函数用override声明，确保在编译时检查重写方法的一致性。避免因为函数签名不同错过调用重写逻辑
	void on_update(float delta) override;
	void on_draw() override;
	/// <summary>
	/// 受击
	/// </summary>
	void on_hurt() override;
	/// <summary>
	/// 设置翻滚状态
	/// </summary>
	/// <param name="flag"></param>
	void set_rolling(bool flag)
	{
		is_rolling = flag;
	}
	/// <summary>
	/// 获取翻滚状态
	/// </summary>
	/// <returns></returns>
	bool get_rolling() const
	{
		return is_rolling;
	}
	/// <summary>
	/// 当前是否可以翻滚
	/// </summary>
	/// <returns></returns>
	bool can_roll() const
	{
		return is_roll_cd_comp && !is_rolling && is_roll_key_down;
	}
	/// <summary>
	/// 设置攻击状态
	/// </summary>
	/// <param name="flag"></param>
	void set_attacking(bool flag)
	{
		is_attacking = flag;
	}
	/// <summary>
	/// 获取攻击状态
	/// </summary>
	/// <returns></returns>
	bool get_attacking() const
	{
		return is_attacking;
	}
	/// <summary>
	/// 当前是否可以攻击
	/// </summary>
	/// <returns></returns>
	bool can_attack() const
	{
		return is_attack_cd_comp && !is_attacking && is_attack_key_down;
	}
	/// <summary>
	/// 当前是否可以跳跃
	/// </summary>
	/// <returns></returns>
	bool can_jump() const
	{
		return is_on_floor() && is_jump_key_down;
	}
	/// <summary>
	/// 获取水平移动方向
	/// </summary>
	/// <returns>-1右 0不动 1左</returns>
	int get_move_axis() const
	{
		return is_right_key_down - is_left_key_down;
	}
	/// <summary>
	/// 获取攻击方向
	/// </summary>
	/// <returns></returns>
	AttackDir get_attack_dir() const
	{
		return attack_dir;
	}
	/// <summary>
	/// 跳跃
	/// </summary>
	void on_jump();
	/// <summary>
	/// 落地
	/// </summary>
	void on_land();
	/// <summary>
	/// 翻滚
	/// </summary>
	void on_roll();
	/// <summary>
	/// 攻击
	/// </summary>
	void on_attack();
private:
	/// <summary>
	/// 传入鼠标点击坐标，转换为攻击方向
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void update_attack_dir(int x, int y);
};

