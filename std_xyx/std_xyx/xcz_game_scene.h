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
    // ���ɵ���
    void add_enemy();

private:
    GameImg* bg = nullptr;
    // �˳���ť
    GameBtn* btn_exit = nullptr;
    // Ѫ��
    GameBar* hp_bar = nullptr;
    // �����ı�
    GameLable* score_lable = nullptr;
    // ����
    Player_xcz* player = nullptr;
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
    // �������������Ѿ������Ĺ���
    std::queue<Enemy_xcz*> enemy_queue;
};

