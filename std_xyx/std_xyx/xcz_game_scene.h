#pragma once

#include "scene.h"
#include "game_btn.h"
#include "game_bar.h"
#include "game_lable.h"
#include "player_xcz.h"
#include "enemy_xcz.h"
//#include "timer.h"

class XczGameScene :
    public Scene
{
public:
    XczGameScene();
    ~XczGameScene();

    void on_enter() override;
    void on_exit() override;
    void on_update(float delta) override;
    // 生成敌人
    void add_enemy();

private:
    GameImg* bg = nullptr;
    // 退出按钮
    GameBtn* btn_exit = nullptr;
    // 血条
    GameBar* hp_bar = nullptr;
    // 分数文本
    GameLable* score_lable = nullptr;
    // 主角
    Player_xcz* player = nullptr;
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
    // 怪物池用来存放已经死亡的怪物
    std::queue<Enemy_xcz*> enemy_queue;
};

