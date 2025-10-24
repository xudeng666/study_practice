#pragma once
#include "scene.h"
#include "tree_node.h"

#include "timer.h"

enum class ZmdjEnemyType
{
    E_S = 0,
    E_M,
    E_F
};

class ZmdjGameScene:public Scene
{
public:
    ZmdjGameScene() = default;
    virtual ~ZmdjGameScene() = default;

    ZmdjGameScene(const std::string& id) : Scene(id) {}
    ZmdjGameScene(const std::string& id, int num) : Scene(id, num) {}

    DEFINE_TYPE_NAME(ZmdjGameScene);

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
    // ׼��
    TreeNode_WP crosshair;
    // ��̨
    TreeNode_WP battery;
    // ������ ͳһ�������е���
    TreeNode_WP enemy_box;
    // �����-�����ڻ��չ��
    TreeNode_SP enemy_pool = nullptr;
    // �ӵ���-�����ڻ����ӵ���
    TreeNode_SP bullet_pool = nullptr;


    // ��������
    int enemy_num = 0;
    // ����
    int score = 0;
    // Ѫ��
    int max_hp = 10;
    // ��ǰѪ��
    int hp = 10;

    int num_per_gen = 2;                            // ����ÿ����������
    Timer timer_generate;							// �������ɶ�ʱ��
    Timer timer_increase_num_per_gen;				// ����ÿ�ε�������������ʱ��

};

