#include "start_menu_scene.h"
#include "game_mgr.h"
#include "tree_mgr.h"

INIT_TYPE_NAME(StartMenuScene);

void StartMenuScene::on_init()
{
    auto btn_xcz_ptr = TreeNode::create_obj<GameBtn>("btn_xcz");
    btn_xcz_ptr->set_position(Vector2(-440, -80));
    btn_xcz_ptr->set_res_name("btn_xcz_");
    btn_xcz_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_xcz_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_xcz_ptr->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·ÐÒ´æÕß" << std::endl;
        GameMgr::instance()->exchange_game(GameType::XCZ);
        }
    );

    auto btn_kdws_ptr = TreeNode::create_obj<GameBtn>("btn_kdws");
    btn_kdws_ptr->set_position(Vector2(-220, -80));
    btn_kdws_ptr->set_res_name("btn_kdws_");
    btn_kdws_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_kdws_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_kdws_ptr->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·¿Õ¶´ÎäÊ¿" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::KDWS);
        }
    );

    auto btn_dld_ptr = TreeNode::create_obj<GameBtn>("btn_dld");
    btn_dld_ptr->set_position(Vector2(0, -80));
    btn_dld_ptr->set_res_name("btn_dld_");
    btn_dld_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_dld_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_dld_ptr->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·´óÂÒ¶·" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::DLD);
        }
    );

    auto btn_zmdj_ptr = TreeNode::create_obj<GameBtn>("btn_zmdj");
    btn_zmdj_ptr->set_position(Vector2(220, -80));
    btn_zmdj_ptr->set_res_name("btn_zmdj_");
    btn_zmdj_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_zmdj_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_zmdj_ptr->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·ÖÂÃü´ò¼¦" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::ZMDJ);
        }
    );

    auto btn_phf_ptr = TreeNode::create_obj<GameBtn>("btn_phf");
    btn_phf_ptr->set_position(Vector2(440, -80));
    btn_phf_ptr->set_res_name("btn_phf_");
    btn_phf_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_phf_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_phf_ptr->set_on_click([]() {
        std::cout << "ÇÐ»»ÓÎÏ·Æ´ºÃ·¹" << std::endl;
        //GameMgr::instance()->exchange_game(GameType::PHF);
        }
    );

    auto btn_exit_ptr = TreeNode::create_obj<GameBtn>("btn_exit");
    btn_exit_ptr->set_position(Vector2(0, 260));
    btn_exit_ptr->set_res_name("btn_tc_");
    btn_exit_ptr->set_anchor_mode(AnchorMode::CENTER);
    btn_exit_ptr->set_anchor_referent_mode(AnchorMode::CENTER);
    btn_exit_ptr->set_on_click([]() {
        //std::cout << "ÍË³öÓÎÏ·" << std::endl;
        GameMgr::instance()->set_is_run(false);
        }
    );

    auto bg_ptr = TreeNode::create_obj<GameImg>("bg");
    bg_ptr->set_position(Vector2(0, 0));
    bg_ptr->set_res_name("bg");
    bg_ptr->set_anchor_mode(AnchorMode::CENTER);
    bg_ptr->set_anchor_referent_mode(AnchorMode::CENTER);

    bg = bg_ptr;
    btn_xcz =  btn_xcz_ptr;
    btn_kdws = btn_kdws_ptr;
    btn_dld =  btn_dld_ptr;
    btn_zmdj = btn_zmdj_ptr;
    btn_phf =  btn_phf_ptr;
    btn_exit = btn_exit_ptr;

    TreeMgr::instance()->get_bg_node()->add_children(std::move(bg_ptr));
    TreeNode_SP ui = TreeMgr::instance()->get_ui_node();
    ui->add_children(std::move(btn_xcz_ptr));
    ui->add_children(std::move(btn_kdws_ptr));
    ui->add_children(std::move(btn_dld_ptr));
    ui->add_children(std::move(btn_zmdj_ptr));
    ui->add_children(std::move(btn_phf_ptr));
    ui->add_children(std::move(btn_exit_ptr));
}