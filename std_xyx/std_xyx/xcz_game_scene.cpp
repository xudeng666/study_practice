#include "xcz_game_scene.h"
#include "player_xcz.h"
#include "collision_mgr.h"

XczGameScene::XczGameScene()
{
    bg = new GameImg({ 0,0 }, "background");
    bg->set_ID("bg");
    bg->set_anchor_mode(AnchorMode::CENTER);
    bg->set_anchor_referent_mode(AnchorMode::CENTER);

    hp_bar = new GameBar({ -10,10 });
    hp_bar->set_ID("hp_bar");
    hp_bar->set_anchor_mode(AnchorMode::TOPRIGHT);
    hp_bar->set_anchor_referent_mode(AnchorMode::TOPRIGHT);
    hp_bar->get_img_pro()->set_anchor_mode(AnchorMode::LEFTCENTER);
    hp_bar->get_img_pro()->set_anchor_referent_mode(AnchorMode::LEFTCENTER);
    hp_bar->get_img_pro()->set_res_name("ui_heart");
    hp_bar->get_img_pro()->set_texture_map_type(TextureMapType::TILE);
    pre_order_traversal(hp_bar, [&](GameObj* obj) {
        obj->set_size({320,32});
        });
    hp_bar->set_max_value({ 320,32 });

    score_lable = new GameLable({0,10});
    score_lable->set_ID("score_lable");
    score_lable->set_anchor_mode(AnchorMode::TOPCENTER);
    score_lable->set_anchor_referent_mode(AnchorMode::TOPCENTER);
    score_lable->set_is_shade(true);
    score_lable->set_lable_color(0xDDFFFFFF);
    score_lable->set_shade_color(0xFF000000);
    score_lable->set_lable_anchor_mode(AnchorMode::CENTER);
    score_lable->set_pos_shade({-3,2});
    score_lable->set_size({ 200,32 });

    player = new Player_xcz();
    player->set_ID("player");

    background->add_children(bg);
    entity->add_children(player);
    ui->add_children(hp_bar);
    ui->add_children(score_lable);

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
        add_enemy();
        });
    
}

XczGameScene::~XczGameScene()
{
}

void XczGameScene::on_enter()
{
    if (_DE_BUG_)
    {
        std::cout << "XczGameScene::on_enter" << std::endl;
    }
    hp_bar->set_percent_num(1.0f);
    score_lable->set_font("IPix_30");
    score = 0;
    max_hp = 10;
    timer_bul_recover.restart();
    Scene::on_enter();
}

void XczGameScene::on_exit()
{
    if (_DE_BUG_)
    {
        std::cout << "XczGameScene::on_exit" << std::endl;
    }
    Scene::on_exit();
}

void XczGameScene::on_update(float delta)
{
    if (_DE_BUG_)
    {
        //std::cout << "XczGameScene::on_update" << std::endl;
    }
    Scene::on_update(delta);
    // 角色移动速度，每得15分提高8%，最多提升到200%
    int val = score / 15;
    val = val > 9 ? 9 : val;
    float n = pow(1.08f, val);
    player->set_speed(150.0f * n);
    // 子弹每得20分多一颗，最高8颗
    int bn = 3 + score / 20;
    bn = bn > 8 ? 8 : bn;
    bn -= deduction_bul;
    if (bn > player->get_bullet_num())
    {
        player->add_bullet(1);
    }
    // 子弹因为受伤减少时，每 30 秒自动恢复 1 颗子弹（不超过当前分数对应上限）
    if (deduction_bul > 0)
    {
        timer_bul_recover.on_update(delta);
    }

    // 敌人生成时间间隔,每得10分减少0.3秒
    float t = 3.0f - (score / 10 * 0.3f);
    t = t < 1.0 ? 1.0 : t;
    // 子弹数量≤2 时，怪物生成速度临时降低 10%（持续 10 秒）
    if (is_enemy_produce_slow)
    {
        timer_enemy_produce_slow.on_update(delta);
    }
    else
    {
        t *= 1.1;
        if (2 >= player->get_bullet_num())
        {
            is_enemy_produce_slow = true;
            timer_enemy_produce_slow.restart();
        }
    }
    timer_enemy_produce.set_wait_time(t);
    timer_enemy_produce.on_update(delta);

    std::list<GameObj*> enemy_list = entity->get_children();
    Vector2 p = player->get_anchor_position(AnchorMode::CENTER);
    auto it = enemy_list.begin();
    while (it != enemy_list.end()) {
        GameObj* obj = *it;
        if (!obj)
        {
            it = enemy_list.erase(it);
            continue;
        }
        if (obj->get_ID() == "player")
        {
            ++it;
            continue;
        }

        Enemy_xcz* enemy = (Enemy_xcz*)obj;

        if (enemy && enemy->get_hp() == 0)
        {
            enemy->on_exit();
            score++;
            enemy_queue.push(enemy);
            it = enemy_list.erase(it);
        }
        else
        {
            enemy->set_player_pos(p);
            ++it;
        }
    }
    CollisionMgr::instance()->processCollide();
    // 最后将怪物和玩家在对象树中按照y轴升序排序。
    // 如果有空节点，则排在后面
    entity->get_children().sort([](const GameObj* a, const GameObj* b) {
        if (!a) return false;
        if (!b) return true; 
        return a->get_position().y < b->get_position().y;
        });

    // 更新分数
    score_lable->set_lable_text("SCORE:" + std::to_string(score));
    // 更新血量
    hp_bar->set_percent_num(player->get_hp() / max_hp);
}

void XczGameScene::on_render()
{
    Scene::on_render();
    CollisionMgr::instance()->onDebugRender();
}

void XczGameScene::add_enemy()
{
    Enemy_xcz* enemy = nullptr;
    // 如果怪物池有，就直接取出
    if (!enemy_queue.empty())
    {
        enemy = enemy_queue.front();
        enemy_queue.pop();
    }
    else
    {
        //没有就new一个
        enemy = new Enemy_xcz();
    }
    // enter后放入对象树和怪物表
    //enemy_list.push_back(enemy);
    enemy->on_enter();
    entity->add_children(enemy);
}