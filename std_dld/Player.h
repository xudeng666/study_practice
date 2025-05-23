#pragma once
#include "PlayerID.h"
#include "Platform.h"
#include "Bullet.h"
#include "Particle.h"
#include "Animation.h"
#include <graphics.h>

extern bool is_debug;
extern std::vector<Platform> platform_list;
extern std::vector<Bullet*> bullet_list;
extern Atlas atlas_run_effect;


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

		timer_invincible.set_wait_time(750);
		timer_invincible.set_one_shot(true);
		timer_invincible.set_callback([&]() {is_invincible = false;});

		timer_sketch_blink.set_wait_time(75);
		timer_sketch_blink.set_one_shot(false);
		timer_sketch_blink.set_callback([&]() {is_sketch_show = !is_sketch_show;});

		timer_run_eff_par.set_wait_time(75);
		timer_run_eff_par.set_callback([&]() 
			{
				Vector2 par_pos;
				IMAGE* img = atlas_run_effect.getImageByIndex(0);
				par_pos.x = position.x + (size.x - img->getwidth()) / 2;
				par_pos.y = position.y + size.y - img->getheight();
				par_list.emplace_back(par_pos, &atlas_run_effect, 45);
			}
		);

		timer_die_eff_par.set_wait_time(35);
		timer_die_eff_par.set_callback([&]() 
			{
				Vector2 par_pos;
				IMAGE* img = atlas_run_effect.getImageByIndex(0);
				par_pos.x = position.x + (size.x - img->getwidth()) / 2;
				par_pos.y = position.y + size.y - img->getheight();
				par_list.emplace_back(par_pos, &atlas_run_effect, 150);
			}
		);
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
			currentAni = is_face_right ? &ani_run_right : &ani_run_left;
			timer_run_eff_par.pause();	
		}
		currentAni->on_updata(delta);
		timer_attack_cd.on_update(delta);
		timer_invincible.on_update(delta);
		timer_sketch_blink.on_update(delta);
		timer_run_eff_par.on_update(delta);

		if (hp <= 0)
		{
			timer_die_eff_par.on_update(delta);
		}

		par_list.erase(std::remove_if(
			par_list.begin(), par_list.end(), 
			[](const Particle& particle)
			{
				return !particle.check_valid();
			}
		), par_list.end());

		for (Particle& par : par_list)
		{
			par.on_updata(delta);
		}

		if (is_sketch_show)
		{
			set_silh_img(currentAni->get_frame(), &img_sketch);
		}

		move_and_collide(delta);
    }

    virtual void on_draw(const Camera& camera)
    {

		for (const Particle& par : par_list)
		{
			par.on_draw(camera);
		}

		if (hp > 0 && is_invincible && is_sketch_show)
		{
			putimage_alpha(camera, (int)position.x, (int)position.y, &img_sketch);
		}
		else
		{
			currentAni->on_draw(camera, (int)position.x, (int)position.y);
		}
		if (is_debug)
		{
			setlinecolor(RGB(255, 0, 0));
			rectangle(position.x, position.y, position.x + size.x, position.y + size.y);
		}
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
					break;
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
				if (checkRectToHLine<float>(position.x, position.x + size.x, position.y, position.y + size.y,
					plat.shape.left, plat.shape.right, plat.shape.y))
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

		if (!is_invincible)// �޵�״̬���ܵ��ӵ���ײ
		{
			for (Bullet* bullet : bullet_list)
			{
				if (!bullet->get_valid() || bullet->get_collide_target() != id)
				{
					continue;
				}
				if (bullet->check_cllide(position, size))
				{
					make_invincible();
					bullet->on_collide();
					bullet->set_valid(false);
					hp -= bullet->get_damage();
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
		timer_run_eff_par.resume();
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

	const PlayerID getId()
	{
		return id;
	}

	const int get_hp()
	{
		return hp;
	}

	const int get_mp()
	{
		return mp;
	}

	//����Ϊ�޵�״̬
	void make_invincible()
	{
		is_invincible = true;
		timer_invincible.restart();
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
	IMAGE img_sketch;			// ��ӰͼƬ

    PlayerID id = PlayerID::P1; // ������

    bool is_left_kd = false;// �Ƿ���߰�ť����
    bool is_right_kd = false;// �Ƿ��ұ߰�ť����

	bool is_face_right = false; //�Ƿ�������

	int attack_cd = 500;		// �չ���ȴʱ��
	Timer timer_attack_cd;		// �չ���ȴ��ʱ��
	bool can_attack = true;		// �Ƿ�����չ�

	bool is_attack_ex = false;	// �Ƿ����⹥����

	bool is_invincible = false;	// �Ƿ��޵�״̬
	bool is_sketch_show = false;// �Ƿ���ʾ��Ӱ 
	Timer timer_invincible;		// �޵�״̬��ʱ��
	Timer timer_sketch_blink;	// ��Ӱ��˸��ʱ��

	Timer timer_run_eff_par;	// �ܶ����ӷ��䶨ʱ��
	Timer timer_die_eff_par;	// �������ӷ��䶨ʱ��

	std::vector<Particle> par_list;


};

