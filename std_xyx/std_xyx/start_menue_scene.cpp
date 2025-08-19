#include "start_menue_scene.h"
#include "res_mgr.h"
#include "game_mgr.h"


StartMenueScene::StartMenueScene()
{
    btn_xcz = new GameBtn({ 200,280 }, "btn_xcz_");
    btn_xcz->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·ÐÒ´æÕß" << std::endl;
        GameMgr::instance()->exchange_game(GameType::XCZ);
        }
    );

    btn_kdws = new GameBtn({ 420,280 }, "btn_kdws_");
    btn_kdws->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·¿Õ¶´ÎäÊ¿" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::KDWS);
        }
    );
    btn_dld = new GameBtn({ 640,280 }, "btn_dld_");
    btn_dld->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·´óÂÒ¶·" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::DLD);
        }
    );
    btn_zmdj = new GameBtn({ 860,280 }, "btn_zmdj_");
    btn_zmdj->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·ÖÂÃü´ò¼¦" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::ZMDJ);
        }
    );
    btn_phf = new GameBtn({ 1080,280 }, "btn_phf_");
    btn_phf->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·Æ´ºÃ·¹" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::PHF);
        }
    );
    btn_exit = new GameBtn({ 640,660 }, "btn_tc_");
    btn_exit->set_on_click([]() {
        //std::cout << "ÍË³öÓÎÏ·" << std::endl;
        GameMgr::instance()->set_is_run(false);
        }
    );
}

StartMenueScene::~StartMenueScene()
{
    delete btn_xcz;
    delete btn_kdws;
    delete btn_dld;
    delete btn_zmdj;
    delete btn_phf;
    delete btn_exit;
}

void StartMenueScene::on_enter()
{
    bg = ResMgr::instance()->find_texture("bg");
}
void StartMenueScene::on_update(float delta)
{
    btn_xcz->on_update(delta);
    btn_kdws->on_update(delta);
    btn_dld->on_update(delta);
    btn_zmdj->on_update(delta);
    btn_phf->on_update(delta);
    btn_exit->on_update(delta);
}
void StartMenueScene::on_input(const SDL_Event& event)
{
    btn_xcz->on_input(event);
    btn_kdws->on_input(event);
    btn_dld->on_input(event);
    btn_zmdj->on_input(event);
    btn_phf->on_input(event);
    btn_exit->on_input(event);
}
void StartMenueScene::on_render()
{
    int w_bg, h_bg;
    SDL_QueryTexture(bg, nullptr, nullptr, &w_bg, &h_bg);
    const SDL_FRect rect_bg = { (float)(_WIN_W_ - w_bg) / 2,(float)(_WIN_H_ - h_bg) / 2,(float)w_bg,(float)h_bg };
    GameMgr::instance()->get_camera()->render_texture(bg, nullptr, &rect_bg, 0, nullptr);
    btn_xcz->on_render();
    btn_kdws->on_render();
    btn_dld->on_render();
    btn_zmdj->on_render();
    btn_phf->on_render();
    btn_exit->on_render();
}
void StartMenueScene::on_exit()
{

}