#include "xcz_menue_scene.h"
#include "res_mgr.h"
#include "game_mgr.h"


XczMenueScene::XczMenueScene()
{
    btn_start = new GameBtn({ 640,450 }, "ui_start_");
    btn_start->set_on_click([]() {
        GameMgr::instance()->get_current_game()->exchange_scene(SceneType::GAME);
        }
    );

    btn_end = new GameBtn({ 640,580 }, "ui_quit_");
    btn_end->set_on_click([]() {
        GameMgr::instance()->exchange_game(GameType::START);
        }
    );

    bg = new GameImg({ _WIN_W_ / 2, _WIN_H_ / 2 }, "menu");
}

XczMenueScene::~XczMenueScene()
{
    delete btn_start;
    delete btn_end;
}

void XczMenueScene::on_enter()
{
    bg->on_enter();
    btn_start->on_enter();
    btn_end->on_enter();
}
void XczMenueScene::on_update(float delta)
{
}
void XczMenueScene::on_input(const SDL_Event& event)
{
    btn_start->on_input(event);
    btn_end->on_input(event);
}
void XczMenueScene::on_render()
{
    bg->on_render();
    btn_start->on_render();
    btn_end->on_render();
}
void XczMenueScene::on_exit()
{

}