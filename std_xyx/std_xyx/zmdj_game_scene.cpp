#include "zmdj_game_scene.h"
#include "event_mgr.h"
#include "game_mgr.h"
#include "collision_mgr.h"
#include "tree_mgr.h"

#include "game_btn.h"
#include "game_bar.h"
#include "game_lable.h"

#include <assert.h>

//#include "game_type.h"
//#include "util.h"

INIT_TYPE_NAME(ZmdjGameScene);

void ZmdjGameScene::on_init()
{
    // ����ظ��ӵ��ؽڵ�����ʼ��
    enemy_pool = TreeNode::create_obj<GameObj>("enemy_pool");
    bullet_pool = TreeNode::create_obj<GameObj>("bullet_pool");

    // ��ӵ�ͼ
    auto bg_obj = TreeNode::create_obj<GameImg>("bg");
    bg = bg_obj;
    bg_obj->set_position(Vector2(0, 0));
    bg_obj->set_res_name("background");
    bg_obj->set_anchor_mode(AnchorMode::CENTER);
    bg_obj->set_anchor_referent_mode(AnchorMode::CENTER);
    // ��ӵ��˲�
    auto e_box = TreeNode::create_obj<GameObj>("enemy_box");
    enemy_box = e_box;
    e_box->set_position(Vector2(0, 0));
    bg_obj->set_anchor_mode(AnchorMode::CENTER);
    bg_obj->set_anchor_referent_mode(AnchorMode::CENTER);
    // �����̨

    // ���UI Ѫ��  ����  �˳�  
    auto bar_obj = TreeNode::create_obj<GameBar>("hp_bar");
    hp_bar = bar_obj;
    bar_obj->set_position(Vector2(-10, 0));
    bar_obj->set_anchor_mode(AnchorMode::TOPRIGHT);
    bar_obj->set_anchor_referent_mode(AnchorMode::TOPRIGHT);
    bar_obj->get_img_bg()->set_display(false);
    bar_obj->set_size({ 320,42 });
    bar_obj->set_max_value({ 320,32 });
    auto bar_pro = bar_obj->get_img_pro()->get_obj_as<GameImg>();
    bar_pro->set_anchor_mode(AnchorMode::RIGHTCENTER);
    bar_pro->set_anchor_referent_mode(AnchorMode::RIGHTCENTER);
    bar_pro->set_res_name("heart");
    bar_pro->set_texture_map_type(TextureMapType::TILE);

    auto lab_obj = TreeNode::create_obj<GameLable>("score_lable");
    score_lable = lab_obj;
    lab_obj->set_position(Vector2(0, 10));
    lab_obj->set_anchor_mode(AnchorMode::TOPCENTER);
    lab_obj->set_anchor_referent_mode(AnchorMode::TOPCENTER);
    lab_obj->set_is_shade(true);
    lab_obj->set_lable_color(0xDDFFFFFF);
    lab_obj->set_shade_color(0xFF000000);
    lab_obj->set_lable_anchor_mode(AnchorMode::CENTER);
    lab_obj->set_pos_shade({ -3,2 });
    lab_obj->set_size({ 200,32 });

    auto exit_obj = TreeNode::create_obj<GameBtn>("btn_exit");
    btn_exit = exit_obj;
    exit_obj->set_position(Vector2(0, 0));
    exit_obj->set_res_name("ui_goback_");
    exit_obj->set_anchor_mode(AnchorMode::TOPLEFT);
    exit_obj->set_anchor_referent_mode(AnchorMode::TOPLEFT);
    exit_obj->set_on_click([]() {
        // �˳���Ϸ����ʼ��Ϸ
        GameMgr::instance()->exchange_game(GameType::START);
        }
    );

    timer_generate.set_one_shot(false);
    timer_generate.set_wait_time(1.5f);
    timer_generate.set_on_timeout([&]()
        {
            // �������ɵ����¼�
        });

    timer_increase_num_per_gen.set_one_shot(false);
    timer_increase_num_per_gen.set_wait_time(8.0f);
    timer_increase_num_per_gen.set_on_timeout([&]()
        { num_per_gen += 1; });
}

void ZmdjGameScene::on_enter()
{
    if (_DE_BUG_)
    {
        std::cout << "ZmdjGameScene::on_enter" << std::endl;
    }
    score = 0;
    max_hp = 10;
    enemy_num = 0;
    num_per_gen = 2;
    Scene::on_enter();
}

void ZmdjGameScene::on_exit()
{
    if (_DE_BUG_)
    {
        std::cout << "ZmdjGameScene::on_exit" << std::endl;
    }

    enemy_pool.reset();
    bullet_pool.reset();
}

void ZmdjGameScene::on_input(const SDL_Event& event)
{
    if (event.type == EventMgr::instance()->get_event_type(EventType::PLAYER_DIE))
    {
        // ������������л��ؿ�ʼ��Ϸ
        GameMgr::instance()->exchange_game(GameType::START);
    }
}

void ZmdjGameScene::on_update(float delta)
{
    if (_DE_BUG_)
    {
        //std::cout << "ZmdjGameScene::on_update" << std::endl;
    }
    // ��ײ���
    CollisionMgr::instance()->processCollide();
    // ��󽫹����ڶ������а���y����������
    if (!enemy_box.expired())
    {
        enemy_box.lock()->sort_children([](const TreeNode_SP& a, const TreeNode_SP& b) {
            return a->get_position().y < b->get_position().y;
            });
    }

    // ���·���
    score_lable.lock()->get_obj_as<GameLable>()->set_lable_text("SCORE:" + std::to_string(score));
    // ����Ѫ��
    hp_bar.lock()->get_obj_as<GameBar>()->set_percent_num(1.0f * hp / max_hp);
    // ͳһ����¹���
    add_enemy();
}

void ZmdjGameScene::on_render()
{
    Scene::on_render();
    CollisionMgr::instance()->onDebugRender();
}

void ZmdjGameScene::add_enemy()
{
    auto e_box = enemy_box.lock();
    for (int i = 0; i < num_per_gen; i++)
    {
        int val = getIntRand(0, 99);
        if (val < 50)       // 50%
            // ����һ�����
        else if (val < 80)  // 30%
            // ���ɶ������
        else                // 20%
            // �����������
    }
    while (num_per_gen > 0)
    {
        // ���������У���ֱ��ȡ��
        if (enemy_pool->get_children_size() > 0)
        {
            auto enemy = enemy_pool->take_out_of_children();
            if (!enemy)
            {
                assert(false && "δ֪ԭ�����ػ�ȡ����");
            }
            enemy->on_enter();
            e_box->add_children(std::move(enemy));
        }
        else
        {
            //û�о�newһ��
            auto enemy_n = TreeNode::create_obj<Enemy_xcz>("enemy_", enemy_num);
            enemy_n->on_enter();
            enemy_num++;
            e_box->add_children(std::move(enemy_n));
        }
        enemy_add--;
    }
}
