#include "event_mgr.h"

EventMgr* EventMgr::manager = nullptr;

EventMgr* EventMgr::instance()
{
	if (!manager)
	{
		manager = new EventMgr();
	}
	return manager;
}

EventMgr::EventMgr()
{
	init_custom_events();
}

void EventMgr::destroy()
{
	event_type_map.clear();
	delete manager;
	manager = nullptr;
}

bool EventMgr::init_custom_events()
{
	const int num = static_cast<int>(EventType::COUNT);

	Uint32 id = SDL_RegisterEvents(num);
	if (id == INVALID_EVENT_TYPE) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "自定义事件注册失败：%s", SDL_GetError());
		return false;
	}
	for (int i = 0; i < num; ++i)
	{
		EventType event_type = static_cast<EventType>(i);
		Uint32 sdl_event_id = id + i;
		event_type_map[event_type] = sdl_event_id;
	}
	return true;
}

const Uint32 EventMgr::get_event_type(EventType type)
{
	auto it = event_type_map.find(type);
	if (type == EventType::COUNT || it == event_type_map.end())
	{
		std::cout << "枚举值错误或者未找到对应事件" << std::endl;
		return INVALID_EVENT_TYPE;
	}

	return it->second;
}
//
//bool EventMgr::add_listen_event(const char* type, std::weak_ptr<Obj> executor, EventCallback func, EventParams data, int num, bool is_res, bool is_top)
//{
//	if (executor.expired())
//	{
//		std::cout << type << "  事件对象不能为空!" << std::endl;
//		return false;
//	}
//	if (!func)
//	{
//		std::cout << type << "  回调函数不能为空!" << std::endl;
//		return false;
//	}
//	if (!is_res)
//	{
//		auto it = list_event.find(type);
//		if (it != list_event.end())
//		{
//			std::shared_ptr<Obj> ex_ps = executor.lock();
//			for (const Event& e : it->second)
//			{
//				if (e.executor.lock() == ex_ps)
//				{
//					std::cout << type << "  事件不能重复注册!" << std::endl;
//					return false;
//				}
//			}
//		}
//	}
//	Event new_event = { type, executor, func, data, num, is_res, false, false };
//	if (is_top)
//	{
//		list_event[type].insert(list_event[type].begin(), new_event);
//	}
//	else
//	{
//		list_event[type].push_back(new_event);
//	}
//	return true;
//}
//
//bool EventMgr::delete_listen_event(const char* type, std::weak_ptr<Obj> executor)
//{
//	if (executor.expired())
//	{
//		std::cout << type << "  事件对象不能为空!" << std::endl;
//		return false;
//	}
//	auto it = list_event.find(type);
//	if (it == list_event.end())
//	{
//		std::cout << type << "  事件类型不存在!" << std::endl;
//		return false;
//	}
//	std::shared_ptr<Obj> ex_ps = executor.lock();
//	bool is_find = false;
//	for (Event& e : it->second)
//	{
//		if (e.executor.lock() == ex_ps)
//		{
//			e.can_remove = true;
//			is_find = true;
//		}
//	}
//	if (!is_find)
//	{
//		std::cout << ex_ps->get_ID() << "  事件对象查找失败!" << std::endl;
//	}
//	return is_find;
//}
//
//void EventMgr::send_event(const char* type, EventParams data)
//{
//	auto it = list_event.find(type);
//	if (it == list_event.end())
//	{
//		return;
//	}
//
//	for (Event& e : it->second)
//	{
//		if (is_can_remove(e))
//		{
//			continue;
//		}
//		e.can_execute = true;
//		// 合并参数
//		for (const auto& [key, val] : data) {
//			e.data[key] = val;
//		}
//	}
//}
//
//void EventMgr::send_event_to(const char* type, std::weak_ptr<Obj> target, EventParams data)
//{
//	auto it = list_event.find(type);
//	if (it == list_event.end() || target.expired())
//	{
//		return;
//	}
//
//	std::shared_ptr<Obj> target_ptr = target.lock();
//	for (Event& e : it->second)
//	{
//		if (is_can_remove(e) || e.executor.lock() != target_ptr)
//		{
//			continue;
//		}
//		e.can_execute = true;
//		// 合并参数
//		for (const auto& [key, val] : data) {
//			e.data[key] = val;
//		}
//	}
//}
//
//void EventMgr::dispatch_sdl_event(const SDL_Event& event)
//{
//	EventParams params;
//	
//	static const std::unordered_map<SDL_Keycode, KeyCode> key_map = {
//		{SDLK_w,    KeyCode::KEY_W},
//		{SDLK_UP,   KeyCode::KEY_UP},
//		{SDLK_s,    KeyCode::KEY_S},
//		{SDLK_DOWN, KeyCode::KEY_DOWN},
//		{SDLK_a,    KeyCode::KEY_A},
//		{SDLK_LEFT, KeyCode::KEY_LEFT},
//		{SDLK_d,    KeyCode::KEY_D},
//		{SDLK_RIGHT,KeyCode::KEY_RIGHT}
//	};
//
//	switch (event.type)
//	{
//	case SDL_MOUSEMOTION:
//		{
//			params["point"] = SDL_Point{ event.motion.x, event.motion.y };
//			send_event(EventType::MOUSE_MOVE, params);
//		}
//		break;
//	case SDL_MOUSEBUTTONDOWN:
//		if (event.button.button == SDL_BUTTON_LEFT)
//		{
//			params["point"] = SDL_Point{ event.button.x, event.button.y };
//			send_event(EventType::MOUSE_LEFT_DOWN, params);
//		}
//		break;
//	case SDL_MOUSEBUTTONUP:
//		if (event.button.button == SDL_BUTTON_LEFT)
//		{
//			params["point"] = SDL_Point{ event.button.x, event.button.y };
//			send_event(EventType::MOUSE_LEFT_UP, params);
//			send_event(EventType::MOUSE_LEFT_CLICK, params);
//		}
//		break;
//	case SDL_KEYDOWN:
//		handle_key_event(event.key.keysym.sym, EventType::BTN_DOWN, params, key_map);
//		break;
//	case SDL_KEYUP:
//		handle_key_event(event.key.keysym.sym, EventType::BTN_UP, params, key_map);
//		break;
//	}
//}
//
//void EventMgr::handle_key_event(SDL_Keycode sdl_key, const char* event_type, EventParams& params, const std::unordered_map<SDL_Keycode, KeyCode>& key_map)
//{
//	auto it = key_map.find(sdl_key);
//	if (it != key_map.end())
//	{
//		params["key"] = it->second;
//		send_event(event_type, params);
//	}
//}
//
//void EventMgr::execute_event()
//{
//	for (auto& [type, vec] : list_event)
//	{
//		if (vec.empty())
//		{
//			continue;
//		}
//		for (Event& e : vec)
//		{
//			if (is_can_remove(e))
//			{
//				continue;
//			}
//			std::shared_ptr<Obj> ex_ps = e.executor.lock();
//			if (ex_ps && e.can_execute && e.call_back)
//			{
//				e.call_back(e.data);
//				e.can_execute = false;
//				if (e.execute_num > 0)
//				{
//					e.execute_num--;
//				}
//			}
//		}
//	}
//}
//
//void EventMgr::remove_event()
//{
//	for (auto& [type, vec] : list_event)
//	{
//		auto end = std::remove_if(vec.begin(), vec.end(), [&](const Event& e) {
//			return is_can_remove(e);
//			});
//		vec.erase(end, vec.end());
//
//		if (vec.empty())
//		{
//			list_event.erase(type);
//		}
//	}
//}
//
//void EventMgr::clear_event()
//{
//	list_event.clear();
//}
//
//bool EventMgr::is_can_remove(const Event& e)
//{
//	return e.can_remove || e.execute_num == 0 || e.executor.expired();
//}