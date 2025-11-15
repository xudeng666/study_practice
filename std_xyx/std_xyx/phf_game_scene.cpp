#include "phf_game_scene.h"
#include "cursor.h"
#include "phf_bundle.h"
#include "takeout_box.h"

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

    // 可乐
    auto cola_obj = TreeNode::create_obj<ColaBundle>("cola_bundle");
    cola_obj->set_position(300, 390);
    cola_bundle = cola_obj;
    // 雪碧
    auto sprite_obj = TreeNode::create_obj<SpriteBundle>("sprite_bundle");
    sprite_obj->set_position(425, 390);
    sprite_bundle = sprite_obj;
    // 餐具
    auto tb_obj = TreeNode::create_obj<TbBundle>("tb_bundle");
    tb_obj->set_position(550, 418);
    tb_bundle = tb_obj;
    // 餐品1
    auto mb_box_obj = TreeNode::create_obj<MbBoxBundle>("mb_box_bundle");
    mb_box_obj->set_position(225, 520);
    mb_box_bundle = mb_box_obj;
    // 餐品2
    auto bc_box_obj = TreeNode::create_obj<BcBoxBundle>("bc_box_bundle");
    bc_box_obj->set_position(395, 520);
    bc_box_bundle = bc_box_obj;
    // 餐品3
    auto rcp_box_obj = TreeNode::create_obj<RcpBoxBundle>("rcp_box_bundle");
    rcp_box_obj->set_position(565, 520);
    rcp_box_bundle = rcp_box_obj;
    // 餐位1
    auto tb_obj1 = TreeNode::create_obj<TakeoutBox>("takeout_box_1");
    tb_obj1->set_position(876, 562);
    takeout_box_1 = tb_obj1;
    // 餐位2
    auto tb_obj2 = TreeNode::create_obj<TakeoutBox>("takeout_box_2");
    tb_obj2->set_position(982, 562);
    takeout_box_2 = tb_obj2;
    // 餐位3
    auto tb_obj3 = TreeNode::create_obj<TakeoutBox>("takeout_box_3");
    tb_obj3->set_position(1088, 562);
    takeout_box_3 = tb_obj3;
    // 餐位4
    auto tb_obj4 = TreeNode::create_obj<TakeoutBox>("takeout_box_4");
    tb_obj4->set_position(1194, 562);
    takeout_box_4 = tb_obj4;

    // 光标
    auto cursor_obj = TreeNode::create_obj<Cursor>("Cursor");
    cursor = cursor_obj;

    auto tree = TreeMgr::instance();
    tree->add_to_bg(bg_obj);
    tree->add_to_game(cola_obj);
    tree->add_to_game(sprite_obj);
    tree->add_to_game(tb_obj);
    tree->add_to_game(mb_box_obj);
    tree->add_to_game(bc_box_obj);
    tree->add_to_game(rcp_box_obj);
    tree->add_to_game(tb_obj1);
    tree->add_to_game(tb_obj2);
    tree->add_to_game(tb_obj3);
    tree->add_to_game(tb_obj4);
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