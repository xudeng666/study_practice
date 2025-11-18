#include "delivery_peple.h"
#include "res_mgr.h"
#include "event_mgr.h"

INIT_TYPE_NAME(DeliveryPeple);

void DeliveryPeple::on_init()
{
}

void DeliveryPeple::on_enter()
{
	refresh();
}

void DeliveryPeple::on_update(float delta)
{
	if (!is_waiting)
	{
		timer_refresh.on_update(delta);
		return;
	}

	time_waited += delta;
	// 等待超时
	if (time_waited >= time_waited_limit)
	{
		refresh();
		// 生命扣除
		return;
	}

	// 检查订单是否都已经交付
	if (std::count(status_list.begin(), status_list.end(), Status::Waiting) == 0)
	{
		refresh();

		// 加分
	}
}

void DeliveryPeple::on_cursor_up()
{
	if (!is_waiting) return;
	if (picked_meal != Meal::None && check_and_place(picked_meal))
	{
		change_picked_meal(Meal::None);
		Mix_PlayChannel(-1, ResMgr::instance()->find_audio("audio_complete"), 0);
		time_waited -= 5.0f;
	}
}

void DeliveryPeple::refresh()
{
	// 重置状态
	time_waited = 0;
	is_waiting = false;
	meal_list.clear();
	status_list.clear();
	num_dish = 0;
	num_drink = 0;

	// 随机刷新时间
	float n = (float)getIntRand(10, 20);
	timer_refresh.set_wait_time(n);
	timer_refresh.restart();

	// 随机外卖员
	is_meituan = getIntRand(0, 1) == 0;

	// 随机餐品数量
	num_drink = getIntRand(0, 8);
	num_dish = getIntRand(0, 4 - std::ceil(num_drink / 2.0f));

	// 随机菜品
	for (int i = 0; i < num_dish; i++)
	{
		switch (getIntRand(0, 2))
		{
		case 0:meal_list.push_back(Meal::BraisedChicken_Hot);	break;
		case 1:meal_list.push_back(Meal::MeatBall_Hot);			break;
		case 2:meal_list.push_back(Meal::RedCookedPork_Hot);	break;
		}
	}

	// 随机饮料
	for (int i = 0; i < num_drink; i++)
	{
		Meal m = Meal::None;
		switch (getIntRand(0, 1))
		{
		case 0:meal_list.push_back(Meal::Cola);		break;
		case 1:meal_list.push_back(Meal::Sprite);	break;
		}
	}
	// 更新餐品状态
	status_list.assign(meal_list.size(), Status::Waiting);
}

bool DeliveryPeple::check_and_place(Meal target)
{
	if (!is_waiting) return false;

	for (int i = 0; i < meal_list.size(); i++)
	{
		if (status_list[i] == Status::Waiting && target == meal_list[i])
		{
			status_list[i] = Status::Completed;
			return true;
		}
	}
	return false;
}