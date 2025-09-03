#include "enemy_xcz.h"


Enemy_xcz::Enemy_xcz()
{
	ani_pool["left"] = Ani_Res("boar_left_", 6);
	ani_pool["right"] = Ani_Res("boar_right_", 6);
}

Enemy_xcz::~Enemy_xcz()
{
	Character::~Character();
}

void Enemy_xcz::on_enter()
{
	if (_DE_BUG_)
	{
		std::cout << ID << "  on_enter" << std::endl;
	}

	set_step_length(48);
	set_speed(120);

	click_enabled = false;
	// 需要在enter添加初始坐标在屏幕外随机
	position = { 0,0 };
	size = { 96,96 };
	hp = 1;
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
	img_shade->set_res_name("shadow_enemy");
	img_shade->set_ID("shade");
}

void Enemy_xcz::on_input(const SDL_Event& event)
{
}
void Enemy_xcz::on_update(float delta)
{
	if (_DE_BUG_)
	{
		//std::cout << ID << "  on_update" << std::endl;
	}
	on_move(delta);
}

void Enemy_xcz::set_face(bool is_left)
{
	set_animation(is_left ? ani_pool["left"] : ani_pool["right"]);
}

void Enemy_xcz::on_render()
{
}
void Enemy_xcz::on_hurt()
{
}
