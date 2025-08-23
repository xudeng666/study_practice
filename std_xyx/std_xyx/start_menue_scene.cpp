#include "start_menue_scene.h"
#include "res_mgr.h"
#include "game_mgr.h"


StartMenueScene::StartMenueScene()
{
    btn_xcz = new GameBtn({ 200,280 }, "btn_xcz_");
    btn_xcz->set_anchor_mode(AnchorMode::CENTER);
    btn_xcz->set_parent_anchor_mode(AnchorMode::CENTER);
    btn_xcz->set_parent(ui);
    btn_xcz->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·ÐÒ´æÕß" << std::endl;
        GameMgr::instance()->exchange_game(GameType::XCZ);
        }
    );

    btn_kdws = new GameBtn({ 420,280 }, "btn_kdws_");
    btn_kdws->set_anchor_mode(AnchorMode::CENTER);
    btn_kdws->set_parent_anchor_mode(AnchorMode::CENTER);
    btn_kdws->set_parent(ui);
    btn_kdws->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·¿Õ¶´ÎäÊ¿" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::KDWS);
        }
    );
    btn_dld = new GameBtn({ 640,280 }, "btn_dld_");
    btn_dld->set_anchor_mode(AnchorMode::CENTER);
    btn_dld->set_parent_anchor_mode(AnchorMode::CENTER);
    btn_dld->set_parent(ui);
    btn_dld->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·´óÂÒ¶·" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::DLD);
        }
    );
    btn_zmdj = new GameBtn({ 860,280 }, "btn_zmdj_");
    btn_zmdj->set_anchor_mode(AnchorMode::CENTER);
    btn_zmdj->set_parent_anchor_mode(AnchorMode::CENTER);
    btn_zmdj->set_parent(ui);
    btn_zmdj->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·ÖÂÃü´ò¼¦" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::ZMDJ);
        }
    );
    btn_phf = new GameBtn({ 1080,280 }, "btn_phf_");
    btn_phf->set_anchor_mode(AnchorMode::CENTER);
    btn_phf->set_parent_anchor_mode(AnchorMode::CENTER);
    btn_phf->set_parent(ui);
    btn_phf->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·Æ´ºÃ·¹" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::PHF);
        }
    );
    btn_exit = new GameBtn({ 640,660 }, "btn_tc_");
    btn_exit->set_anchor_mode(AnchorMode::CENTER);
    btn_exit->set_parent_anchor_mode(AnchorMode::CENTER);
    btn_exit->set_parent(ui);
    btn_exit->set_on_click([]() {
        //std::cout << "ÍË³öÓÎÏ·" << std::endl;
        GameMgr::instance()->set_is_run(false);
        }
    );

    bg = new GameImg({_WIN_W_/2, _WIN_H_/2}, "bg");
    bg->set_anchor_mode(AnchorMode::CENTER);
    bg->set_parent_anchor_mode(AnchorMode::CENTER);
    bg->set_parent(background);
}

StartMenueScene::~StartMenueScene()
{
}

void StartMenueScene::on_enter()
{
   /* bg->on_enter();
    btn_xcz->on_enter();
    btn_kdws->on_enter();
    btn_dld->on_enter();
    btn_zmdj->on_enter();
    btn_phf->on_enter();
    btn_exit->on_enter();*/
}
void StartMenueScene::on_update(float delta)
{
}
void StartMenueScene::on_input(const SDL_Event& event)
{
   /* btn_xcz->on_input(event);
    btn_kdws->on_input(event);
    btn_dld->on_input(event);
    btn_zmdj->on_input(event);
    btn_phf->on_input(event);
    btn_exit->on_input(event);*/
}
void StartMenueScene::on_render()
{
    /*bg->on_render();
    btn_xcz->on_render();
    btn_kdws->on_render();
    btn_dld->on_render();
    btn_zmdj->on_render();
    btn_phf->on_render();
    btn_exit->on_render();*/
}
void StartMenueScene::on_exit()
{
}