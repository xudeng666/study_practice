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
    // 生成敌人
    void add_enemy();

private:
    // 背景图
    TreeNode_WP bg;
    // 退出按钮
    TreeNode_WP btn_exit;
    // 血条
    TreeNode_WP hp_bar;
    // 分数文本
    TreeNode_WP score_lable;
    // 准星
    TreeNode_WP crosshair;
    // 炮台
    TreeNode_WP battery;
    // 怪物箱 统一放置所有敌人
    TreeNode_WP enemy_box;
    // 怪物池-（用于回收怪物）
    TreeNode_SP enemy_pool = nullptr;
    // 子弹池-（用于回收子弹）
    TreeNode_SP bullet_pool = nullptr;


    // 敌人总数
    int enemy_num = 0;
    // 分数
    int score = 0;
    // 血量
    int max_hp = 10;
    // 当前血量
    int hp = 10;

    int num_per_gen = 2;                            // 敌人每次生成数量
    Timer timer_generate;							// 敌人生成定时器
    Timer timer_increase_num_per_gen;				// 增加每次敌人生成数量定时器

};

