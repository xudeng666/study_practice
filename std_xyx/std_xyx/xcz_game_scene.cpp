#include "xcz_game_scene.h"

XczGameScene::XczGameScene()
{
    bg = new GameImg({ 0,0 }, "background");
    bg->set_ID("bg");
    bg->set_anchor_mode(AnchorMode::CENTER);
    bg->set_parent_anchor_mode(AnchorMode::CENTER);

    hp_bar = new GameBar({ 10,10 });
    hp_bar->set_ID("hp_bar");
    hp_bar->set_anchor_mode(AnchorMode::TOPLEFT);
    hp_bar->set_parent_anchor_mode(AnchorMode::TOPLEFT);
    hp_bar->get_img_pro()->set_anchor_mode(AnchorMode::LEFTCENTER);
    hp_bar->get_img_pro()->set_parent_anchor_mode(AnchorMode::LEFTCENTER);
    hp_bar->get_img_pro()->set_res_name("ui_heart");
    hp_bar->get_img_pro()->set_texture_map_type(TextureMapType::TILE);
    pre_order_traversal(hp_bar, [&](GameObj* obj) {
        obj->set_size({320,32});
        });
    hp_bar->set_max_value(320);

    background->add_children(bg);
    ui->add_children(hp_bar);

	set_ID("XczGameScene");
}

XczGameScene::~XczGameScene()
{
}

void XczGameScene::on_enter()
{
    hp_bar->set_percent_num(1.0f);
}
void XczGameScene::on_exit()
{

}