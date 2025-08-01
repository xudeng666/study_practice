#include "delivery_driver.h"

#include "res_mgr.h"
#include "cursor_mgr.h"

#include "util.h"

DeliveryDriver::DeliveryDriver(int x, int y) :Region({x, y, 192, 272})
{
	timer_refresh.set_one_shot(true);
	timer_refresh.set_on_timeout([&]()
		{
			is_waiting = true;
		});
	refresh();
}

void DeliveryDriver::on_cursor_up()
{
	if (!is_waiting) return;
	Meal meal = CursorMgr::instance()->get_picked();
	if (meal != Meal::None && check_and_place(meal))
	{
		CursorMgr::instance()->set_picked(Meal::None);
		Mix_PlayChannel(-1, ResMgr::instance()->find_audio("complete"), 0);
	}
}

void DeliveryDriver::on_update(float delta)
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
		return;
	}

	// 检查订单是否都已经交付
	if (std::count(status_list.begin(), status_list.end(), Status::Waiting) == 0)
	{
		refresh();
	}
}

void DeliveryDriver::on_render(SDL_Renderer* renderer)
{
	if (!is_waiting)
		return;

	// 绘制外卖员
	SDL_RenderCopy(renderer, ResMgr::instance()->find_texture(is_meituan ? "meituan" : "eleme"), nullptr, &rect);

	// 绘制心情条底板
	SDL_Rect rect_pb = { rect.x - 35, rect.y + 15, 40, 160 };
	SDL_RenderCopy(renderer, ResMgr::instance()->find_texture("patience_border"), nullptr, &rect_pb);

	// 绘制心情条
	int h = (int)(rect_pb.h - 28) * (time_waited / time_waited_limit);
	SDL_Rect rect_pc_src = { 0, h, rect_pb.w, rect_pb.h - h };
	SDL_Rect rect_pc_dst = { rect_pb.x, rect_pb.y + h, rect_pb.w, rect_pb.h - h };
	SDL_RenderCopy(renderer, ResMgr::instance()->find_texture("patience_content"), &rect_pc_src, &rect_pc_dst);

	// 绘制餐品清单底板
	SDL_Rect rect_bubble = { rect.x + 175, rect.y + 55, 76, 139 };
	SDL_RenderCopy(renderer, ResMgr::instance()->find_texture("bubble"), nullptr, &rect_bubble);
	
	// 绘制菜品
	for (int i = 0; i < num_dish; i++)
	{
		SDL_Texture* texture = nullptr;
		switch (meal_list[i])
		{
		case Meal::BraisedChicken_Hot:	texture = ResMgr::instance()->find_texture("bc_icon");	break;
		case Meal::MeatBall_Hot:		texture = ResMgr::instance()->find_texture("mb_icon");	break;
		case Meal::RedCookedPork_Hot:	texture = ResMgr::instance()->find_texture("rcp_icon");	break;
		}
		SDL_Rect rect = { rect_bubble.x + 18,rect_bubble.y + 32 * i + 5,45,25 };
		SDL_SetTextureAlphaMod(texture, (Uint8)((status_list[i] == Status::Waiting ? 1.0f : 0.35f) * 255));
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}

	// 绘制饮料
	for (int i = num_dish; i < meal_list.max_size(); i++)
	{
		SDL_Texture* texture = nullptr;
		switch (meal_list[i])
		{
		case Meal::Cola:	texture = ResMgr::instance()->find_texture("cola_icon");	break;
		case Meal::Sprite:	texture = ResMgr::instance()->find_texture("sprite_icon");	break;
		}
		SDL_Rect rect = { rect_bubble.x + 18 + ((i - num_dish) % 2) * 32, 
			rect_bubble.y + 32 * num_dish + 10 + (i - num_dish) / 2 * 28, 20, 26 };
		SDL_SetTextureAlphaMod(texture, (Uint8)((status_list[i] == Status::Waiting ? 1.0f : 0.35f) * 255));
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}

}

void DeliveryDriver::refresh()
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
		switch (getIntRand(0,2))
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

bool DeliveryDriver::check_and_place(Meal target)
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

