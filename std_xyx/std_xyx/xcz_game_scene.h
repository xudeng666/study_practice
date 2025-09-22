#pragma once

#include "scene.h"
#include "tree_node.h"

#include "timer.h"

#include <queue>

class XczGameScene :
    public Scene
{
public:
    XczGameScene() = default;
    virtual ~XczGameScene() = default;

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    // ���ɵ���
    void add_enemy();

private:
    // ����ͼ
    TreeNode_WP bg;
    // �˳���ť
    TreeNode_WP btn_exit;
    // Ѫ��
    TreeNode_WP hp_bar;
    // �����ı�
    TreeNode_WP score_lable;
    // ����
    TreeNode_WP player;
    // ��������
    int enemy_num = 0;
    // ��֡Ҫ��ӵĵ�������
    int enemy_add = 0;
    // ����
    int score = 0;
    // Ѫ��
    int max_hp = 10;
    // �۵����ӵ���
    int deduction_bul = 0;
    // �Ƿ�������ɽ��ٽ׶�
    bool is_enemy_produce_slow = false;
    // �Զ��ظ��ӵ���ʱ��
    Timer timer_bul_recover;
    // �ӵ��������ͣ��������ɽ��ټ�ʱ��
    Timer timer_enemy_produce_slow;
    // �������ɼ�ʱ��
    Timer timer_enemy_produce;
    // �����-������������
    std::queue<TreeNode_SP> enemy_queue;
};

