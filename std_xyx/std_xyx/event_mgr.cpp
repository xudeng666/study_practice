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

void EventMgr::destroy()
{
	list_event.clear();
	delete manager;
	manager = nullptr;
}

bool EventMgr::add_listen_event(const std::string& type, std::weak_ptr<Obj> executor, EventCallback func, EventParams data, int num, bool is_res, bool is_top)
{
	if (executor.expired())
	{
		std::cout << type << "  事件对象不能为空!" << std::endl;
		return false;
	}
	if (!func)
	{
		std::cout << type << "  回调函数不能为空!" << std::endl;
		return false;
	}
	if (!is_res)
	{
		auto it = list_event.find(type);
		if (it != list_event.end())
		{
			std::shared_ptr<Obj> ex_ps = executor.lock();
			for (const Event& e : it->second)
			{
				if (e.executor.lock() == ex_ps)
				{
					std::cout << type << "  事件不能重复注册!" << std::endl;
					return false;
				}
			}
		}
	}
	Event new_event = { type, executor, func, data, num, is_res, false, false };
	if (is_top)
	{
		list_event[type].insert(list_event[type].begin(), new_event);
	}
	else
	{
		list_event[type].push_back(new_event);
	}
	return true;
}

bool EventMgr::delete_listen_event(const std::string& type, std::weak_ptr<Obj> executor)
{
	if (executor.expired())
	{
		std::cout << type << "  事件对象不能为空!" << std::endl;
		return false;
	}
	auto it = list_event.find(type);
	if (it == list_event.end())
	{
		std::cout << type << "  事件类型不存在!" << std::endl;
		return false;
	}
	std::shared_ptr<Obj> ex_ps = executor.lock();
	bool is_find = false;
	for (Event& e : it->second)
	{
		if (e.executor.lock() == ex_ps)
		{
			e.can_remove = true;
			is_find = true;
		}
	}
	if (!is_find)
	{
		std::cout << ex_ps->get_ID() << "  事件对象查找失败!" << std::endl;
	}
	return is_find;
}

void EventMgr::send_event(const std::string& type, EventParams data)
{
	auto it = list_event.find(type);
	if (it == list_event.end())
	{
		return;
	}

	for (Event& e : it->second)
	{
		if (is_can_remove(e))
		{
			continue;
		}
		e.can_execute = true;
		// 合并参数
		for (const auto& [key, val] : data) {
			e.data[key] = val;
		}
	}
}

void EventMgr::send_event_to(const std::string& type, std::weak_ptr<Obj> target, EventParams data)
{
	auto it = list_event.find(type);
	if (it == list_event.end() || target.expired())
	{
		return;
	}

	std::shared_ptr<Obj> target_ptr = target.lock();
	for (Event& e : it->second)
	{
		if (is_can_remove(e) || e.executor.lock() != target_ptr)
		{
			continue;
		}
		e.can_execute = true;
		// 合并参数
		for (const auto& [key, val] : data) {
			e.data[key] = val;
		}
	}
}

void EventMgr::dispatch_sdl_event(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
	{
		SDL_Point p = { event.motion.x, event.motion.y };
		EventParams params;
		params["point"] = p;
		send_event(EventType::MOUSE_MOVE, params);
	}
	break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p = { event.button.x, event.button.y };
			EventParams params;
			params["point"] = p;
			send_event(EventType::MOUSE_DOWN_LEFT, params);
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p = { event.button.x, event.button.y };
			EventParams params;
			params["point"] = p;
			send_event(EventType::MOUSE_UP_LEFT, params);
			send_event(EventType::MOUSE_CLICK_LEFT, params);
		}
		break;
		// 可扩展其他事件类型（右键、滚轮等）
	}
}

void EventMgr::execute_event()
{
	for (auto& [type, vec] : list_event)
	{
		if (vec.empty())
		{
			continue;
		}
		for (Event& e : vec)
		{
			if (is_can_remove(e))
			{
				continue;
			}
			std::shared_ptr<Obj> ex_ps = e.executor.lock();
			if (ex_ps && e.can_execute && e.call_back)
			{
				e.call_back(e.data);
				e.can_execute = false;
				if (e.execute_num > 0)
				{
					e.execute_num--;
				}
			}
		}
	}
}

void EventMgr::remove_event()
{
	for (auto& [type, vec] : list_event)
	{
		auto end = std::remove_if(vec.begin(), vec.end(), [&](const Event& e) {
			return is_can_remove(e);
			});
		vec.erase(end, vec.end());

		if (vec.empty())
		{
			list_event.erase(type);
		}
	}
}

void EventMgr::clear_event()
{
	list_event.clear();
}

bool EventMgr::is_can_remove(const Event& e)
{
	return e.can_remove || e.execute_num == 0 || e.executor.expired();
}