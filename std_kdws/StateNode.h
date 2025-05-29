#pragma once
/**
*@brief 	״̬�ڵ����
*@author	xd
*@date 		2025-5-29
*/
class StateNode
{
public:
	StateNode() = default;
	~StateNode() = default;

	/**
	*@brief 	��д��ǰ״̬�ڵ����ʱ�ĳ�ʼ���߼�
	*/
	virtual void on_enter() {}
	/**
	*@brief 	��д��ǰ״̬�ڵ���ж��߼�
	*@param 	delta ʱ������
	*/
	virtual void on_update(float delta) {}
	/**
	*@brief 	��д��ǰ״̬�ڵ��˳�ʱ���߼�
	*/
	virtual void on_exit() {}
};

