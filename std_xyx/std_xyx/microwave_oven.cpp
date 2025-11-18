#include "microwave_oven.h"
#include "res_mgr.h"
#include "event_mgr.h"

INIT_TYPE_NAME(MicrowaveOven);

void MicrowaveOven::on_init()
{
	set_anchor_mode(AnchorMode::TOPLEFT);

	auto img = TreeNode::create_obj<GameImg>("food");
	img->set_anchor_mode(AnchorMode::BOTTOMCENTER);
	img->set_anchor_referent_mode(AnchorMode::CENTER);
	img->set_anchor_referent_node(self_node);
	img->set_texture_map_type(TextureMapType::AUTO);
	img->set_position(16, 16);
	food = img;
	add_children(img);

	change_render();

	timer.set_one_shot(true);
	timer.set_wait_time(9.0f);
	timer.set_on_timeout([&]()
		{
			is_working = false;
			change_render();
			Mix_PlayChannel(-1, ResMgr::instance()->find_audio("audio_mo_complete"), 0);
		});
}

void MicrowaveOven::on_update(float delta)
{
	if (is_working)
	{
		timer.on_update(delta);
	}
}

void MicrowaveOven::on_cursor_down()
{
	std::cout << "on_cursor_down" << std::endl;
	if (!is_working && picked_meal == Meal::None)
	{
		std::cout << "on_cursor_down1" << std::endl;
		change_picked_meal(meal);
		meal = Meal::None;
		change_render();
	}
}

void MicrowaveOven::on_cursor_up()
{
	std::cout << "on_cursor_up" << std::endl;
	if (!is_working && meal == Meal::None && can_place(picked_meal))
	{
		std::cout << "on_cursor_up1" << std::endl;
		switch (picked_meal)
		{
		case Meal::BraisedChicken_Cold:
			meal = Meal::BraisedChicken_Hot;
			break;
		case Meal::MeatBall_Cold:
			meal = Meal::MeatBall_Hot;
			break;
		case Meal::RedCookedPork_Cold:
			meal = Meal::RedCookedPork_Hot;
			break;
		}
		timer.restart();
		is_working = true;
		change_render();
		change_picked_meal(Meal::None);
		Mix_PlayChannel(-1, ResMgr::instance()->find_audio("audio_mo_working"), 0);
	}
}

bool MicrowaveOven::can_place(Meal m)
{
	return m == Meal::BraisedChicken_Cold
		|| m == Meal::MeatBall_Cold
		|| m == Meal::RedCookedPork_Cold;
}

void MicrowaveOven::change_render()
{
	auto img = food.lock()->get_obj_as<GameImg>();
	if (is_working)
	{
		std::cout << "change_render1" << std::endl;
		set_res_name("mo_working");
		img->set_res_name("");
	}
	else
	{
		std::cout << "change_render2" << std::endl;
		set_res_name("mo_opening");

		std::string str = "";
		switch (meal)
		{
		case Meal::None:	break;
		case Meal::BraisedChicken_Hot:	str = "bc_hot_picked";	break;
		case Meal::MeatBall_Hot:		str = "mb_hot_picked";	break;
		case Meal::RedCookedPork_Hot:	str = "rcp_hot_picked";	break;
		}
		img->set_res_name(str);
	}
}