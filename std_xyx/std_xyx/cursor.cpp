#include "cursor.h"

#include "res_mgr.h"
#include "event_mgr.h"

INIT_TYPE_NAME(Cursor);

void Cursor::on_init()
{
	set_anchor_mode(AnchorMode::CENTER);
	set_anchor_referent_mode(AnchorMode::TOPLEFT);
	set_texture_map_type(TextureMapType::AUTO);

	auto img = TreeNode::create_obj<GameImg>("cursor");
	img->set_anchor_mode(AnchorMode::TOPLEFT);
	img->set_anchor_referent_mode(AnchorMode::CENTER);
	img->set_anchor_referent_node(self_node);
	img->set_texture_map_type(TextureMapType::AUTO);

	cursor = img;
	add_children(img);
}

void Cursor::on_enter()
{
}

void Cursor::on_input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
	{
		set_position(event.motion.x, event.motion.y);
	}
	break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			is_mouse_lbtn_down = true;
			std::string str = "audio_click_" + getIntRand(1, 3);
			Mix_PlayChannel(-1, ResMgr::instance()->find_audio(str), 0);
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			is_mouse_lbtn_down = false;
		}
		break;
	}
	if (event.type == EventMgr::instance()->get_event_type(EventType::PHF_EVENT_SEND))
	{
		EventData* data = static_cast<EventData*>(event.user.data1);
		if (!data) return;
		int meal;
		if (data->get("meal", meal))
		{
			set_picked(static_cast<Meal>(meal));
		}
	}
}

void Cursor::on_update(float delta)
{
	std::string str = "";
	switch (meal_picked)
	{
	case Meal::None:				break;
	case Meal::Cola:				str = "cola";				break;
	case Meal::Sprite:				str = "sprite";				break;
	case Meal::BraisedChicken_Hot:	str = "bc_hot_picked";		break;
	case Meal::BraisedChicken_Cold:	str = "bc_cold_picked";		break;
	case Meal::MeatBall_Hot:		str = "mb_hot_picked";		break;
	case Meal::MeatBall_Cold:		str = "mb_cold_picked";		break;
	case Meal::RedCookedPork_Hot:	str = "rcp_hot_picked";		break;
	case Meal::RedCookedPork_Cold:	str = "rcp_cold_picked";	break;
	case Meal::BraisedChicken_Box:	str = "bc_box";				break;
	case Meal::MeatBall_Box:		str = "mb_box";				break;
	case Meal::RedCookedPork_Box:	str = "rcp_box";			break;
	case Meal::TakeoutBox:			str = "tb_picked";			break;
	}
	set_res_name(str);
	auto img = cursor.lock()->get_obj_as<GameImg>();
	img->set_res_name(is_mouse_lbtn_down ? "cursor_down" : "cursor_idle");
}

void Cursor::set_picked(Meal meal)
{
	meal_picked = meal;
	// 发送同步事件
	SDL_Event event;
	event.type = EventMgr::instance()->get_event_type(EventType::PHF_EVENT_SYNC);
	EventData* data = new EventData();
	data->set("meal", static_cast<int>(meal_picked));
	event.user.data1 = data;
	event.user.data2 = nullptr;
	SDL_PushEvent(&event);
}

Meal Cursor::get_picked()
{
	return meal_picked;
}