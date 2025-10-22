#include "event_mgr.h"

#include "assert.h"

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

	EventTypeId id = SDL_RegisterEvents(num);
	if (id == INVALID_EVENT_TYPE)
	{
		assert(false && "通用事件注册失败");
		return false;
	}
	for (int i = 0; i < num; ++i)
	{
		EventType event_type = static_cast<EventType>(i);
		EventTypeId sdl_event_id = id + i;
		event_type_map[event_type] = sdl_event_id;
	}
	return true;
}

const EventTypeId EventMgr::get_event_type(EventType type)
{
	auto it = event_type_map.find(type);
	if (type == EventType::COUNT || it == event_type_map.end())
	{
		assert(false && "枚举值错误或者未找到对应事件");
	}

	return it->second;
}

void EventMgr::flush_custom_events()
{
	const EventTypeId min = get_event_type(EventType::COLLISION);

	int last = static_cast<int>(EventType::COUNT) - 1;
	EventType last_event = static_cast<EventType>(last);
	const EventTypeId max = get_event_type(last_event);

	SDL_Event events[1024];				// 临时数组存储事件（大小根据队列最大容量设置）
	int event_count = SDL_PeepEvents(
		events,							// 存储事件的数组
		1024,							// 数组最大容量
		SDL_PEEKEVENT,					// 模式：只读不删除
		min,							// 最小类型
		max								// 最大类型
	);
	for (int i = 0; i < event_count; ++i) {
		SDL_Event& event = events[i];
		// 取出参数对象指针（假设存在自定义参数）
		EventData* datas = static_cast<EventData*>(event.user.data1);
		if (datas) {
			delete datas; // 释放动态内存（或用智能指针管理）
		}
	}
	SDL_FlushEvents(min, max);
}

EventTypeId EventMgr::add_temp_event() {
	EventTypeId temp_id = SDL_RegisterEvents(1);
	if (temp_id == INVALID_EVENT_TYPE) 
	{
		assert(false && "临时事件注册失败");
	}
	return temp_id;
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