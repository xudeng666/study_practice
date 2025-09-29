#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <any>

using EventParams = std::unordered_map<std::string, std::any>; // ��ϣ���������
using EventCallback = std::function<void(const EventParams& params)>;

struct Event
{
	std::string type;					// �¼�����
	std::weak_ptr<void> executor;		// �¼����ܶ��󣬲���Ϊ��
	EventCallback call_back;			// �¼��ص�����
	int executable_num = -1;			// �¼���ִ�д��� ����Ϊ���޴���
	bool can_executable = false;		// �Ƿ����ִ��
	bool can_remove = false;			// �Ƿ��ɾ��
	bool is_res_reg = false;			// �Ƿ�����ظ�ע��
}; 

class EventManager
{
};

