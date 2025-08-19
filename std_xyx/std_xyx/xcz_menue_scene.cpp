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
}

XczMenueScene::~XczMenueScene()
{
    delete btn_start;
    delete btn_end;
}

void XczMenueScene::on_enter()
{
    bg = ResMgr::instance()->find_texture("menu");
}
void XczMenueScene::on_update(float delta)
{
    btn_start->on_update(delta);
    btn_end->on_update(delta);
}
void XczMenueScene::on_input(const SDL_Event& event)
{
    btn_start->on_input(event);
    btn_end->on_input(event);
}
void XczMenueScene::on_render()
{
    int w_bg, h_bg;
    SDL_QueryTexture(bg, nullptr, nullptr, &w_bg, &h_bg);
    const SDL_FRect rect_bg = { (float)(_WIN_W_ - w_bg) / 2,(float)(_WIN_H_ - h_bg) / 2,(float)w_bg,(float)h_bg };
    GameMgr::instance()->get_camera()->render_texture(bg, nullptr, &rect_bg, 0, nullptr);

    btn_start->on_render();
    btn_end->on_render();
}
void XczMenueScene::on_exit()
{

}