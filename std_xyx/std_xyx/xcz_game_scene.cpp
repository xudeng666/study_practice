#include "xcz_game_scene.h"
#include "player_xcz.h"
#include "collision_mgr.h"
#include "game_mgr.h"
#include "res_mgr.h"
#include "tree_mgr.h"

#include "game_btn.h"
#include "game_bar.h"
#include "game_lable.h"
#include "enemy_xcz.h"


void XczGameScene::on_init()
{
    auto bg_ptr = TreeNode::create(std::make_unique<GameImg>("bg"));
    bg = bg_ptr;
    auto bg_obj = bg_ptr->get_obj_as<GameImg>();
    bg_obj->set_position(Vector2(0, 0));
    bg_obj->set_res_name("background");
    bg_obj->set_anchor_mode(AnchorMode::CENTER);
    bg_obj->set_anchor_referent_mode(AnchorMode::CENTER);

    auto hp_bar_ptr = TreeNode::create(std::make_unique<GameBar>("hp_bar"));
    hp_bar = hp_bar_ptr;
    auto bar_obj = hp_bar_ptr->get_obj_as<GameBar>();
    bar_obj->set_position(Vector2(-10, 10));
    bar_obj->set_anchor_mode(AnchorMode::TOPRIGHT);
    bar_obj->set_anchor_referent_mode(AnchorMode::TOPRIGHT);
    bar_obj->get_img_bg()->get_obj()->set_display(false);
    bar_obj->set_size({ 320,32 });
    bar_obj->set_max_value({ 320,32 });
    auto bar_pro = bar_obj->get_img_pro()->get_obj_as<GameImg>();
    bar_pro->set_anchor_mode(AnchorMode::LEFTCENTER);
    bar_pro->set_anchor_referent_mode(AnchorMode::LEFTCENTER);
    bar_pro->set_res_name("ui_heart");
    bar_pro->set_texture_map_type(TextureMapType::TILE);

    auto lable_ptr = TreeNode::create(std::make_unique<GameLable>("score_lable"));
    score_lable = lable_ptr;
    auto lab_obj = lable_ptr->get_obj_as<GameLable>();
    lab_obj->set_position(Vector2(0, 10));
    lab_obj->set_anchor_mode(AnchorMode::TOPCENTER);
    lab_obj->set_anchor_referent_mode(AnchorMode::TOPCENTER);
    lab_obj->set_is_shade(true);
    lab_obj->set_lable_color(0xDDFFFFFF);
    lab_obj->set_shade_color(0xFF000000);
    lab_obj->set_lable_anchor_mode(AnchorMode::CENTER);
    lab_obj->set_pos_shade({ -3,2 });
    lab_obj->set_size({ 200,32 });

    auto exit_ptr = TreeNode::create(std::make_unique<GameBtn>("btn_exit"));
    btn_exit = exit_ptr;
    auto exit_obj = exit_ptr->get_obj_as<GameBtn>();
    exit_obj->set_position(Vector2(0, 0));
    exit_obj->set_res_name("ui_goback_");
    exit_obj->set_anchor_mode(AnchorMode::TOPLEFT);
    exit_obj->set_anchor_referent_mode(AnchorMode::TOPLEFT);
    exit_obj->set_on_click([]() {
        // 退出游戏到菜单界面
        GameMgr::instance()->exchange_scene(SceneType::MENU);
        }
    );

    auto player_ptr = TreeNode::create(std::make_unique<Player_xcz>("player"));
    player = player_ptr;
    auto player_obj = player_ptr->get_obj_as<Player_xcz>();

    player_obj->set_on_hurt_fun([&]() { // 被击中则扣掉的子弹数+1
        deduction_bul++;
        Mix_PlayChannel(-1, ResMgr::instance()->find_audio("audio_hurt"), 0);
        });
    player_obj->set_on_hit_fun([&]() {  // 击中怪物加1分，播放音效
        score++;
        Mix_PlayChannel(-1, ResMgr::instance()->find_audio("audio_hit"), 0);
        });

    TreeMgr::instance()->get_bg_node()->add_children(std::move(bg_ptr));
    TreeMgr::instance()->get_game_node()->add_children(std::move(player_ptr));
    auto ui = TreeMgr::instance()->get_ui_node();
    ui->add_children(std::move(hp_bar_ptr));
    ui->add_children(std::move(lable_ptr));
    ui->add_children(std::move(exit_ptr));

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
    p->add_bullet(2);
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

    std::cout << "enemy_queue  num:" << enemy_queue.size() << std::endl;
    // 清理怪物池中的怪物
    std::queue<TreeNode_SP> empty_queue;
    std::swap(enemy_queue, empty_queue);
    std::cout << "enemy_queue1  num:" << enemy_queue.size() << std::endl;

    TreeMgr::instance()->get_game_node()->remove_children_if([](const TreeNode_SP& child) {
        return child->get_obj()->id_contains("enemy");
        });

    Scene::on_exit();
}

