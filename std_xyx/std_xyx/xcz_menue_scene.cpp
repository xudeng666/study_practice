#include "xcz_menue_scene.h"
#include "game_mgr.h"


XczMenueScene::XczMenueScene()
{
    auto btn_start_ptr = std::make_unique<GameBtn>(Vector2(0, 90), "ui_start_");
    btn_start = btn_start_ptr.get();
    btn_start->set_ID("btn_start");
    btn_start->set_anchor_mode(AnchorMode::CENTER);
    btn_start->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_start->set_on_click([]() {
        std::cout << "切换到幸存者游戏界面" << std::endl;
        GameMgr::instance()->exchange_scene(SceneType::GAME);
        }
    );

    auto btn_end_ptr = std::make_unique<GameBtn>(Vector2(0, 220), "ui_quit_");
    btn_end = btn_end_ptr.get();
    btn_end->set_ID("btn_end");
    btn_end->set_anchor_mode(AnchorMode::CENTER);
    btn_end->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_end->set_on_click([]() {
        GameMgr::instance()->exchange_game(GameType::START);
        }
    );

    auto bg_ptr = std::make_unique<GameImg>(Vector2(0, 0), "menu");
    bg = bg_ptr.get();
    bg->set_ID("bg");
    bg->set_anchor_mode(AnchorMode::CENTER);
    bg->set_anchor_referent_mode(AnchorMode::CENTER);

    background->add_children(std::move(bg_ptr));
    ui->add_children(std::move(btn_start_ptr));
    ui->add_children(std::move(btn_end_ptr));

    set_ID("XczMenueScene");
}

XczMenueScene::~XczMenueScene()
{
}

void XczMenueScene::on_enter()
{
    if (_DE_BUG_)
    {
        std::cout << "XczMenueScene::on_enter" << std::endl;
    }
    Scene::on_enter();
}

void XczMenueScene::on_exit()
{
    if (_DE_BUG_)
    {
        std::cout << "XczMenueScene::on_exit" << std::endl;
    }
    Scene::on_exit();
}