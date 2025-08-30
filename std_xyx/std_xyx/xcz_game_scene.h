#pragma once

#include "scene.h"
#include "game_btn.h"
#include "game_bar.h"
#include "game_lable.h"
#include "character.h"

class XczGameScene :
    public Scene
{
public:
    XczGameScene();
    ~XczGameScene();

    void on_enter() override;
    void on_exit() override;

private:
    GameImg* bg = nullptr;
    // 退出按钮
    GameBtn* btn_exit = nullptr;
    // 血条
    GameBar* hp_bar = nullptr;
    // 分数文本
    GameLable* score_lable = nullptr;
    // 主角
    Character* player = nullptr;
    // 子弹列表
    // 怪物列表
    // 动画列表
    // 分数
    int score = 0;
    // 血量
    int hp = 10;
};