void XczGameScene::on_update(float delta)
{
    if (_DE_BUG_)
    {
        //std::cout << "XczGameScene::on_update" << std::endl;
    }
    auto player_obj = player.lock()->get_obj_as<Player_xcz>();
    if (!player_obj->get_alive()) return;

    Scene::on_update(delta);
    // 角色移动速度，每得20分提高8%，最多提升到200%
    int val = score / 20;
    val = val > 9 ? 9 : val;
    float n = pow(1.08f, val);
    player_obj->set_speed(150.0f * n);
    // 子弹每得30分多一颗，最高8颗,最低一颗
    int bn = 2 + score / 30;
    bn = bn > 8 ? 8 : bn;
    bn -= deduction_bul;
    bn = bn < 1 ? 1 : bn;
    if (bn > player_obj->get_bullet_num())
    {
        player_obj->add_bullet(1);
    }
    else if (bn < player_obj->get_bullet_num())
    {
        player_obj->reduce_bullet(1);
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
        if (2 >= player_obj->get_bullet_num())
        {
            is_enemy_produce_slow = true;
            timer_enemy_produce_slow.restart();
        }
    }
    timer_enemy_produce.set_wait_time(t);
    timer_enemy_produce.on_update(delta);

    // 获取玩家当前位置
    Vector2 p = player_obj->get_anchor_position(AnchorMode::CENTER);

    std::vector<TreeNode_WP> t_list;

    auto entity = TreeMgr::instance()->get_game_node();
    // 遍历怪物
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
        enemy_queue.push(std::move(entity->remove_children(node.lock())));
    }
    // 碰撞检测
    CollisionMgr::instance()->processCollide();
    // 最后将怪物和玩家在对象树中按照y轴升序排序。
    entity->sort_children([](const TreeNode_SP& a, const TreeNode_SP& b) {
        //return a->get_position().y < b->get_position().y;
        return a->get_obj()->get_position().y < b->get_obj()->get_position().y;
        });

    // 更新分数
    score_lable.lock()->get_obj_as<GameLable>()->set_lable_text("SCORE:" + std::to_string(score));
    // 更新血量
    int hp = player_obj->get_hp();
    hp_bar.lock()->get_obj_as<GameBar>()->set_percent_num(1.0f * hp / max_hp);

    // 统一添加新怪物
    add_enemy();

    if (!player_obj->get_alive())
    {
        // 退出游戏到菜单界面
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
        // 如果怪物池有，就直接取出
        if (!enemy_queue.empty())
        {
            auto enemy = std::move(enemy_queue.front());
            enemy_queue.pop();
            enemy->get_obj()->on_enter();
            entity->add_children(std::move(enemy));
        }
        else
        {
            //没有就new一个
            auto enemy_n = std::make_unique<Enemy_xcz>("enemy_", enemy_num);
            enemy_n->set_hp(1);
            enemy_n->on_enter();
            enemy_num++;
            auto enemy = TreeNode::create(std::move(enemy_n));
            entity->add_children(std::move(enemy));
        }
        enemy_add--;
    }
}