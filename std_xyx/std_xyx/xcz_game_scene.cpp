#include "xcz_game_scene.h"
#include "player_xcz.h"
#include "bullet_box.h"
#include "collision_mgr.h"
#include "game_mgr.h"
#include "res_mgr.h"
#include "tree_mgr.h"
#include "event_mgr.h"

#include "game_btn.h"
#include "game_bar.h"
#include "game_lable.h"
#include "enemy_xcz.h"

#include <assert.h>

INIT_TYPE_NAME(XczGameScene);

void XczGameScene::on_init()
{
    // ����ؽڵ�����ʼ��
    enemy_pool = TreeNode::create_obj<GameObj>("enemy_pool");

    auto bg_obj = TreeNode::create_obj<GameImg>("bg");
    bg = bg_obj;
    bg_obj->set_position(Vector2(0, 0));
    bg_obj->set_res_name("background");
    bg_obj->set_anchor_mode(AnchorMode::CENTER);
    bg_obj->set_anchor_referent_mode(AnchorMode::CENTER);

    auto bar_obj = TreeNode::create_obj<GameBar>("hp_bar");
    hp_bar = bar_obj;
    bar_obj->set_position(Vector2(-10, 0));
    bar_obj->set_anchor_mode(AnchorMode::TOPRIGHT);
    bar_obj->set_anchor_referent_mode(AnchorMode::TOPRIGHT);
    bar_obj->get_img_bg()->set_display(false);
    bar_obj->set_size({ 330,42 });
    bar_obj->set_max_value({ 320,32 });
    auto bar_pro = bar_obj->get_img_pro()->get_obj_as<GameImg>();
    bar_pro->set_anchor_mode(AnchorMode::CENTER);
    bar_pro->set_anchor_referent_mode(AnchorMode::CENTER);
    bar_pro->set_res_name("ui_heart");
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
        // �˳���Ϸ���˵�����
        GameMgr::instance()->exchange_scene(SceneType::MENU);
        }
    );

    auto player_obj = TreeNode::create_obj<Player_xcz>("player");
    player = player_obj;

    player_obj->set_on_hurt_fun([&]() { // ��������۵����ӵ���+1
        deduction_bul++;
        Mix_PlayChannel(-1, ResMgr::instance()->find_audio("audio_hurt"), 0);
        });
    //player_obj->set_on_hit_fun([&]() {});

    TreeNode_SP b_box = TreeNode::create_obj<BulletBox>("bullet_box");
    bullet_box = b_box;
    b_box->set_anchor_mode(AnchorMode::CENTER);
    b_box->set_anchor_referent_mode(AnchorMode::CENTER);
    b_box->set_anchor_referent_node(player);
    auto bbox = b_box->get_obj_as<BulletBox>();
    bbox->set_hit_fun([&]() {// ���й����1�֣�������Ч
        score++;
        Mix_PlayChannel(-1, ResMgr::instance()->find_audio("audio_hit"), 0);
        });

    TreeMgr::instance()->get_bg_node()->add_children(std::move(bg_obj));

    auto game = TreeMgr::instance()->get_game_node();
    game->add_children(std::move(player_obj));
    game->add_children(std::move(b_box));

    auto ui = TreeMgr::instance()->get_ui_node();
    ui->add_children(std::move(bar_obj));
    ui->add_children(std::move(lab_obj));
    ui->add_children(std::move(exit_obj));

    set_ID("XczGameScene");

    timer_bul_recover.set_wait_time(30);
    timer_bul_recover.set_one_shot(false);
    timer_bul_recover.set_on_timeout([&]() {
        if (deduction_bul > 0)
        {
            deduction_bul--;
        }
        });

    timer_enemy_produce_slow.set_wait_time(10);
    timer_enemy_produce_slow.set_one_shot(true);
    timer_enemy_produce_slow.set_on_timeout([&]() {
        is_enemy_produce_slow = false;
        });

    timer_enemy_produce.set_one_shot(false);
    timer_enemy_produce.set_on_timeout([&]() {
        enemy_add++;
        });
}

void XczGameScene::on_enter()
{
    if (_DE_BUG_)
    {
        std::cout << "XczGameScene::on_enter" << std::endl;
    }
    hp_bar.lock()->get_obj_as<GameBar>()->set_percent_num(1.0f);
    score_lable.lock()->get_obj_as<GameLable>()->set_font("IPix_30");
    deduction_bul = 0;
    score = 0;
    max_hp = 10;
    timer_bul_recover.restart();
    auto p = player.lock()->get_obj_as<Player_xcz>();
    p->set_position({ 0,0 });
    p->set_hp(max_hp);
    enemy_num = 0;
    enemy_add = 0;
    Scene::on_enter();
}

