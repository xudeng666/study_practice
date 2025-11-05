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
    // 怪物池节点必须初始化
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
    bar_obj->set_size({ 320,42 });
    bar_obj->set_max_value({ 320,32 });
    auto bar_pro = bar_obj->get_img_pro()->get_obj_as<GameImg>();
    bar_pro->set_anchor_mode(AnchorMode::RIGHTCENTER);
    bar_pro->set_anchor_referent_mode(AnchorMode::RIGHTCENTER);
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
        // 退出游戏到菜单界面
        GameMgr::instance()->exchange_scene(SceneType::MENU);
        }
    );

    auto player_obj = TreeNode::create_obj<Player_xcz>("player");
    player = player_obj;

    player_obj->set_on_hurt_fun([&]() { // 被击中则扣掉的子弹数+1
        std::cout << "被击中" << std::endl;
        deduction_bul++;
        });
    //player_obj->set_on_hit_fun([&]() {});

    TreeNode_SP b_box = TreeNode::create_obj<BulletBox>("bullet_box");
    bullet_box = b_box;
    b_box->set_anchor_mode(AnchorMode::CENTER);
    b_box->set_anchor_referent_mode(AnchorMode::CENTER);
    b_box->set_position({0,0});
    b_box->set_size({0,0});
    b_box->set_anchor_referent_node(player);
    b_box->set_angle_anchor_mode(AnchorMode::CENTER);
    b_box->set_center({ 0,0 });
    auto bbox = b_box->get_obj_as<BulletBox>();
    bbox->set_hit_fun([&]() {// 击中怪物加1分，播放音效
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
    enemy_list.clear();
    // 清理怪物池中的怪物
    enemy_pool.reset();
}

void XczGameScene::on_input(const SDL_Event& event)
{
    if (event.type == EventMgr::instance()->get_event_type(EventType::PLAYER_DIE))
    {
        // 玩家死亡，则切换回菜单场景
        GameMgr::instance()->exchange_scene(SceneType::MENU);
    }
}

void XczGameScene::on_update(float delta)
{
    if (_DE_BUG_)
    {
        //std::cout << "XczGameScene::on_update" << std::endl;
    }

    auto entity = TreeMgr::instance()->get_game_node();
    for (TreeNode_WP& node : enemy_list)
    {
        auto enemy = node.lock();
        if (enemy)
        {
            enemy_pool->add_children(node.lock());
        }
    }
    enemy_list.clear();

    auto player_obj = player.lock()->get_obj_as<Player_xcz>();
    auto bul_box = bullet_box.lock()->get_obj_as<BulletBox>();
    if (!player_obj->get_alive()) return;

    // 角色移动速度，每得20分提高8%，最多提升到200%
    int val = score / 20;
    val = val > 9 ? 9 : val;
    float n = pow(1.08f, val);
    player_obj->set_speed(150.0f * n);
    // 子弹每得30分多一颗，最高8颗,最低1颗，初始2颗
    int bn = 2 + score / 30;
    bn = bn > 8 ? 8 : bn;
    bn -= deduction_bul;
    bn = bn < 1 ? 1 : bn;
    if (bn > bul_box->get_bullet_num())
    {
        SDL_Event event;
        event.type = EventMgr::instance()->get_event_type(EventType::ADD_BULLET);
        event.user.data1 = nullptr;
        event.user.data2 = nullptr;
        SDL_PushEvent(&event);
    }
    else if (bn < bul_box->get_bullet_num())
    {
        SDL_Event event;
        event.type = EventMgr::instance()->get_event_type(EventType::REDUCE_BULLET);
        event.user.data1 = nullptr;
        event.user.data2 = nullptr;
        SDL_PushEvent(&event);
    }
    // 子弹因为受伤减少时，每 30 秒自动恢复 1 颗子弹（不超过当前分数对应上限）
    if (deduction_bul > 0)
    {
        timer_bul_recover.on_update(delta);
    }

    // 敌人生成时间间隔,每得10分减少0.1秒
    float t = 1.5f - (score / 10 * 0.1f);
    t = t < 0.3 ? 0.3 : t;
    // 子弹数量≤2 时，怪物生成速度临时降低 10%（持续 10 秒）
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

    // 碰撞检测
    CollisionMgr::instance()->processCollide();
    // 最后将怪物和玩家在对象树中按照y轴升序排序。
    entity->sort_children([](const TreeNode_SP& a, const TreeNode_SP& b) {
        return a->get_rect_position().y < b->get_rect_position().y;
        }); 

    // 更新分数
    score_lable.lock()->get_obj_as<GameLable>()->set_lable_text("SCORE:" + std::to_string(score));
    // 更新血量
    int hp = player_obj->get_hp();
    hp_bar.lock()->get_obj_as<GameBar>()->set_percent_num(1.0f * hp / max_hp);

    // 统一添加新怪物
    add_enemy();
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
        // 如果怪物池有，就直接取出
        if (enemy_pool->get_children_size() > 0)
        {
            auto enemy = enemy_pool->take_out_of_children();
            if (!enemy)
            {
                assert(false && "未知原因怪物池获取错误");
            }
            enemy->on_enter();
            entity->add_children(std::move(enemy));
        }
        else
        {
            //没有就new一个
            auto enemy_n = TreeNode::create_obj<Enemy_xcz>("enemy_", enemy_num);
            std::weak_ptr<Enemy_xcz> enemy_w = enemy_n;
            enemy_n->on_enter();
            enemy_num++;
            enemy_n->set_on_hurt_fun([enemy_w,this]() {
                auto enemy = enemy_w.lock();
                if (enemy && !enemy->get_alive())
                {
                    enemy_list.push_back(enemy_w);
                }
                });
            enemy_n->set_on_hit_fun([enemy_w, this]() { // 怪物击中角色 播放音效
                Mix_PlayChannel(-1, ResMgr::instance()->find_audio("audio_hurt"), 0);
                auto enemy = enemy_w.lock();
                if (enemy && !enemy->get_alive())
                {
                    enemy_list.push_back(enemy_w);
                }
                });
            entity->add_children(std::move(enemy_n));
        }
        enemy_add--;
    }
}