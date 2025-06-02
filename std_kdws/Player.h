#pragma once
#include "Character.h"

/*�����*/
class Player:public Character
{
public:
	/*��ǹ�������*/
	enum class AttackDir
	{
		Up,Down,Left,Right
	};
private:
	/*����״̬*/
	//������ȴʱ��
	Timer timer_roll_cd;
	//��ǵ�ǰ�Ƿ�Ϊ����״̬
	bool is_rolling = false;
	//��Ƿ�����ȴʱ���Ƿ����
	bool is_roll_cd_comp = true;

	/*����״̬*/
	//������ȴʱ��
	Timer timer_attack_cd;
	//��ǵ�ǰ�Ƿ�Ϊ����״̬
	bool is_attacking = false;
	//��ǹ�����ȴʱ���Ƿ����
	bool is_attack_cd_comp = true;

	//��ǵ�ǰ�������Һ͹�����ť����״̬��������Ծ�����Ƿ�����
	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_roll_key_down = false;
	bool is_attack_key_down = false;
	//ն���������������ң�
	Animation animation_slash_up;
	Animation animation_slash_down;
	Animation animation_slash_left;
	Animation animation_slash_right;
	//��ǵ�ǰ��������Ĭ���ң�
	AttackDir attack_dir = AttackDir::Right;
	//��ǰն������
	Animation* current_slash_ani = nullptr;
	// �������״̬
	bool is_jump_vfx_visible = false;
	Animation animation_jump_vfx;//��������
	//������״̬
	bool is_land_vfx_visible = false;
	Animation animation_land_vfx;//��ض���
private:
	const float CD_ROLL = 0.75f;//������ȴʱ��
	const float CD_ATTACK = 0.5f;//������ȴʱ��
	const float SPEED_RUN = 300.0f;//�����ٶ�
	const float SPEED_JUMP = 780.0f;//�����ٶ�
	const float SPEED_ROLL = 800.0f;//�����ٶȡ�

public:
	Player();
    ~Player();

	void on_input(const ExMessage& msg) override;//����д�ĺ�����override������ȷ���ڱ���ʱ�����д������һ���ԡ�������Ϊ����ǩ����ͬ���������д�߼�
	void on_update(float delta) override;
	void on_draw() override;
	/// <summary>
	/// �ܻ�
	/// </summary>
	void on_hurt() override;
	/// <summary>
	/// ���÷���״̬
	/// </summary>
	/// <param name="flag"></param>
	void set_rolling(bool flag)
	{
		is_rolling = flag;
	}
	/// <summary>
	/// ��ȡ����״̬
	/// </summary>
	/// <returns></returns>
	bool get_rolling() const
	{
		return is_rolling;
	}
	/// <summary>
	/// ��ǰ�Ƿ���Է���
	/// </summary>
	/// <returns></returns>
	bool can_roll() const
	{
		return is_roll_cd_comp && !is_rolling && is_roll_key_down;
	}
	/// <summary>
	/// ���ù���״̬
	/// </summary>
	/// <param name="flag"></param>
	void set_attacking(bool flag)
	{
		is_attacking = flag;
	}
	/// <summary>
	/// ��ȡ����״̬
	/// </summary>
	/// <returns></returns>
	bool get_attacking() const
	{
		return is_attacking;
	}
	/// <summary>
	/// ��ǰ�Ƿ���Թ���
	/// </summary>
	/// <returns></returns>
	bool can_attack() const
	{
		return is_attack_cd_comp && !is_attacking && is_attack_key_down;
	}
	/// <summary>
	/// ��ǰ�Ƿ������Ծ
	/// </summary>
	/// <returns></returns>
	bool can_jump() const
	{
		return is_on_floor() && is_jump_key_down;
	}
	/// <summary>
	/// ��ȡˮƽ�ƶ�����
	/// </summary>
	/// <returns>-1�� 0���� 1��</returns>
	int get_move_axis() const
	{
		return is_right_key_down - is_left_key_down;
	}
	/// <summary>
	/// ��ȡ��������
	/// </summary>
	/// <returns></returns>
	AttackDir get_attack_dir() const
	{
		return attack_dir;
	}
	/// <summary>
	/// ��Ծ
	/// </summary>
	void on_jump();
	/// <summary>
	/// ���
	/// </summary>
	void on_land();
	/// <summary>
	/// ����
	/// </summary>
	void on_roll();
	/// <summary>
	/// ����
	/// </summary>
	void on_attack();
private:
	/// <summary>
	/// ������������꣬ת��Ϊ��������
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void update_attack_dir(int x, int y);
};

