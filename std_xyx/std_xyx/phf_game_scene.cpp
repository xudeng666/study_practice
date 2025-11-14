#include "phf_game_scene.h"
#include "cursor.h"

#include "game_bar.h"
#include "game_lable.h"
#include "game_btn.h"

#include "game_mgr.h"
#include "tree_mgr.h"


INIT_TYPE_NAME(PhfGameScene);

void PhfGameScene::on_init()
{
    // 添加背景图
    auto bg_obj = TreeNode::create_obj<GameImg>("bg");
    bg = bg_obj;
    bg_obj->set_position(Vector2(0, 0));
    bg_obj->set_res_name("background");
    bg_obj->set_anchor_mode(AnchorMode::CENTER);
    bg_obj->set_anchor_referent_mode(AnchorMode::CENTER);

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

    // 光标
    auto cursor_obj = TreeNode::create_obj<Cursor>("Cursor");
    cursor = cursor_obj;

    auto tree = TreeMgr::instance();
    tree->add_to_bg(bg_obj);
    tree->add_to_game(cursor_obj);
    tree->add_to_ui(bar_obj);
    tree->add_to_ui(lab_obj);
    tree->add_to_ui(exit_obj);
}

void PhfGameScene::on_enter()
{
    if (_DE_BUG_)
    {
        std::cout << "PhfGameScene::on_enter" << std::endl;
    }
    score_lable.lock()->get_obj_as<GameLable>()->set_font("IPix_30");
    score = 0;
    max_hp = 10;
    SDL_ShowCursor(SDL_DISABLE);
    Scene::on_enter();
}

void PhfGameScene::on_exit()
{
    if (_DE_BUG_)
    {
        std::cout << "PhfGameScene::on_exit" << std::endl;
    }

    SDL_ShowCursor(SDL_ENABLE);
}

void PhfGameScene::on_input(const SDL_Event& event)
{
    // 外卖员失望离开掉血
    // 外卖员满意离开加分
}

void PhfGameScene::on_update(float delta)
{
    if (_DE_BUG_)
    {
        //std::cout << "PhfGameScene::on_update" << std::endl;
    }

    // 更新分数
    score_lable.lock()->get_obj_as<GameLable>()->set_lable_text("SCORE:" + std::to_string(score));
    // 更新血量
    hp_bar.lock()->get_obj_as<GameBar>()->set_percent_num(1.0f * hp / max_hp);
}

void PhfGameScene::on_render()
{
    Scene::on_render();
}