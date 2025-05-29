#pragma once
#include "StateNode.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

/**
*@brief 	状态机类
*@author	xd
*@date 		2025-5-29
*/
class StateMachine
{
public:
    StateMachine();
    ~StateMachine();
    /*帧更新*/
    void on_update(float delta);
    /**
    *@brief 	设置初始状态
    *@param 	id 状态id  
    */
    void set_entry(const std::string& id);
    /**
    *@brief 	切换状态
    *@param 	id 状态id
    */
    void switch_to(const std::string& id);
    /**
    *@brief 	        注册新状态
    *@param id          状态id
    *@param state_node  状态对象指针
    */
    void register_state(const std::string& id, StateNode* state_node);

private:
    /*当前状态机是否需要初始化*/
    bool need_init = true;
    /*当前激活的状态节点*/
    StateNode* current_state = nullptr;
    std::unordered_map<std::string, StateNode*> state_pool;
};