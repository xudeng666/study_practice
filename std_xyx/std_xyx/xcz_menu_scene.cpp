#include "xcz_menu_scene.h"
#include "game_mgr.h"
#include "tree_mgr.h"


void XczMenuScene::on_init()
{
    auto btn_s = TreeNode::create_obj<GameBtn>("btn_start");
    btn_start = btn_s;
    btn_s->set_position(Vector2(0, 90));
    btn_s->set_res_name("ui_start_");
    btn_s->set_anchor_mode(AnchorMode::CENTER);
    btn_s->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_s->set_on_click([]() {
        std::cout << "切换到幸存者游戏界面" << std::endl;
        GameMgr::instance()->exchange_scene(SceneType::GAME);
        }
    );

    auto btn_e = TreeNode::create_obj<GameBtn>("btn_end");
    btn_end = btn_e;
    btn_e->set_position(Vector2(0, 220));
    btn_e->set_res_name("ui_quit_");
    btn_e->set_anchor_mode(AnchorMode::CENTER);
    btn_e->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_e->set_on_click([]() {
        GameMgr::instance()->exchange_game(GameType::START);
        }
    );

    auto bg_obj = TreeNode::create_obj<GameImg>("bg");
    bg = bg_obj;
    bg_obj->set_position(Vector2(0, 0));
    bg_obj->set_res_name("menu");
    bg_obj->set_anchor_mode(AnchorMode::CENTER);
    bg_obj->set_anchor_referent_mode(AnchorMode::CENTER);

    TreeMgr::instance()->get_bg_node()->add_children(std::move(bg_obj));
    TreeNode_SP ui = TreeMgr::instance()->get_ui_node();
    ui->add_children(std::move(btn_s));
    ui->add_children(std::move(btn_e));

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