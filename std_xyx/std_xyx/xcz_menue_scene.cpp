#include "xcz_menue_scene.h"
#include "res_mgr.h"
#include "game_mgr.h"


XczMenueScene::XczMenueScene()
{
    btn_start = new GameBtn({ 640,450 }, "ui_start_");
    btn_start->set_ID("btn_start");
    btn_start->set_anchor_mode(AnchorMode::CENTER);
    btn_start->set_parent_anchor_mode(AnchorMode::CENTER);
    btn_start->set_parent(ui);
    btn_start->set_on_click([]() {
        std::cout << "切换到幸存者游戏界面" << std::endl;
        //GameMgr::instance()->get_current_game()->exchange_scene(SceneType::GAME);
        }
    );

    btn_end = new GameBtn({ 640,580 }, "ui_quit_");
    btn_end->set_ID("btn_end");
    btn_end->set_anchor_mode(AnchorMode::CENTER);
    btn_end->set_parent_anchor_mode(AnchorMode::CENTER);
    btn_end->set_parent(ui);
    btn_end->set_on_click([]() {
        GameMgr::instance()->exchange_game(GameType::START);
        }
    );

    bg = new GameImg({ _WIN_W_ / 2, _WIN_H_ / 2 }, "menu");
    bg->set_ID("bg");
    bg->set_anchor_mode(AnchorMode::CENTER);
    bg->set_parent_anchor_mode(AnchorMode::CENTER);
    bg->set_parent(background);

    set_ID("XczMenueScene");
}

XczMenueScene::~XczMenueScene()
{
}

void XczMenueScene::on_enter()
{
    Scene::on_enter();
}

void XczMenueScene::on_exit()
{
    Scene::on_exit();
}