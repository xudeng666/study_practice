#pragma once
/**
*@brief 	状态节点基类
*@author	xd
*@date 		2025-5-29
*/
class StateNode
{
public:
	StateNode() = default;
	~StateNode() = default;

	/**
	*@brief 	编写当前状态节点进入时的初始化逻辑
	*/
	virtual void on_enter() {}
	/**
	*@brief 	编写当前状态节点的行动逻辑
	*@param 	delta 时间流逝
	*/
	virtual void on_update(float delta) {}
	/**
	*@brief 	编写当前状态节点退出时的逻辑
	*/
	virtual void on_exit() {}
};

