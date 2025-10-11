#pragma once

#include <unordered_map>
#include <iostream>

#include"game_obj.h"

class EventMgr
{
public:
	static EventMgr* instance();

	/// <summary>
	/// ���ٹ�����
	/// </summary>
	void destroy();
	/// <summary>
	/// ��ȡ�Զ����¼�����
	/// </summary>
	/// <param name="type">EventType ö������</param>
	/// <returns></returns>
	const Uint32 get_event_type(EventType type);

private:
	EventMgr();
	~EventMgr() = default;

	EventMgr(const EventMgr&) = delete;
	EventMgr& operator=(const EventMgr&) = delete;
	/*��ʼ���Զ����¼��б�*/
	bool init_custom_events();
private:
	static EventMgr* manager;
	std::unordered_map<EventType, Uint32> event_type_map;

public:
	Uint32 INVALID_EVENT_TYPE = 0xFFFFFFFFU;	// ��Ч�¼�
};


//using EventParams = std::unordered_map<std::string, std::any>; // ��ϣ���������
//using EventCallback = std::function<void(const EventParams& params)>;
//
//struct Event
//{
//	std::string type;					// �¼�����
//	std::weak_ptr<Obj> executor;		// �¼����ܶ��󣬲���Ϊ��
//	EventCallback call_back;			// �¼��ص�����
//	EventParams data;					// �ص���������
//	int execute_num = -1;				// �¼���ִ�д��� ����Ϊ���޴���
//	bool is_res_reg = true;				// �Ƿ�����ظ�ע��
//	bool can_execute = false;			// �Ƿ����ִ��
//	bool can_remove = false;			// �Ƿ��ɾ��
//};

	///// <summary>
	///// ע���¼�
	///// </summary>
	///// <param name="type">�¼�����</param>
	///// <param name="executor">�¼�����</param>
	///// <param name="func">�ص�����</param>
	///// <param name="data">�ص���������</param>
	///// <param name="num">ִ�д���</param>
	///// <param name="is_res">�Ƿ�����ظ�ע��</param>
	///// <param name="is_top">�Ƿ��ö����ȴ���</param>
	///// <returns>�ɹ�����true</returns>
	//bool add_listen_event(const char* type, std::weak_ptr<Obj> executor, EventCallback func, EventParams data = {}, int num = -1, bool is_res = true, bool is_top = false);
	//
	///// <summary>
	///// ע��ɾ��
	///// </summary>
	///// <param name="type">�¼�����</param>
	///// <param name="executor">�¼�����</param>
	///// <returns>�ɹ�����true</returns>
	//bool delete_listen_event(const char* type, std::weak_ptr<Obj> executor);

	///// <summary>
	///// �����¼�(�㲥ģʽ)
	///// </summary>
	///// <param name="type">�¼�����</param>
	///// <param name="data">�ص���������</param>
	//void send_event(const char* type, EventParams data = {});

	///// <summary>
	/////  �����¼�������ģʽ����Ŀ�������գ�
	///// </summary>
	///// <param name="type">�¼�����</param>
	///// <param name="target">�¼����ܶ���</param>
	///// <param name="data">�ص���������</param>
	//void send_event_to(const char* type, std::weak_ptr<Obj> target, EventParams data = {});

	///// <summary>
	///// �ַ�SDL�¼�
	///// </summary>
	//void dispatch_sdl_event(const SDL_Event& event);

	///// <summary>
	///// ִ���¼��ص�����
	///// </summary>
	//void execute_event();

	///// <summary>
	///// ɾ���������¼�
	///// </summary>
	//void remove_event();

	///// <summary>
	///// ����¼��б�
	///// </summary>
	//void clear_event();

	//bool is_can_remove(const Event& e);
	/// <summary>
	/// �����¼���ȡ
	/// </summary>
	/// <param name="sdl_key">SDL_key</param>
	/// <param name="event_type">�����¼�</param>
	/// <param name="params">�¼����Ͳ���</param>
	/// <param name="key_map">�¼�ӳ���</param>
	// void handle_key_event(SDL_Keycode sdl_key, const char* event_type, EventParams& params, const std::unordered_map<SDL_Keycode, KeyCode>& key_map);