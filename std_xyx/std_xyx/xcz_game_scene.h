#pragma once

#include "scene.h"
#include "tree_node.h"

#include "timer.h"

class XczGameScene :
    public Scene
{
public:
    XczGameScene() = default;
    virtual ~XczGameScene() = default;

    XczGameScene(const std::string& id) : Scene(id) {}
    XczGameScene(const std::string& id, int num) : Scene(id, num) {}

    DEFINE_TYPE_NAME(XczGameScene);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
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
    // �ӵ���
    TreeNode_WP bullet_box;
    // ����ؽڵ�-������������
    TreeNode_SP enemy_pool = nullptr;
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
};