#include "player_xcz.h"


Player_xcz::~Player_xcz()
{
	bullet_list.clear();
}

void Player_xcz::on_init()
{
	ani_pool["left"] = Ani_Res("paimon_left_", 6);
	ani_pool["right"] = Ani_Res("paimon_right_", 6);

	set_step_length(48);
	set_speed(150);

	click_enabled = false;
	size = { 40,60 };
	anchor_mode = AnchorMode::BOTTOMCENTER;
	anchor_referent_mode = AnchorMode::CENTER;

	auto ani = current_ani.lock()->get_obj_as<GameAni>();
	ani->set_position({ 0,0 });
	ani->set_anchor_mode(AnchorMode::BOTTOMCENTER);
	ani->set_anchor_referent_mode(AnchorMode::BOTTOMCENTER);
	ani->set_anchor_referent_node(self_node);
	ani->set_ID("ani");
	ani->set_res_int_val(0);
	ani->set_res_name(ani_pool["left"]);
	ani->set_loop(true);
	set_interval();

	auto shade = img_shade.lock()->get_obj_as<GameImg>();
	shade->set_position({ 0,0 });
	shade->set_anchor_mode(AnchorMode::CENTER);
	shade->set_anchor_referent_mode(AnchorMode::BOTTOMCENTER);
	shade->set_anchor_referent_node(current_ani);
	shade->set_res_name("shadow_player");
	shade->set_ID("shade");

	auto hit_obj = hit_box.lock()->get_obj_as<GameCollisionBox>();
	hit_obj->set_position({ 0,0 });
	hit_obj->set_size({ 10,10 });
	hit_obj->set_anchor_mode(AnchorMode::CENTER);
	hit_obj->set_anchor_referent_mode(AnchorMode::CENTER);
	hit_obj->set_layer_dst(CollisionLayer::ENEMY);
	hit_obj->set_layer_src(CollisionLayer::NONE);
	hit_obj->set_ID("player_hit_box");
	hit_obj->set_anchor_referent_node(self_node);

	auto hurt_obj = hurt_box.lock()->get_obj_as<GameCollisionBox>();
	hurt_obj->set_position({ 0,0 });
	hurt_obj->set_size({ 10,10 });
	hurt_obj->set_anchor_mode(AnchorMode::CENTER);
	hurt_obj->set_anchor_referent_mode(AnchorMode::CENTER);
	hurt_obj->set_layer_dst(CollisionLayer::NONE);
	hurt_obj->set_layer_src(CollisionLayer::PLAYER_1);
	hurt_obj->set_ID("player_hurt_box");
	hurt_obj->set_call_back([&]() {decrease_hp(1);});
	hurt_obj->set_anchor_referent_node(self_node);
}

void Player_xcz::on_enter()
{
	if (_DE_BUG_)
	{
		std::cout << ID <<"  on_enter" << std::endl;
	}
	CharacterXcz::on_enter();

	auto hit_obj = hit_box.lock()->get_obj_as<GameCollisionBox>();
	auto hurt_obj = hurt_box.lock()->get_obj_as<GameCollisionBox>();
	hit_obj->set_collision_enabled(true);
	hurt_obj->set_collision_enabled(true);
}

void Player_xcz::on_exit()
{
	CharacterXcz::on_exit();
	auto hit_obj = hit_box.lock()->get_obj_as<GameCollisionBox>();
	auto hurt_obj = hurt_box.lock()->get_obj_as<GameCollisionBox>();
	hit_obj->set_collision_enabled(false);
	hurt_obj->set_collision_enabled(false);
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
			auto p = TreeNode::create_obj<BulletXcz>("bul_", bul_num - 1);
			p->set_anchor_referent_node(current_ani);
			p->on_enter();
			p->set_on_hit_fun([&]() {
				on_hit();
				});
			add_children(std::move(p));
			bullet_list.push_back(p);
		}
		else
		{
			auto p = bullet_list[bul_num - 1].lock();
			p->on_enter();
		}
	}
}
void Player_xcz::reduce_bullet(const int num)
{
	for (size_t i = 0; i < num; i++)
	{
		bul_num--;
		if (bul_num < 0) return;
		auto p = bullet_list[bul_num].lock();
		if (p)
		{
			p->on_exit();
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
		auto p = bullet_list[i].lock();
		if (p)
		{
			p->set_position({(float)cos(dre * _PI_ / 180) * bul_radius, -(float)(sin(dre * _PI_ / 180) * bul_radius)});
			p->set_rotation(90 - dre);
		}
	}
}