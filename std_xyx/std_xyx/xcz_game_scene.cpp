#include "xcz_game_scene.h"
#include "player_xcz.h"
#include "collision_mgr.h"
#include "game_mgr.h"
#include "res_mgr.h"

XczGameScene::XczGameScene()
{
    auto bg_ptr = std::make_unique<GameImg>(Vector2(0, 0), "background");
    bg = bg_ptr.get();
    bg->set_ID("bg");
    bg->set_anchor_mode(AnchorMode::CENTER);
    bg->set_anchor_referent_mode(AnchorMode::CENTER);

    auto hp_bar_ptr = std::make_unique<GameBar>(Vector2(-10, 10));
    hp_bar = hp_bar_ptr.get();
    hp_bar->set_ID("hp_bar");
    hp_bar->set_anchor_mode(AnchorMode::TOPRIGHT);
    hp_bar->set_anchor_referent_mode(AnchorMode::TOPRIGHT);
    hp_bar->get_img_bg()->set_display(false);
    hp_bar->get_img_pro()->set_anchor_mode(AnchorMode::LEFTCENTER);
    hp_bar->get_img_pro()->set_anchor_referent_mode(AnchorMode::LEFTCENTER);
    hp_bar->get_img_pro()->set_res_name("ui_heart");
    hp_bar->get_img_pro()->set_texture_map_type(TextureMapType::TILE);
    pre_order_traversal(hp_bar, [&](GameObj* obj) {
        obj->set_size({320,32});
        });
    hp_bar->set_max_value({ 320,32 });

    auto lable_ptr = std::make_unique<GameLable>(Vector2(0, 10));
    score_lable = lable_ptr.get();
    score_lable->set_ID("score_lable");
    score_lable->set_anchor_mode(AnchorMode::TOPCENTER);
    score_lable->set_anchor_referent_mode(AnchorMode::TOPCENTER);
    score_lable->set_is_shade(true);
    score_lable->set_lable_color(0xDDFFFFFF);
    score_lable->set_shade_color(0xFF000000);
    score_lable->set_lable_anchor_mode(AnchorMode::CENTER);
    score_lable->set_pos_shade({-3,2});
    score_lable->set_size({ 200,32 });

    auto exit_ptr = std::make_unique<GameBtn>(Vector2(0, 0), "ui_goback_");
    btn_exit = exit_ptr.get();
    btn_exit->set_ID("btn_exit");
    btn_exit->set_anchor_mode(AnchorMode::TOPLEFT);
    btn_exit->set_anchor_referent_mode(AnchorMode::TOPLEFT);
    btn_exit->set_on_click([]() {
        // �˳���Ϸ���˵�����
        GameMgr::instance()->exchange_scene(SceneType::MENUE);
        }
    );

    auto player_ptr = std::make_unique<Player_xcz>();
    player = player_ptr.get();
    player->set_ID("player");
    player->set_on_hurt_fun([&]() { // ��������۵����ӵ���+1
        deduction_bul++;
        });
    player->set_on_hit_fun([&]() {  // ���й����1�֣�������Ч
        score++;
        Mix_PlayChannel(-1, ResMgr::instance()->find_audio("audio_hit"), 0);
        });

    background->add_children(std::move(bg_ptr));
    entity->add_children(std::move(player_ptr));
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
    deduction_bul = 0;
    score = 0;
    max_hp = 10;
    timer_bul_recover.restart();
    player->set_position({ 0,0 });
    player->set_hp(max_hp);
    player->add_bullet(2);
    enemy_num = 0;
    Scene::on_enter();
}

void XczGameScene::on_exit()
{
    if (_DE_BUG_)
    {
        std::cout << "XczGameScene::on_exit" << std::endl;
    }
    std::cout << "entity  num:" << entity->get_children().size() << std::endl;

    // ������Ⱦ�еĹ���
    auto& children = entity->get_children();
    for (auto it = children.begin(); it != children.end(); ) {
        const auto& child_ptr = *it;
        if (!child_ptr || child_ptr->get_ID().substr(0, 6) != "enemy_") {
            ++it;
            continue;
        }
        it = children.erase(it);
    }
    // ���������еĹ���
    std::queue<std::unique_ptr<GameObj>> empty_queue;
    std::swap(enemy_queue, empty_queue);

    Scene::on_exit();
}

