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
extern Atlas atlas_run_effect;						// 奔跑特效动画图集
extern Atlas atlas_jump_effect;						// 跳跃特效动画图集
extern Atlas atlas_land_effect;						// 落地特效动画图集
extern IMAGE img_1P_cursor;							// 1P 指示光标图片
extern IMAGE img_2P_cursor;							// 2P 指示光标图片


/*玩家基类*/
class Player
{
public:
	Player(bool right = true):is_face_right(right)
	{
		currentAni = &ani_idle_right;
		position.x = position.y = 0;
		is_cursor_show = true;

		ani_jump_eff.set_atlas(&atlas_jump_effect);
		ani_jump_eff.set_interval(25);
		ani_jump_eff.set_loop(false);
		ani_jump_eff.set_callback([&]() {is_jump_eff_show = false;});

		ani_land_eff.set_atlas(&atlas_land_effect);
		ani_land_eff.set_interval(50);
		ani_land_eff.set_loop(false);
		ani_land_eff.set_callback([&]() {is_land_eff_show = false;});

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

		timer_cursor_show.set_wait_time(2500);
		timer_cursor_show.set_one_shot(true);
		timer_cursor_show.set_callback([&]() {is_cursor_show = false;});
	}
    ~Player() = default;

    virtual void on_update(int delta)
    {
		int dirc = is_right_kd - is_left_kd;//朝向
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

		if (is_attack_ex)
		{
			currentAni = is_face_right ? &ani_attack_ex_right : &ani_attack_ex_left;
		}

		if (hp <= 0)
		{
			currentAni = is_face_right ? &ani_die_left : &ani_die_right;
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

		if (is_jump_eff_show)
		{
			ani_jump_eff.on_updata(delta);
		}

		if (is_land_eff_show)
		{
			ani_land_eff.on_updata(delta);
		}

		if (is_cursor_show)
		{
			timer_cursor_show.on_update(delta);
		}

		move_and_collide(delta);
    }

    virtual void on_draw(const Camera& camera)
    {

		for (const Particle& par : par_list)
		{
			par.on_draw(camera);
		}

		if (is_jump_eff_show)
		{
			ani_jump_eff.on_draw(camera, pos_jump_eff.x, pos_jump_eff.y);
		}

		if (is_land_eff_show)
		{
			ani_land_eff.on_draw(camera, pos_land_eff.x, pos_land_eff.y);
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

		if (is_cursor_show)
		{
			IMAGE* img = id == PlayerID::P1 ? &img_1P_cursor : &img_2P_cursor;
			putimage_alpha(camera, position.x + (size.x - img->getwidth()) / 2, position.y - img->getheight(), img);
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

	/*移动和撞击*/
	virtual void move_and_collide(int delta)
	{
		float last_v_y = velocity.y;
		velocity.y += gravity * delta;
		position.y += velocity.y * (float)delta;
		position.x += velocity.x * (float)delta;

		if (hp <= 0)
			return;

		if ( velocity.y > 0)
		{
			for (const Platform& plat : platform_list)
			{
				if (checkRectToHLine<float>(position.x, position.x + size.x, position.y, position.y + size.y,
					plat.shape.left, plat.shape.right, plat.shape.y))
				{
					float posy = velocity.y * (float)delta;
					float last_posy = position.y + size.y - posy;
					if (last_posy <= plat.shape.y) // 上一帧在平台上面
					{
						position.y = plat.shape.y - size.y;
						velocity.y = 0;
						if (last_v_y != 0)
						{
							on_land();
						}
						break;
					}
				}
			}
		}

		if (!is_invincible)// 无敌状态不受到子弹碰撞
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
					last_hunt_dir = bullet->get_center_position() - get_center_position();
					if ( hp <= 0)
					{
						velocity.x = last_hunt_dir.x < 0 ? 0.35f : -0.35f;
						velocity.y = -1.0f;
					}
				}
			}
		}
	}

	/*移动*/
	virtual void on_run(float distance)
	{
		if (is_attack_ex)
		{
			return;
		}
		position.x += distance;
		timer_run_eff_par.resume();
	}

	/*跳跃*/
	virtual void on_jump()
	{
		if (is_attack_ex || velocity.y != 0)
		{
			return;
		}
		velocity.y += jump_velocity;

		is_jump_eff_show = true;
		ani_jump_eff.reset();
		pos_jump_eff.x = position.x + (size.x - ani_jump_eff.get_frame()->getwidth()) / 2;
		pos_jump_eff.y = position.y + size.y - ani_jump_eff.get_frame()->getheight();
	}

	/*落地*/
	virtual void on_land()
	{
		is_land_eff_show = true;
		ani_land_eff.reset();
		pos_land_eff.x = position.x + (size.x - ani_land_eff.get_frame()->getwidth()) / 2;
		pos_land_eff.y = position.y + size.y - ani_land_eff.get_frame()->getheight();
	}

	/*普通攻击*/
	virtual void on_attack()
	{
	}

	/*特殊攻击*/
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

	/*获取中心位置*/
	Vector2 get_center_position()
	{
		return { position.x + size.x / 2,position.x + size.y / 2 };
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

	int get_hp() const
	{
		return hp;
	}

	int get_mp() const
	{
		return mp;
	}

	void set_hp(int val)
	{
		hp = val;
	}

	void set_mp(int val)
	{
		mp = val;
	}

	//设置为无敌状态
	void make_invincible()
	{
		is_invincible = true;
		timer_invincible.restart();
	}

protected:
	const float run_velocity = 0.55f;	// 跑动速度
	const float jump_velocity = -0.85f;	// 跳跃速度
	const float gravity = 1.6e-3f;		// 重力加速度

protected:
	// 蓝条
	int mp = 0;
	// 红条
	int hp = 100;
	// 尺寸
	Vector2 size;
	// 位置
	Vector2 position;
	// 速度
	Vector2 velocity;

    Animation ani_idle_left;    // 站立（默认）动画左边
    Animation ani_idle_right;
    Animation ani_run_left;      // 移动动画左边
    Animation ani_run_right;
    Animation ani_die_left;      // 死亡动画左边
    Animation ani_die_right;
    Animation ani_attack_ex_left;      // 大招动画左边
    Animation ani_attack_ex_right;
	Animation ani_jump_eff;
	Animation ani_land_eff;

	Animation* currentAni = nullptr;	// 当前动画
	IMAGE img_sketch;			// 剪影图片

    PlayerID id = PlayerID::P1; // 玩家序号


	bool is_jump_eff_show = false;// 跳跃动画是否显示
	bool is_land_eff_show = false;// 落地动画是否显示

	Vector2 pos_jump_eff;
	Vector2 pos_land_eff;

    bool is_left_kd = false;// 是否左边按钮按下
    bool is_right_kd = false;// 是否右边按钮按下

	bool is_face_right = false; //是否面向右

	int attack_cd = 500;		// 普攻冷却时间
	Timer timer_attack_cd;		// 普攻冷却计时器
	bool can_attack = true;		// 是否可以普攻

	bool is_attack_ex = false;	// 是否特殊攻击中

	bool is_invincible = false;	// 是否无敌状态
	bool is_sketch_show = false;// 是否显示剪影 
	Timer timer_invincible;		// 无敌状态计时器
	Timer timer_sketch_blink;	// 剪影闪烁计时器

	Timer timer_run_eff_par;	// 跑动粒子发射定时器
	Timer timer_die_eff_par;	// 死亡粒子发射定时器

	std::vector<Particle> par_list;

	bool is_cursor_show = false;
	Timer timer_cursor_show;

	Vector2 last_hunt_dir;// 最后受击方向


};

