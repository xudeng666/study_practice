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
    // 主角
    TreeNode_WP player;
    // 敌人总数
    int enemy_num = 0;
    // 本帧要添加的敌人总数
    int enemy_add = 0;
    // 分数
    int score = 0;
    // 血量
    int max_hp = 10;
    // 扣掉的子弹数
    int deduction_bul = 0;
    // 是否怪物生成降速阶段
    bool is_enemy_produce_slow = false;
    // 自动回复子弹计时器
    Timer timer_bul_recover;
    // 子弹数量过低，怪物生成降速计时器
    Timer timer_enemy_produce_slow;
    // 怪物生成计时器
    Timer timer_enemy_produce;
    // 怪物池-（存放死亡怪物）
    std::queue<TreeNode_SP> enemy_queue;
};

