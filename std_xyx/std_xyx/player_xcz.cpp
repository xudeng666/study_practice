#include "player_xcz.h"


Player_xcz::Player_xcz()
{
	ani_pool["left"] = Ani_Res("paimon_left_", 6);
	ani_pool["right"] = Ani_Res("paimon_right_", 6);

	set_step_length(48);
	set_speed(150);

	click_enabled = false;
	size = { 40,60 };
	anchor_mode = AnchorMode::BOTTOMCENTER;
	anchor_referent_mode = AnchorMode::CENTER;

	current_ani->set_position({ 0,0 });
	current_ani->set_anchor_mode(AnchorMode::BOTTOMCENTER);
	current_ani->set_anchor_referent_mode(AnchorMode::BOTTOMCENTER);
	current_ani->set_anchor_referent_obj(this);
	current_ani->set_ID("ani");
	current_ani->set_res_int_val(0);
	current_ani->set_res_name(ani_pool["left"]);
	current_ani->set_loop(true);
	set_interval();

	img_shade->set_position({ 0,0 });
	img_shade->set_anchor_mode(AnchorMode::CENTER);
	img_shade->set_anchor_referent_mode(AnchorMode::BOTTOMCENTER);
	img_shade->set_anchor_referent_obj(current_ani);
	img_shade->set_res_name("shadow_player");
	img_shade->set_ID("shade");

	hit_box->set_position({ 0,0 });
	hit_box->set_size({ 10,10 });
	hit_box->set_anchor_mode(AnchorMode::CENTER);
	hit_box->set_anchor_referent_mode(AnchorMode::CENTER);
	hit_box->set_layer_dst(CollisionLayer::ENEMY);
	hit_box->set_layer_src(CollisionLayer::NONE);
	hit_box->set_ID("player_hit_box");
	//hit_box->set_call_back([&]() {on_hit();});
	hit_box->set_anchor_referent_obj(this);

	hurt_box->set_position({ 0,0 });
	hurt_box->set_size({ 10,10 });
	hurt_box->set_anchor_mode(AnchorMode::CENTER);
	hurt_box->set_anchor_referent_mode(AnchorMode::CENTER);
	hurt_box->set_layer_dst(CollisionLayer::NONE);
	hurt_box->set_layer_src(CollisionLayer::PLAYER_1);
	hurt_box->set_ID("player_hurt_box");
	hurt_box->set_call_back([&]() {decrease_hp(1);});
	hurt_box->set_anchor_referent_obj(this);
}

Player_xcz::~Player_xcz()
{
	bullet_list.clear();
	Character::~Character();
}

void Player_xcz::on_enter()
{
	if (_DE_BUG_)
	{
		std::cout << ID <<"  on_enter" << std::endl;
	}
	CharacterXcz::on_enter();

	hit_box->set_collision_enabled(true);
	hurt_box->set_collision_enabled(true);
}

void Player_xcz::on_exit()
{
	CharacterXcz::on_exit();
	hit_box->set_collision_enabled(false);
	hurt_box->set_collision_enabled(false);
	reduce_bullet(bul_num);
}

void Player_xcz::on_input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP:
			set_move_status(0, true);
			break;
		case SDLK_s:
		case SDLK_DOWN:
			set_move_status(1, true);
			break;
		case SDLK_a:
		case SDLK_LEFT:
			set_move_status(2, true);
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			set_move_status(3, true);
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP:
			set_move_status(0, false);
			break;
		case SDLK_s:
		case SDLK_DOWN:
			set_move_status(1, false);
			break;
		case SDLK_a:
		case SDLK_LEFT:
			set_move_status(2, false);
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			set_move_status(3, false);
			break;
		}
		break;
	}
}
void Player_xcz::on_update(float delta)
{
	if (_DE_BUG_)
	{
		//std::cout << ID << "  on_update" << std::endl;
	}
	if (alive)
	{
		on_move(delta);
		move_bullet(delta);
	}
}

void Player_xcz::set_face(bool is_left)
{
	set_animation(is_left ? ani_pool["left"] : ani_pool["right"]);
}

void Player_xcz::on_render()
{
}

void Player_xcz::on_move(float delta)
{
	float x1 = move_status[2] ? -1 : 0;
	float x2 = move_status[3] ? 1 : 0;
	float y1 = move_status[0] ? -1 : 0;
	float y2 = move_status[1] ? 1 : 0;
	Vector2 t = { x1 + x2, y1 + y2 };
	t = t.normalize();
	velocity = t * speed * delta;
	lock_in_screen();
	if (velocity.x != 0)
	{
		set_face(velocity.x < 0);
	}
	position += velocity;
}

void Player_xcz::add_bullet(const int num)
{
	for (size_t i = 0; i < num; i++)
	{
		bul_num++;
		if (bul_num > bullet_list.size())
		{
			auto bul_ptr = std::make_unique<BulletXcz>();
			BulletXcz* p = bul_ptr.get();
			p->set_ID("bul_", bul_num - 1);
			p->set_anchor_referent_obj(current_ani);
			p->on_enter();
			p->set_on_hit_fun([&]() {
				on_hit();
				});
			add_children(std::move(bul_ptr));
			bullet_list.push_back(p);
		}
		else
		{
			bullet_list[bul_num - 1]->on_enter();
		}
	}
}
void Player_xcz::reduce_bullet(const int num)
{
	for (size_t i = 0; i < num; i++)
	{
		bul_num--;
		if (bul_num < 0) return;
		if (bullet_list[bul_num])
		{
			bullet_list[bul_num]->on_exit();
		}
	}
}

int Player_xcz::get_bullet_num()
{
	return bul_num;
}

void Player_xcz::set_bullet_num(const int num)
{
	bul_num = num;
}

void Player_xcz::move_bullet(float delta)
{
	if (bullet_list.size() < bul_num) return;
	bul_degrees += delta * angle_speed;
	for (int i = 0; i < bul_num; ++i)
	{
		int dre = bul_degrees + 360 / bul_num * i;
		dre %= 360;
		//std::cout << "bullet dre:   " << dre << std::endl;
		bullet_list[i]->set_position({ (float)cos(dre * _PI_ / 180) * bul_radius, -(float)(sin(dre * _PI_ / 180) * bul_radius) });
		bullet_list[i]->set_rotation(90 - dre);
	}
}