#include "start_menu_scene.h"
#include "game_mgr.h"
#include "tree_mgr.h"

void StartMenuScene::on_init()
{
    auto btn_xcz_ptr = std::make_unique<GameBtn>("btn_xcz");
    btn_xcz_ptr->set_position(Vector2(-440, -80));
    btn_xcz_ptr->set_res_name("btn_xcz_");
    btn_xcz_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_xcz_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_xcz_ptr->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·ÐÒ´æÕß" << std::endl;
        GameMgr::instance()->exchange_game(GameType::XCZ);
        }
    );

    auto btn_kdws_ptr = std::make_unique<GameBtn>("btn_kdws");
    btn_kdws_ptr->set_position(Vector2(-220, -80));
    btn_kdws_ptr->set_res_name("btn_kdws_");
    btn_kdws_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_kdws_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_kdws_ptr->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·¿Õ¶´ÎäÊ¿" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::KDWS);
        }
    );

    auto btn_dld_ptr = std::make_unique<GameBtn>("btn_dld");
    btn_dld_ptr->set_position(Vector2(0, -80));
    btn_dld_ptr->set_res_name("btn_dld_");
    btn_dld_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_dld_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_dld_ptr->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·´óÂÒ¶·" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::DLD);
        }
    );

    auto btn_zmdj_ptr = std::make_unique<GameBtn>("btn_zmdj");
    btn_zmdj_ptr->set_position(Vector2(220, -80));
    btn_zmdj_ptr->set_res_name("btn_zmdj_");
    btn_zmdj_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_zmdj_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_zmdj_ptr->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·ÖÂÃü´ò¼¦" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::ZMDJ);
        }
    );

    auto btn_phf_ptr = std::make_unique<GameBtn>("btn_phf");
    btn_phf_ptr->set_position(Vector2(440, -80));
    btn_phf_ptr->set_res_name("btn_phf_");
    btn_phf_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_phf_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_phf_ptr->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·Æ´ºÃ·¹" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::PHF);
        }
    );

    auto btn_exit_ptr = std::make_unique<GameBtn>("btn_exit");
    btn_exit_ptr->set_position(Vector2(0, 260));
    btn_exit_ptr->set_res_name("btn_tc_");
    btn_exit_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_exit_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_exit_ptr->set_on_click([]() {
        //std::cout << "ÍË³öÓÎÏ·" << std::endl;
        GameMgr::instance()->set_is_run(false);
        }
    );

    auto bg_ptr = std::make_unique<GameBtn>("bg");
    bg_ptr->set_position(Vector2(0, 0));
    bg_ptr->set_res_name("bg");
    bg_ptr->set_anchor_mode(AnchorMode::CENTER);
    bg_ptr->set_anchor_referent_mode(AnchorMode::CENTER);

    auto bg_p   = TreeNode::create(std::move(bg_ptr));
    auto xcz_p  = TreeNode::create(std::move(btn_xcz_ptr));
    auto kdws_p = TreeNode::create(std::move(btn_kdws_ptr));
    auto dld_p  = TreeNode::create(std::move(btn_dld_ptr));
    auto zmdj_p = TreeNode::create(std::move(btn_zmdj_ptr));
    auto exit_p = TreeNode::create(std::move(btn_exit_ptr));

    bg = bg_p;
    btn_xcz = bg_p;
    btn_kdws = xcz_p;
    btn_dld = kdws_p;
    btn_zmdj = dld_p;
    btn_phf = zmdj_p;
    btn_exit = exit_p;

    TreeMgr::instance()->get_bg_node()->add_children(std::move(bg_p));
    TreeNode_SP ui = TreeMgr::instance()->get_ui_node();
    ui->add_children(std::move(bg_p  ));
    ui->add_children(std::move(xcz_p ));
    ui->add_children(std::move(kdws_p));
    ui->add_children(std::move(dld_p ));
    ui->add_children(std::move(zmdj_p));
    ui->add_children(std::move(exit_p));
}