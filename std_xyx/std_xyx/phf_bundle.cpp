#include "phf_bundle.h"

#include "event_mgr.h"

INIT_TYPE_NAME(PhfBundle);

void PhfBundle::on_init()
{
	set_anchor_referent_mode(AnchorMode::TOPLEFT);
	set_anchor_mode(AnchorMode::TOPLEFT);
}

void PhfBundle::on_input(const SDL_Event& event)
{
	if (event.type == EventMgr::instance()->get_event_type(EventType::PHF_EVENT_SYNC))
	{
		EventData* data = static_cast<EventData*>(event.user.data1);
		if (!data) return;
		int m;
		if (data->get("meal", m))
		{
			set_picked_meal(static_cast<Meal>(m));
		}
	}
	PhfObj::on_input(event);
}

void PhfBundle::on_cursor_down()
{
	if (picked_meal == Meal::None)
	{
		change_picked_meal(meal);
	}
}

void PhfBundle::on_cursor_up()
{
	if (picked_meal == meal)
	{
		change_picked_meal(Meal::None);
	}
}
//
//void PhfBundle::set_meal(Meal m)
//{
//	meal = m;
//}
//
//Meal PhfBundle::get_meal()
//{
//	return meal;
//}
//
//void PhfBundle::set_picked_meal(Meal m)
//{
//	picked_meal = m;
//}
//
//Meal PhfBundle::get_picked_meal()
//{
//	return picked_meal;
//}
//
//void PhfBundle::change_picked_meal(Meal m)
//{
//	// ·¢ËÍÊÂ¼þ
//	SDL_Event event;
//	event.type = EventMgr::instance()->get_event_type(EventType::PHF_EVENT_SEND);
//	EventData* data = new EventData();
//	data->set("meal", static_cast<int>(m));
//	event.user.data1 = data;
//	event.user.data2 = nullptr;
//	SDL_PushEvent(&event);
//}

INIT_TYPE_NAME(ColaBundle);
void ColaBundle::on_init()
{
	PhfBundle::on_init();
	set_meal(Meal::Cola);
	set_res_name("cola_bundle");
}

INIT_TYPE_NAME(SpriteBundle);
void SpriteBundle::on_init()
{
	PhfBundle::on_init();
	set_meal(Meal::Sprite);
	set_res_name("sprite_bundle");
}

INIT_TYPE_NAME(TbBundle);
void TbBundle::on_init()
{
	PhfBundle::on_init();
	set_meal(Meal::TakeoutBox);
	set_res_name("tb_bundle");
}

INIT_TYPE_NAME(MbBoxBundle);
void MbBoxBundle::on_init()
{
	PhfBundle::on_init();
	set_meal(Meal::MeatBall_Box);
	set_res_name("mb_box_bundle");
}

INIT_TYPE_NAME(BcBoxBundle);
void BcBoxBundle::on_init()
{
	PhfBundle::on_init();
	set_meal(Meal::BraisedChicken_Box);
	set_res_name("bc_box_bundle");
}

INIT_TYPE_NAME(RcpBoxBundle);
void RcpBoxBundle::on_init()
{
	PhfBundle::on_init();
	set_meal(Meal::RedCookedPork_Box);
	set_res_name("rcp_box_bundle");
}