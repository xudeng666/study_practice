#include "player_xcz.h"


Player_xcz::Player_xcz()
{

	ani_pool["left"] = Ani_Res("paimon_left_", 6);
	ani_pool["right"] = Ani_Res("paimon_right_", 6);
}

Player_xcz::~Player_xcz()
{
	Character::~Character();
}

void Player_xcz::on_enter()
{
	if (_DE_BUG_)
	{
		std::cout << ID <<"  on_enter" << std::endl;
	}

	set_step_length(48);
	set_speed(100);

	click_enabled = false;
	position = { 0,0 };
	size = { 0,0 };
	hp = 10;
	anchor_mode = AnchorMode::CENTER;
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
	on_move(delta);
}

void Player_xcz::set_face(bool is_left)
{
	set_animation(is_left ? ani_pool["left"] : ani_pool["right"]);
}

void Player_xcz::on_render()
{
}
void Player_xcz::on_hurt()
{
}