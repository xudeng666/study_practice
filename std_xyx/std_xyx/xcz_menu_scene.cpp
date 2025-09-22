#include "xcz_menu_scene.h"
#include "game_mgr.h"
#include "tree_mgr.h"


void XczMenuScene::on_init()
{
    auto btn_start_ptr = TreeNode::create(std::make_unique<GameBtn>("btn_start"));
    btn_start = btn_start_ptr;
    auto btn_s = btn_start_ptr->get_obj_as<GameBtn>();
    btn_s->set_position(Vector2(0, 90));
    btn_s->set_res_name("ui_start_");
    btn_s->set_anchor_mode(AnchorMode::CENTER);
    btn_s->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_s->set_on_click([]() {
        std::cout << "切换到幸存者游戏界面" << std::endl;
        GameMgr::instance()->exchange_scene(SceneType::GAME);
        }
    );

    auto btn_end_ptr = TreeNode::create(std::make_unique<GameBtn>("btn_end"));
    btn_end = btn_end_ptr;
    auto btn_e = btn_end_ptr->get_obj_as<GameBtn>();
    btn_e->set_position(Vector2(0, 220));
    btn_e->set_res_name("ui_quit_");
    btn_e->set_anchor_mode(AnchorMode::CENTER);
    btn_e->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_e->set_on_click([]() {
        GameMgr::instance()->exchange_game(GameType::START);
        }
    );

    auto bg_ptr = TreeNode::create(std::make_unique<GameImg>("bg"));
    bg = bg_ptr;
    auto bg_obj = bg_ptr->get_obj_as<GameImg>();
    bg_obj->set_position(Vector2(0, 0));
    bg_obj->set_res_name("menu");
    bg_obj->set_anchor_mode(AnchorMode::CENTER);
    bg_obj->set_anchor_referent_mode(AnchorMode::CENTER);

    TreeMgr::instance()->get_bg_node()->add_children(std::move(bg_ptr));
    TreeNode_SP ui = TreeMgr::instance()->get_ui_node();
    ui->add_children(std::move(btn_start_ptr));
    ui->add_children(std::move(btn_end_ptr));

    set_ID("XczMenuScene");
}

void XczMenuScene::on_enter()
{
    if (_DE_BUG_)
    {
        std::cout << "XczMenuScene::on_enter" << std::endl;
    }
    Scene::on_enter();
}

void XczMenuScene::on_exit()
{
    if (_DE_BUG_)
    {
        std::cout << "XczMenuScene::on_exit" << std::endl;
    }
    Scene::on_exit();
}