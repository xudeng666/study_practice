#pragma once
#include "scene.h"
#include "tree_node.h"

class PhfGameScene :
    public Scene
{
public:
    PhfGameScene() = default;
    virtual ~PhfGameScene() = default;

    PhfGameScene(const std::string& id) : Scene(id) {}
    PhfGameScene(const std::string& id, int num) : Scene(id, num) {}

    DEFINE_TYPE_NAME(PhfGameScene);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;

private:
    TreeNode_WP bg;                 // 背景图
    TreeNode_WP btn_exit;           // 退出按钮
    TreeNode_WP hp_bar;             // 血条
    TreeNode_WP score_lable;        // 分数文本

    TreeNode_WP cursor;             // 光标

    TreeNode_WP delivery_p1;        // 外卖员1
    TreeNode_WP delivery_p2;        // 外卖员2
    TreeNode_WP delivery_p3;        // 外卖员3

    TreeNode_WP cola_bundle;        // 可乐
    TreeNode_WP sprite_bundle;      // 雪碧
    TreeNode_WP tb_bundle;          // 餐具

    TreeNode_WP mb_box_bundle;      // 餐品1
    TreeNode_WP bc_box_bundle;      // 餐品2
    TreeNode_WP rcp_box_bundle;     // 餐品3

    TreeNode_WP microwave_oven_1;   // 微波炉1
    TreeNode_WP microwave_oven_2;   // 微波炉2

    TreeNode_WP takeout_box_1;      // 餐位1
    TreeNode_WP takeout_box_2;      // 餐位2
    TreeNode_WP takeout_box_3;      // 餐位3
    TreeNode_WP takeout_box_4;      // 餐位4

    int score = 0;                  // 分数
    int max_hp = 10;                // 血量
    int hp = 10;                    // 当前血量
};