void XczGameScene::on_exit()
{
    if (_DE_BUG_)
    {
        std::cout << "XczGameScene::on_exit" << std::endl;
    }

    // ���������еĹ���
    enemy_pool.reset();
}

void XczGameScene::on_update(float delta)
{
    if (_DE_BUG_)
    {
        //std::cout << "XczGameScene::on_update" << std::endl;
    }
    auto player_obj = player.lock()->get_obj_as<Player_xcz>();
    auto bul_box = bullet_box.lock()->get_obj_as<BulletBox>();
    if (!player_obj->get_alive()) return;

    // ��ɫ�ƶ��ٶȣ�ÿ��20�����8%�����������200%
    int val = score / 20;
    val = val > 9 ? 9 : val;
    float n = pow(1.08f, val);
    player_obj->set_speed(150.0f * n);
    // �ӵ�ÿ��30�ֶ�һ�ţ����8��,���һ��
    int bn = 2 + score / 30;
    bn = bn > 8 ? 8 : bn;
    bn -= deduction_bul;
    bn = bn < 1 ? 1 : bn;
    if (bn > bul_box->get_children_size())
    {
        SDL_Event event;
        event.type = EventMgr::instance()->get_event_type(EventType::ADD_BULLET);
        SDL_PushEvent(&event);
    }
    else if (bn < bul_box->get_children_size())
    {
        SDL_Event event;
        event.type = EventMgr::instance()->get_event_type(EventType::REDUCE_BULLET);
        SDL_PushEvent(&event);
    }
    // �ӵ���Ϊ���˼���ʱ��ÿ 30 ���Զ��ָ� 1 ���ӵ�����������ǰ������Ӧ���ޣ�
    if (deduction_bul > 0)
    {
        timer_bul_recover.on_update(delta);
    }

    // ��������ʱ����,ÿ��10�ּ���0.1��
    float t = 1.5f - (score / 10 * 0.1f);
    t = t < 0.3 ? 0.3 : t;
    // �ӵ�������2 ʱ�����������ٶ���ʱ���� 10%������ 10 �룩
    if (is_enemy_produce_slow)
    {
        timer_enemy_produce_slow.on_update(delta);
    }
    else
    {
        t *= 1.1;
        if (2 >= bul_box->get_children_size())
        {
            is_enemy_produce_slow = true;
            timer_enemy_produce_slow.restart();
        }
    }
    timer_enemy_produce.set_wait_time(t);
    timer_enemy_produce.on_update(delta);

    // ��ȡ��ҵ�ǰλ��
    Vector2 p = player_obj->get_anchor_position(AnchorMode::CENTER);

    std::vector<TreeNode_WP> t_list;

    auto entity = TreeMgr::instance()->get_game_node();
    // ��������
    entity->for_each_child([&](TreeNode_SP node) {
        auto enemy = node->get_obj_as<Enemy_xcz>();
        if (enemy && enemy->id_contains("enemy"))
        {
            if (enemy->get_alive())
            {
                enemy->set_player_pos(p);
            }
            else
            {
                t_list.push_back(node);
            }
        }
        });

    for (TreeNode_WP& node : t_list)
    {
        //std::cout << "delete:  " << obj->get_ID() << std::endl;
        enemy_pool->add_children(entity->remove_children(node.lock()));
    }
    // ��ײ���
    CollisionMgr::instance()->processCollide();
    // ��󽫹��������ڶ������а���y����������
    entity->sort_children([](const TreeNode_SP& a, const TreeNode_SP& b) {
        return a->get_position().y < b->get_position().y;
        });

    // ���·���
    score_lable.lock()->get_obj_as<GameLable>()->set_lable_text("SCORE:" + std::to_string(score));
    // ����Ѫ��
    int hp = player_obj->get_hp();
    hp_bar.lock()->get_obj_as<GameBar>()->set_percent_num(1.0f * hp / max_hp);

    // ͳһ����¹���
    add_enemy();

    if (!player_obj->get_alive())
    {
        // �˳���Ϸ���˵�����
        GameMgr::instance()->exchange_scene(SceneType::MENU);
    }
}

void XczGameScene::on_render()
{
    Scene::on_render();
    CollisionMgr::instance()->onDebugRender();
}

void XczGameScene::add_enemy()
{
    auto entity = TreeMgr::instance()->get_game_node();
    while (enemy_add > 0)
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
            entity->add_children(std::move(enemy));
        }
        else
        {
            //û�о�newһ��
            auto enemy_n = TreeNode::create_obj<Enemy_xcz>("enemy_", enemy_num);
            enemy_n->on_enter();
            enemy_num++;
            entity->add_children(std::move(enemy_n));
        }
        enemy_add--;
    }
}