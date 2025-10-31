#include "zmdj_game_scene.h"
#include "event_mgr.h"
#include "game_mgr.h"
#include "collision_mgr.h"
#include "tree_mgr.h"
#include "enemy_zmdj.h"
#include "res_mgr.h"

#include "game_btn.h"
#include "game_bar.h"
#include "game_lable.h"

#include "turret_zmdj.h"

#include <assert.h>

INIT_TYPE_NAME(ZmdjGameScene);

void ZmdjGameScene::on_init()
{
    // 怪物池个子弹池节点必须初始化
    enemy_pool = TreeNode::create_obj<GameObj>("enemy_pool");
    bullet_pool = TreeNode::create_obj<GameObj>("bullet_pool");

    // 添加地图
    auto bg_obj = TreeNode::create_obj<GameImg>("bg");
    bg = bg_obj;
    bg_obj->set_position(Vector2(0, 0));
    bg_obj->set_res_name("background");
    bg_obj->set_anchor_mode(AnchorMode::CENTER);
    bg_obj->set_anchor_referent_mode(AnchorMode::CENTER);
    // 添加敌人层
    auto e_box = TreeNode::create_obj<GameObj>("enemy_box");
    enemy_box = e_box;
    e_box->set_position(Vector2(0, 0));
    e_box->set_anchor_mode(AnchorMode::TOPLEFT);
    e_box->set_anchor_referent_mode(AnchorMode::TOPLEFT);
    // 添加子弹层
    auto b_box = TreeNode::create_obj<GameObj>("bullet_box");
    bullet_box = b_box;
    b_box->set_position(Vector2(0, 0));
    b_box->set_anchor_mode(AnchorMode::TOPLEFT);
    b_box->set_anchor_referent_mode(AnchorMode::TOPLEFT);
    // 添加炮台
    auto bat = TreeNode::create_obj<TurretZmdj>("battery");
    battery = bat;
    // 添加准星
    auto cro = TreeNode::create_obj<GameImg>("crosshair");
    crosshair = cro;
    cro->set_position(Vector2(0, 0));
    cro->set_res_name("crosshair");
    cro->set_anchor_mode(AnchorMode::CENTER);
    cro->set_anchor_referent_mode(AnchorMode::CENTER);

    // 添加UI 血条  分数  退出  
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
        // 退出游戏到开始游戏
        GameMgr::instance()->exchange_game(GameType::START);
        }
    );


    TreeMgr::instance()->get_bg_node()->add_children(std::move(bg_obj));

    auto game = TreeMgr::instance()->get_game_node();
    game->add_children(std::move(e_box));
    game->add_children(std::move(b_box));
    game->add_children(std::move(bat));
    game->add_children(std::move(cro));

    auto ui = TreeMgr::instance()->get_ui_node();
    ui->add_children(std::move(bar_obj));
    ui->add_children(std::move(lab_obj));
    ui->add_children(std::move(exit_obj));

    timer_generate.set_one_shot(false);
    timer_generate.set_wait_time(1.5f);
    timer_generate.set_on_timeout([&]()
        {
            // 发送生成敌人事件
            SDL_Event event;
            event.type = EventMgr::instance()->get_event_type(EventType::ADD_ENEMY);
            event.user.data1 = nullptr;
            event.user.data2 = nullptr;
            SDL_PushEvent(&event);
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
    score_lable.lock()->get_obj_as<GameLable>()->set_font("IPix_30");
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
        // 玩家死亡，则切换回开始游戏
        GameMgr::instance()->exchange_game(GameType::START);
    }
    else if (event.type == EventMgr::instance()->get_event_type(EventType::ENEMY_DIE))
    {
        score++;
        Mix_PlayChannel(-1, ResMgr::instance()->find_audio("explosion"), 0);
    }
    else if (event.type == EventMgr::instance()->get_event_type(EventType::ADD_ENEMY))
    {
        add_enemy();
    }
    else if (event.type == EventMgr::instance()->get_event_type(EventType::REDUCE_ENEMY))
    {
        EventData* data = static_cast<EventData*>(event.user.data1);
        if (!data) return;
        TreeNode_WP node;
        if (data->get("node", node))
        {
            if (!node.expired())
            {
                enemy_pool->add_children(node.lock());
            }
        }
    }
}

void ZmdjGameScene::on_update(float delta)
{
    if (_DE_BUG_)
    {
        //std::cout << "ZmdjGameScene::on_update" << std::endl;
    }

    //timer_generate.on_update(delta);
    timer_increase_num_per_gen.on_update(delta);

    // 碰撞检测
    CollisionMgr::instance()->processCollide();
    // 最后将怪物在对象树中按照y轴升序排序。
    if (!enemy_box.expired())
    {
        enemy_box.lock()->sort_children([](const TreeNode_SP& a, const TreeNode_SP& b) {
            return a->get_position().y < b->get_position().y;
            });
    }

    // 更新分数
    score_lable.lock()->get_obj_as<GameLable>()->set_lable_text("SCORE:" + std::to_string(score));
    // 更新血量
    hp_bar.lock()->get_obj_as<GameBar>()->set_percent_num(1.0f * hp / max_hp);
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
        // 如果怪物池有，就直接取出
        if (enemy_pool->get_children_size() > 0)
        {
            auto enemy = enemy_pool->take_out_of_children();
            if (!enemy)
            {
                assert(false && "未知原因怪物池获取错误");
            }
            enemy->on_enter();
            e_box->add_children(std::move(enemy));
        }
        else
        {
            //没有就new一个
            auto enemy_n = TreeNode::create_obj<EnemyZmdj>("enemy_", enemy_num);
            enemy_n->on_enter();
            enemy_num++;
            e_box->add_children(std::move(enemy_n));
        }
    }
}
