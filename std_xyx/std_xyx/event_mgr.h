#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>
#include <any>
#include <iostream>

#include "obj.h"

using EventParams = std::unordered_map<std::string, std::any>; // ��ϣ���������
using EventCallback = std::function<void(const EventParams& params)>;

struct Event
{
	std::string type;					// �¼�����
	std::weak_ptr<Obj> executor;		// �¼����ܶ��󣬲���Ϊ��
	EventCallback call_back;			// �¼��ص�����
	EventParams data;					// �ص���������
	int execute_num = -1;				// �¼���ִ�д��� ����Ϊ���޴���
	bool is_res_reg = true;				// �Ƿ�����ظ�ע��
	bool can_execute = false;			// �Ƿ����ִ��
	bool can_remove = false;			// �Ƿ��ɾ��
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
	/// ע���¼�
	/// </summary>
	/// <param name="type">�¼�����</param>
	/// <param name="executor">�¼�����</param>
	/// <param name="func">�ص�����</param>
	/// <param name="data">�ص���������</param>
	/// <param name="num">ִ�д���</param>
	/// <param name="is_res">�Ƿ�����ظ�ע��</param>
	/// <param name="is_top">�Ƿ��ö����ȴ���</param>
	/// <returns>�ɹ�����true</returns>
	bool add_listen_event(const std::string& type, std::weak_ptr<Obj> executor, EventCallback func, EventParams data = {}, int num = -1, bool is_res = true, bool is_top = false)
	{
		if (executor.expired())
		{
			std::cout<< type << "  �¼�������Ϊ��!" << std::endl;
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
						std::cout << type << "  �¼������ظ�ע��!" << std::endl;
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
	/// ע��ɾ��
	/// </summary>
	/// <param name="type">�¼�����</param>
	/// <param name="executor">�¼�����</param>
	/// <returns>�ɹ�����true</returns>
	bool delete_listen_event(const std::string& type, std::weak_ptr<Obj> executor)
	{
		if (executor.expired())
		{
			std::cout << type << "  �¼�������Ϊ��!" << std::endl;
			return false;
		}
		auto it = list_event.find(type);
		if (it == list_event.end())
		{
			std::cout << type << "  �¼����Ͳ�����!" << std::endl;
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
			std::cout << ex_ps->get_ID() << "  �¼��������ʧ��!" << std::endl;
		}
		return is_find;
	}

	/// <summary>
	/// �����¼�
	/// </summary>
	/// <param name="type">�¼�����</param>
	/// <param name="data">�ص���������</param>
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
			// �ϲ�����
			for (const auto& [key, val] : data) {
				e.data[key] = val;
			}
		}
	}
	/// <summary>
	/// ִ���¼��ص�����
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
	/// ɾ���������¼�
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
	/// ����¼��б�
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