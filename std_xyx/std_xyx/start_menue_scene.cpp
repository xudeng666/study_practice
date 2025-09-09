#include "start_menue_scene.h"
#include "game_mgr.h"


StartMenueScene::StartMenueScene()
{
    auto btn_xcz_ptr = std::make_unique<GameBtn>(Vector2(-440, -80), "btn_xcz_");
    btn_xcz = btn_xcz_ptr.get();
    btn_xcz->set_ID("btn_xcz");
    btn_xcz->set_anchor_mode(AnchorMode::CENTER);
    btn_xcz->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_xcz->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·ÐÒ´æÕß" << std::endl;
        GameMgr::instance()->exchange_game(GameType::XCZ);
        }
    );

    auto btn_kdws_ptr = std::make_unique<GameBtn>(Vector2(-220, -80), "btn_kdws_");
    btn_kdws = btn_kdws_ptr.get();
    btn_kdws->set_ID("btn_kdws");
    btn_kdws->set_anchor_mode(AnchorMode::CENTER);
    btn_kdws->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_kdws->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·¿Õ¶´ÎäÊ¿" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::KDWS);
        }
    );

    auto btn_dld_ptr = std::make_unique<GameBtn>(Vector2(0, -80), "btn_dld_");
    btn_dld = btn_dld_ptr.get();
    btn_dld->set_ID("btn_dld");
    btn_dld->set_anchor_mode(AnchorMode::CENTER);
    btn_dld->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_dld->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·´óÂÒ¶·" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::DLD);
        }
    );

    auto btn_zmdj_ptr = std::make_unique<GameBtn>(Vector2(220, -80), "btn_zmdj_");
    btn_zmdj = btn_zmdj_ptr.get();
    btn_zmdj->set_ID("btn_zmdj");
    btn_zmdj->set_anchor_mode(AnchorMode::CENTER);
    btn_zmdj->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_zmdj->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·ÖÂÃü´ò¼¦" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::ZMDJ);
        }
    );

    auto btn_phf_ptr = std::make_unique<GameBtn>(Vector2(440, -80), "btn_phf_");
    btn_phf = btn_phf_ptr.get();
    btn_phf->set_ID("btn_phf");
    btn_phf->set_anchor_mode(AnchorMode::CENTER);
    btn_phf->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_phf->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·Æ´ºÃ·¹" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::PHF);
        }
    );

    auto btn_exit_ptr = std::make_unique<GameBtn>(Vector2(0, 260), "btn_tc_");
    btn_exit = btn_exit_ptr.get();
    btn_exit->set_ID("btn_exit");
    btn_exit->set_anchor_mode(AnchorMode::CENTER);
    btn_exit->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_exit->set_on_click([]() {
        //std::cout << "ÍË³öÓÎÏ·" << std::endl;
        GameMgr::instance()->set_is_run(false);
        }
    );

    auto bg_ptr = std::make_unique<GameImg>(Vector2(0, 0), "bg");
    bg = bg_ptr.get();
    bg->set_ID("bg");
    bg->set_anchor_mode(AnchorMode::CENTER);
    bg->set_anchor_referent_mode(AnchorMode::CENTER);

    background->add_children(std::move(bg_ptr));
    ui->add_children(std::move(btn_xcz_ptr));
    ui->add_children(std::move(btn_kdws_ptr));
    ui->add_children(std::move(btn_dld_ptr));
    ui->add_children(std::move(btn_zmdj_ptr));
    ui->add_children(std::move(btn_phf_ptr));
    ui->add_children(std::move(btn_exit_ptr));

    set_ID("StartMenueScene");
}

StartMenueScene::~StartMenueScene()
{
}

void StartMenueScene::on_enter()
{
    Scene::on_enter();
}
void StartMenueScene::on_exit()
{
    Scene::on_exit();
}