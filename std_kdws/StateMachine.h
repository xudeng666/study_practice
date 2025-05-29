#pragma once
#include "StateNode.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

/**
*@brief 	״̬����
*@author	xd
*@date 		2025-5-29
*/
class StateMachine
{
public:
    StateMachine();
    ~StateMachine();
    /*֡����*/
    void on_update(float delta);
    /**
    *@brief 	���ó�ʼ״̬
    *@param 	id ״̬id  
    */
    void set_entry(const std::string& id);
    /**
    *@brief 	�л�״̬
    *@param 	id ״̬id
    */
    void switch_to(const std::string& id);
    /**
    *@brief 	        ע����״̬
    *@param id          ״̬id
    *@param state_node  ״̬����ָ��
    */
    void register_state(const std::string& id, StateNode* state_node);

private:
    /*��ǰ״̬���Ƿ���Ҫ��ʼ��*/
    bool need_init = true;
    /*��ǰ�����״̬�ڵ�*/
    StateNode* current_state = nullptr;
    std::unordered_map<std::string, StateNode*> state_pool;
};