#pragma once
#include "PlayerID.h"
#include "Platform.h"
#include "Bullet.h"
#include "Animation.h"
#include <graphics.h>


extern std::vector<Platform> platform_list;
extern std::vector<Bullet*> bullet_list;


/*��һ���*/
class Player
{
public:
	Player()
	{
		currentAni = &ani_idle_right;
		position.x = position.y = 0;

		timer_attack_cd.set_wait_time(attack_cd);
		timer_attack_cd.set_one_shot(true);
		timer_attack_cd.set_callback([&]() {can_attack = true;});
	}
    ~Player() = default;

    virtual void on_update(int delta)
    {
		int dirc = is_right_kd - is_left_kd;
		if (0 != dirc)
		{
			is_face_right = dirc > 0;
			currentAni = is_face_right ? &ani_run_right : &ani_run_left;
			float distance = dirc * run_velocity * delta;
			on_run(distance);
		}
		else
		{
			currentAni = is_face_right ? &ani_idle_right : &ani_idle_left;
		}
		currentAni->on_updata(delta);
		timer_attack_cd.on_update(delta);

		move_and_collide(delta);
    }

    virtual void on_draw(const Camera& camera)
    {
		currentAni->on_draw(camera, (int)position.x, (int)position.y);
    }

    virtual void on_input(const ExMessage& msg)
    {
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (id)
			{
			case PlayerID::P1:
				switch (msg.vkcode)
				{
				case 'A':
					is_left_kd = true;
					break;
				case 'D':
					is_right_kd = true;
				case 'W':
					on_jump();
					break;
				case 'F':
					if (can_attack)
					{
						on_attack();
						can_attack = false;
						timer_attack_cd.restart();
					}
					break;
				case 'G':
					if (mp >= 100)
					{
						on_attack_ex();
						mp = 0;
					}
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode)
				{
				case VK_LEFT:
					is_left_kd = true;
					break;
				case VK_RIGHT:
					is_right_kd = true;
					break;
				case VK_UP:
					on_jump();
					break;
				case VK_OEM_PERIOD:
					if (can_attack)
					{
						on_attack();
						can_attack = false;
						timer_attack_cd.restart();
					}
					break;
				case VK_OEM_2:
					if (mp >= 100)
					{
						on_attack_ex();
						mp = 0;
					}
					break;
				}
				break;
			}
			break;
		case WM_KEYUP:
			switch (id)
			{
			case PlayerID::P1:
				switch (msg.vkcode)
				{
				case 'A':
					is_left_kd = false;
					break;
				case 'D':
					is_right_kd = false;
					break;
				}
				break;
			case PlayerID::P2:
				switch (msg.vkcode)
				{
				case VK_LEFT:
					is_left_kd = false;
					break;
				case VK_RIGHT:
					is_right_kd = false;
					break;
				}
				break;
			}
			break;
		}
    }

	/*�ƶ���ײ��*/
	virtual void move_and_collide(int delta)
	{
		velocity.y += gravity * delta;
		position.y += velocity.y * (float)delta;

		if (velocity.y > 0)
		{
			for (const Platform& plat : platform_list)
			{
				if (checkRectToRect<float>(position.x, position.x + size.x, position.y, position.y + size.y,
					plat.shape.left, plat.shape.right, plat.shape.y, plat.shape.y))
				{
					float posy = velocity.y * (float)delta;
					float last_posy = position.y + size.y - posy;
					if (last_posy <= plat.shape.y) // ��һ֡��ƽ̨����
					{
						position.y = plat.shape.y - size.y;
						velocity.y = 0;
						break;
					}
				}
			}
		}
	}

	/*�ƶ�*/
	virtual void on_run(float distance)
	{
		if (is_attack_ex)
		{
			return;
		}
		position.x += distance;
	}

	/*��Ծ*/
	virtual void on_jump()
	{
		if (is_attack_ex || velocity.y != 0)
		{
			return;
		}
		velocity.y += jump_velocity;
	}

	/*��ͨ����*/
	virtual void on_attack()
	{
	}

	/*���⹥��*/
	virtual void on_attack_ex()
	{
	}

    void setId(PlayerID id)
    {
        this->id = id;
    }

	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void setFaceRight(bool isRight)
	{
		is_face_right = isRight;
	}

	const Vector2& getPosition()const
	{
		return position;
	}

	const Vector2& getSize()const
	{
		return size;
	}

protected:
	const float run_velocity = 0.55f;	// �ܶ��ٶ�
	const float jump_velocity = -0.85f;	// ��Ծ�ٶ�
	const float gravity = 1.6e-3f;		// �������ٶ�

protected:
	// ����
	int mp = 0;
	// ����
	int hp = 100;
	// �ߴ�
	Vector2 size;
	// λ��
	Vector2 position;
	// �ٶ�
	Vector2 velocity;

    Animation ani_idle_left;    // վ����Ĭ�ϣ��������
    Animation ani_idle_right;
    Animation ani_run_left;      // �ƶ��������
    Animation ani_run_right;
    Animation ani_attack_ex_left;      // ���ж������
    Animation ani_attack_ex_right;

	Animation* currentAni = nullptr;	// ��ǰ����

    PlayerID id = PlayerID::P1; // ������

    bool is_left_kd = false;
    bool is_right_kd = false;

	bool is_face_right = false;

	int attack_cd = 500;		// �չ���ȴʱ��
	Timer timer_attack_cd;		// �չ���ȴ��ʱ��
	bool can_attack = true;		// �Ƿ�����չ�

	bool is_attack_ex = false;	// �Ƿ����⹥����
};

