#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <any>

using EventParams = std::unordered_map<std::string, std::any>; // 哈希表参数类型
using EventCallback = std::function<void(const EventParams& params)>;

struct Event
{
	std::string type;					// 事件类型
	std::weak_ptr<void> executor;		// 事件接受对象，不可为空
	EventCallback call_back;			// 事件回调函数
	int executable_num = -1;			// 事件可执行次数 负数为不限次数
	bool can_executable = false;		// 是否可以执行
	bool can_remove = false;			// 是否可删除
	bool is_res_reg = false;			// 是否可以重复注册
}; 

class EventManager
{
};