void XczGameScene::on_update(float delta)
{
    if (_DE_BUG_)
    {
        //std::cout << "XczGameScene::on_update" << std::endl;
    }
    if (!player->get_alive()) return;

    Scene::on_update(delta);
    // ��ɫ�ƶ��ٶȣ�ÿ��20�����8%�����������200%
    int val = score / 20;
    val = val > 9 ? 9 : val;
    float n = pow(1.08f, val);
    player->set_speed(150.0f * n);
    // �ӵ�ÿ��30�ֶ�һ�ţ����8��,���һ��
    int bn = 2 + score / 30;
    bn = bn > 8 ? 8 : bn;
    bn -= deduction_bul;
    bn = bn < 1 ? 1 : bn;
    if (bn > player->get_bullet_num())
    {
        player->add_bullet(1);
    }
    else if (bn < player->get_bullet_num())
    {
        player->reduce_bullet(1);
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
        if (2 >= player->get_bullet_num())
        {
            is_enemy_produce_slow = true;
            timer_enemy_produce_slow.restart();
        }
    }
    timer_enemy_produce.set_wait_time(t);
    timer_enemy_produce.on_update(delta);

    // ��ȡ��ҵ�ǰλ��
    Vector2 p = player->get_anchor_position(AnchorMode::CENTER);

    // ��������
    auto& children = entity->get_children();
    for (auto it = children.begin(); it != children.end(); ) {
        auto& child_ptr = *it;
        if (!child_ptr || child_ptr->get_ID().substr(0, 6) != "enemy_")
        {
            ++it;
            continue;
        }

        Enemy_xcz* enemy = dynamic_cast<Enemy_xcz*>(child_ptr.get());
        if (!enemy)
        {
            ++it;
            continue;
        }

        if (enemy->get_alive()) // ������������������
        {
            enemy->set_player_pos(p);
            ++it;
        }
        else // �����������������
        {
            enemy->on_exit();
            uqp_obj removedObj = std::move(child_ptr);  // ת������Ȩ�� removedObj
            it = children.erase(it);

            // ���ɹ��Ƴ����Ͽ����ӹ�ϵ
            if (removedObj) {
                removedObj->set_parent(nullptr);
                removedObj->set_anchor_referent_obj(nullptr);
            }
            enemy_queue.push(std::move(removedObj));
        }
    }
    // ��ײ���
    CollisionMgr::instance()->processCollide();
    // ��󽫹��������ڶ������а���y����������
    // ����пսڵ㣬�����ں���
    entity->get_children().sort([](const uqp_obj& child_a, const uqp_obj& child_b) {
        if (!child_a) return false;
        if (!child_b) return true;
        return child_a->get_position().y < child_b->get_position().y;
        });

    // ���·���
    score_lable->set_lable_text("SCORE:" + std::to_string(score));
    // ����Ѫ��
    int hp = player->get_hp();
    hp_bar->set_percent_num(1.0f * hp / max_hp);

    if (!player->get_alive())
    {
        // �˳���Ϸ���˵�����
        GameMgr::instance()->exchange_scene(SceneType::MENUE);
    }
}

void XczGameScene::on_render()
{
    Scene::on_render();
    CollisionMgr::instance()->onDebugRender();
}

void XczGameScene::add_enemy()
{
    uqp_obj enemy;
    // ���������У���ֱ��ȡ��
    if (!enemy_queue.empty())
    {
        enemy = std::move(enemy_queue.front());
        enemy_queue.pop();
    }
    else
    {
        //û�о�newһ��
        auto enemy_n = std::make_unique<Enemy_xcz>();
        Enemy_xcz* en = enemy_n.get();

        std::string id = "enemy_" + std::to_string(enemy_num);
        en->set_ID(id);
        en->set_hp(1);
        en->set_on_hit_fun([&]() {
            Mix_PlayChannel(-1, ResMgr::instance()->find_audio("audio_hurt"), 0);
            });
        enemy_num++;
        enemy = std::move(enemy_n);
    }
    enemy->on_enter();
    entity->add_children(std::move(enemy));
}