#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>
#include <any>
#include <iostream>

#include "obj.h"

using EventParams = std::unordered_map<std::string, std::any>; // 哈希表参数类型
using EventCallback = std::function<void(const EventParams& params)>;

struct Event
{
	std::string type;					// 事件类型
	std::weak_ptr<Obj> executor;		// 事件接受对象，不可为空
	EventCallback call_back;			// 事件回调函数
	EventParams data;					// 回调函数参数
	int execute_num = -1;				// 事件可执行次数 负数为不限次数
	bool is_res_reg = true;				// 是否可以重复注册
	bool can_execute = false;			// 是否可以执行
	bool can_remove = false;			// 是否可删除
}; 

class EventMgr
{
public:
	static EventMgr* instance()
	{
		if (!manager)
		{
			manager = new EventMgr();
		}
		return manager;
	}
	/// <summary>
	/// 注册事件
	/// </summary>
	/// <param name="type">事件类型</param>
	/// <param name="executor">事件对象</param>
	/// <param name="func">回调函数</param>
	/// <param name="data">回调函数参数</param>
	/// <param name="num">执行次数</param>
	/// <param name="is_res">是否可以重复注册</param>
	/// <param name="is_top">是否置顶优先处理</param>
	/// <returns>成功返回true</returns>
	bool add_listen_event(const std::string& type, std::weak_ptr<Obj> executor, EventCallback func, EventParams data = {}, int num = -1, bool is_res = true, bool is_top = false)
	{
		if (executor.expired())
		{
			std::cout<< type << "  事件对象不能为空!" << std::endl;
			return false;
		}
		if (!is_res)
		{
			auto it = list_event.find(type);
			if (it!=list_event.end())
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
		Event new_event = {type, executor, func, data, num, is_res, false, false};
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
	/// <summary>
	/// 注册删除
	/// </summary>
	/// <param name="type">事件类型</param>
	/// <param name="executor">事件对象</param>
	/// <returns>成功返回true</returns>
	bool delete_listen_event(const std::string& type, std::weak_ptr<Obj> executor)
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

	/// <summary>
	/// 发送事件
	/// </summary>
	/// <param name="type">事件类型</param>
	/// <param name="data">回调函数参数</param>
	void send_event(const std::string& type, EventParams data = {})
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
	/// <summary>
	/// 执行事件回调函数
	/// </summary>
	void execute_event()
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
	/// <summary>
	/// 删除可清理事件
	/// </summary>
	void remove_event()
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
	/// <summary>
	/// 清空事件列表
	/// </summary>
	void clear_event()
	{
		list_event.clear();
	}

	bool is_can_remove(const Event& e)
	{
		return e.can_remove || e.execute_num == 0 || e.executor.expired();
	}

private:
	EventMgr() = default;
	~EventMgr() = default;

	EventMgr(const EventMgr&) = delete;
	EventMgr& operator=(const EventMgr&) = delete;
private:
	static EventMgr* manager;
	std::unordered_map<std::string, std::vector<Event>> list_event;
};

EventMgr* EventMgr::manager = nullptr;