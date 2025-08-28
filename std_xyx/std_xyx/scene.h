#pragma once

//#include "game_obj.h"
//#include "game_mgr.h"

#include <queue>
#include <functional>
#include <string>

#include <SDL.h>

class GameObj;

/*������-����*/
class Scene
{
public:
	Scene();
	virtual ~Scene();
	/*������ʼ��*/
	virtual void on_enter();
	/*��������*/
	virtual void on_update(float delta);
	/*�������*/
	virtual void on_input(const SDL_Event& event);
	/*��Ⱦ��ͼ*/
	virtual void on_render();
	/*�˳�����*/
	virtual void on_exit();
	void set_ID(const std::string id);
	std::string get_ID();

public:
	/// <summary>
	/// ���Ҷ���
	/// </summary>
	/// <param name="id">std::string ����ID</param>
	/// <returns>GameObj* ����ָ��</returns>
	GameObj* find_obj(std::string id);

	// ��ȡUI���ڵ�
	GameObj* get_ui_root();

	/// <summary>
	/// ǰ�������������ȣ�
	/// �ȸ�����
	/// </summary>
	/// <param name="current_node">������ʼ�ڵ�</param>
	/// <param name="callback">�ص�����</param>
	void pre_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback);
	/// <summary>
	/// ���������������ȣ�
	/// ���Ӻ�
	/// </summary>
	/// <param name="current_node">������ʼ�ڵ�</param>
	/// <param name="callback">�ص�����</param>
	void post_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback);

	/// <summary>
	/// ���������������ȣ�
	/// �����˳��
	/// </summary>
	/// <param name="current_node">������ʼ�ڵ�</param>
	/// <param name="callback">�ص�����</param>
	void level_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback);

protected:
	std::string ID;
	// UI ��Ŀ¼
	GameObj* root = nullptr;
	// UI ��Ŀ¼
	GameObj* background = nullptr;
	// UI ��Ŀ¼
	GameObj* entity = nullptr;
	// UI ��Ŀ¼
	GameObj* ui = nullptr;
	// UI ������ ��ʱ�ò���
	// std::unordered_map<std::string, GameObj* > ui_map;
};

