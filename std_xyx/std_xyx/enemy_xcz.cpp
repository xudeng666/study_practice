#include "enemy_xcz.h"
#include "game_wnd.h"
#include "event_mgr.h"

INIT_TYPE_NAME(Enemy_xcz);

void Enemy_xcz::on_init()
{
	CharacterXcz::on_init();
	ani_pool["left"] = Ani_Res("boar_left_", 6);
	ani_pool["right"] = Ani_Res("boar_right_", 6);

	click_enabled = false;
	set_step_length(48);
	set_speed(120);
	size = { 96,96 };
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
	shade->set_position({ 0,-20 });
	shade->set_anchor_mode(AnchorMode::CENTER);
	shade->set_anchor_referent_mode(AnchorMode::BOTTOMCENTER);
	shade->set_anchor_referent_node(current_ani);
	shade->set_res_name("shadow_enemy");
	shade->set_ID("shade");

	auto hit_obj = hit_box.lock()->get_obj_as<GameCollisionBox>();
	hit_obj->set_position({ 0,0 });
	hit_obj->set_size({ 80,80 });
	hit_obj->set_anchor_mode(AnchorMode::CENTER);
	hit_obj->set_anchor_referent_mode(AnchorMode::CENTER);
	hit_obj->set_layer_dst(CollisionLayer::PLAYER_1);
	hit_obj->set_layer_src(CollisionLayer::NONE);
	hit_obj->set_ID("enemy_hit_box");
	hit_obj->set_call_back([&]() {on_hit();});
	hit_obj->set_anchor_referent_node(self_node);

	auto hurt_obj = hurt_box.lock()->get_obj_as<GameCollisionBox>();
	hurt_obj->set_position({ 0,0 });
	hurt_obj->set_size({ 80,80 });
	hurt_obj->set_anchor_mode(AnchorMode::CENTER);
	hurt_obj->set_anchor_referent_mode(AnchorMode::CENTER);
	hurt_obj->set_layer_dst(CollisionLayer::NONE);
	hurt_obj->set_layer_src(CollisionLayer::ENEMY);
	hurt_obj->set_ID("enemy_hurt_box");
	hurt_obj->set_call_back([&]() {
		decrease_hp(1);
		if (!get_alive())
		{
			on_exit();
		}
		});
	hurt_obj->set_anchor_referent_node(self_node);
}

void Enemy_xcz::on_enter()
{
	if (_DE_BUG_)
	{
		//std::cout << ID << "  Enemy_xcz on_enter" << std::endl;
	}
	CharacterXcz::on_enter();

	int w = GameWnd::instance()->get_width();
	int h = GameWnd::instance()->get_height();
	// 初始坐标在屏幕外随机
	switch (getIntRand(0, 3))
	{
	case 0:
		position = { -w / 2.0f - 50,getRealRand(-50,h + 50) };
		break;
	case 1:
		position = { w / 2.0f + 50,getRealRand(-50,h + 50) };
		break;
	case 2:
		position = { getRealRand(-50,w + 50),-h / 2.0f - 50 };
		break;
	case 3:
		position = { getRealRand(-50,w + 50),h / 2.0f + 50 };
		break;
	}

	hp = 1;

	set_display(true);

	auto hit_obj  = hit_box.lock()->get_obj_as<GameCollisionBox>();
	auto hurt_obj = hurt_box.lock()->get_obj_as<GameCollisionBox>();
	hit_obj ->set_collision_enabled(true);
	hurt_obj->set_collision_enabled(true);
}

void Enemy_xcz::on_exit()
{
	auto hit_obj = hit_box.lock()->get_obj_as<GameCollisionBox>();
	auto hurt_obj = hurt_box.lock()->get_obj_as<GameCollisionBox>();
	hit_obj ->set_collision_enabled(false);
	hurt_obj->set_collision_enabled(false);
	set_display(false);
	CharacterXcz::on_exit();
}


void Enemy_xcz::on_input(const SDL_Event& event)
{
	if (event.type == EventMgr::instance()->get_event_type(EventType::PLAYER_MOVE))
	{
		EventData* data = static_cast<EventData*>(event.user.data1);
		if (!data) return;
		Vector2 pos;
		if (data->get("postion", pos))
		{
			set_player_pos(pos);
		}
	}
}
void Enemy_xcz::on_update(float delta)
{
	if (_DE_BUG_)
	{
		//std::cout << ID << "  on_update" << std::endl;
	}
	CharacterXcz::on_update(delta);
	if (alive)
	{
		on_move(delta);
	}
}

void Enemy_xcz::set_face(bool is_left)
{
	set_animation(is_left ? ani_pool["left"] : ani_pool["right"]);
}

void Enemy_xcz::on_render()
{
	CharacterXcz::on_render();
}

void Enemy_xcz::set_player_pos(Vector2 pos)
{
	pos_player = pos;
}

void Enemy_xcz::on_move(float delta)
{
	Vector2 vel = pos_player - get_rect_position();//get_anchor_position(AnchorMode::CENTER);
	Vector2 t = vel.normalize_portion();

	if (vel.x < 5 && vel.x > -5)
	{
		vel.x = 0;
	}
	if (vel.y < 5 && vel.y > -5)
	{
		vel.y = 0;
	}

	if (vel.x != 0.0f && vel.y != 0.0f)
	{
		switch (getIntRand(0,3))
		{
		case 0:t.x = 0.0f;break;
		case 1:t.y = 0.0f;break;
		case 2:t = vel;break; 
		case 3:break;
		}
	}
	velocity = t.normalize() * speed * delta;

	if (std::fabs(velocity.x) > std::fabs(vel.x))
	{
		velocity.x = vel.x;
	}
	if (std::fabs(velocity.y) > std::fabs(vel.y))
	{
		velocity.y = vel.y;
	}
	if (velocity.x != 0.0f)
	{
		set_face(velocity.x < 0.0f);
	}
	position += velocity;
}
