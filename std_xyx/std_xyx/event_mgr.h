#pragma once

#include <unordered_map>
#include <iostream>
#include <variant>
//#include <string>

#include"game_obj.h"

// 事件ID
using EventTypeId = Uint32;

/*事件参数值类型*/
using ParamValue = std::variant<int, EventTypeId, float, bool, std::string, void*, TreeNode_SP, TreeNode_WP, Vector2>;

class EventMgr
{
public:
	static EventMgr* instance();

	/// <summary>
	/// 销毁管理器
	/// </summary>
	void destroy();
	/// <summary>
	/// 获取自定义事件类型
	/// </summary>
	/// <param name="type">EventType 枚举类型</param>
	/// <returns></returns>
	const EventTypeId get_event_type(EventType type);
	/// <summary>
	///	清空自定义事件队列（针对动态参数）
	/// </summary>
	void flush_custom_events();
	/// <summary>
	/// 清除自定义事件参数
	/// </summary>
	/// <param name="event">自定义事件</param>
	void flush_custom_event_param(const SDL_Event& event);

	// 临时注册事件
	EventTypeId add_temp_event();

private:
	EventMgr();
	~EventMgr() = default;

	EventMgr(const EventMgr&) = delete;
	EventMgr& operator=(const EventMgr&) = delete;
	/*初始化自定义事件列表*/
	bool init_custom_events();
private:
	static EventMgr* manager;
	std::unordered_map<EventType, EventTypeId> event_type_map;

	const EventTypeId INVALID_EVENT_TYPE = 0xFFFFFFFFU;	// 无效事件
};

/*事件参数类*/
class EventData {
public:
	/// <summary>
	/// 设置参数
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="key">键值</param>
	/// <param name="value">数据</param>
	template <typename T> void set(const std::string& key, T value)
	{
		data[key] = ParamValue(value);
	}

	/// <summary>
	/// 获取参数
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="key">键值</param>
	/// <param name="out_value">赋值对象</param>
	/// <returns>成功返回trut, 失败返回false</returns>
	template <typename T> bool get(const std::string& key, T& out_value) const
	{
		auto it = data.find(key);
		if (it == data.end()) {
			return false; // 键不存在
		}
		// 尝试将variant转换为目标类型T
		const ParamValue& val = it->second;
		if (const T* p = std::get_if<T>(&val)) {
			out_value = *p;
			return true;
		}
		return false; // 类型不匹配
	}

private:
	std::unordered_map<std::string, ParamValue> data; // 键值对存储参数
};


//using EventParams = std::unordered_map<std::string, std::any>; // 哈希表参数类型
//using EventCallback = std::function<void(const EventParams& params)>;
//
//struct Event
//{
//	std::string type;					// 事件类型
//	std::weak_ptr<Obj> executor;		// 事件接受对象，不可为空
//	EventCallback call_back;			// 事件回调函数
//	EventParams data;					// 回调函数参数
//	int execute_num = -1;				// 事件可执行次数 负数为不限次数
//	bool is_res_reg = true;				// 是否可以重复注册
//	bool can_execute = false;			// 是否可以执行
//	bool can_remove = false;			// 是否可删除
//};

	///// <summary>
	///// 注册事件
	///// </summary>
	///// <param name="type">事件类型</param>
	///// <param name="executor">事件对象</param>
	///// <param name="func">回调函数</param>
	///// <param name="data">回调函数参数</param>
	///// <param name="num">执行次数</param>
	///// <param name="is_res">是否可以重复注册</param>
	///// <param name="is_top">是否置顶优先处理</param>
	///// <returns>成功返回true</returns>
	//bool add_listen_event(const char* type, std::weak_ptr<Obj> executor, EventCallback func, EventParams data = {}, int num = -1, bool is_res = true, bool is_top = false);
	//
	///// <summary>
	///// 注册删除
	///// </summary>
	///// <param name="type">事件类型</param>
	///// <param name="executor">事件对象</param>
	///// <returns>成功返回true</returns>
	//bool delete_listen_event(const char* type, std::weak_ptr<Obj> executor);

	///// <summary>
	///// 发送事件(广播模式)
	///// </summary>
	///// <param name="type">事件类型</param>
	///// <param name="data">回调函数参数</param>
	//void send_event(const char* type, EventParams data = {});

	///// <summary>
	/////  发送事件（定向模式，仅目标对象接收）
	///// </summary>
	///// <param name="type">事件类型</param>
	///// <param name="target">事件接受对象</param>
	///// <param name="data">回调函数参数</param>
	//void send_event_to(const char* type, std::weak_ptr<Obj> target, EventParams data = {});

	///// <summary>
	///// 分发SDL事件
	///// </summary>
	//void dispatch_sdl_event(const SDL_Event& event);

	///// <summary>
	///// 执行事件回调函数
	///// </summary>
	//void execute_event();

	///// <summary>
	///// 删除可清理事件
	///// </summary>
	//void remove_event();

	///// <summary>
	///// 清空事件列表
	///// </summary>
	//void clear_event();

	//bool is_can_remove(const Event& e);
	/// <summary>
	/// 键盘事件提取
	/// </summary>
	/// <param name="sdl_key">SDL_key</param>
	/// <param name="event_type">本地事件</param>
	/// <param name="params">事件发送参数</param>
	/// <param name="key_map">事件映射表</param>
	// void handle_key_event(SDL_Keycode sdl_key, const char* event_type, EventParams& params, const std::unordered_map<SDL_Keycode, KeyCode>& key_map);