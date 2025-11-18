#include "takeout_box.h"
#include "event_mgr.h"

INIT_TYPE_NAME(TakeoutBox);


void TakeoutBox::on_init()
{
	set_size(92, 32);
	set_anchor_mode(AnchorMode::BOTTOMCENTER);
}

void TakeoutBox::on_update(float delta)
{
}

void TakeoutBox::on_cursor_down()
{
	if (picked_meal == Meal::None)
	{
		change_picked_meal(meal);
		meal = Meal::None;
		set_res_name(get_res_name());
	}
}

void TakeoutBox::on_cursor_up()
{
	// 如果当前位置是空的快餐盒
	if (meal == Meal::TakeoutBox)
	{
		switch (picked_meal)
		{
		case Meal::BraisedChicken_Box:
			meal = Meal::BraisedChicken_Cold;
			change_picked_meal(Meal::None);
			break;
		case Meal::MeatBall_Box:
			meal = Meal::MeatBall_Cold;
			change_picked_meal(Meal::None);
			break;
		case Meal::RedCookedPork_Box:
			meal = Meal::RedCookedPork_Cold;
			change_picked_meal(Meal::None);
			break;
		}
		set_res_name(get_res_name());
	}
	// 否则如果当前位置没有物品并且光标抓取了可放置的物品
	else if (meal == Meal::None && can_place(picked_meal))
	{
		meal = picked_meal;
		change_picked_meal(Meal::None);
		set_res_name(get_res_name());
	}
}

std::string TakeoutBox::get_res_name()
{
	std::string str = "";
	switch (meal)
	{
	case Meal::None:				break;
	case Meal::BraisedChicken_Hot:	str = "bc_hot";  	break;
	case Meal::BraisedChicken_Cold:	str = "bc_cold"; 	break;
	case Meal::MeatBall_Hot:		str = "mb_hot";  	break;
	case Meal::MeatBall_Cold:		str = "mb_cold"; 	break;
	case Meal::RedCookedPork_Hot:	str = "rcp_hot"; 	break;
	case Meal::RedCookedPork_Cold:	str = "rcp_cold";	break;
	case Meal::TakeoutBox:			str = "tb";      	break;
	}
	//std::cout << "tb_ID:" << ID << "      new res_name:" << str << std::endl;
	return str;
}

bool TakeoutBox::can_place(Meal m)
{
	return m == Meal::BraisedChicken_Hot || m == Meal::BraisedChicken_Cold
		|| m == Meal::MeatBall_Hot || m == Meal::MeatBall_Cold
		|| m == Meal::RedCookedPork_Hot || m == Meal::RedCookedPork_Cold
		|| m == Meal::TakeoutBox;
}
