#pragma once

#include "scene.h"
#include "game_btn.h"

class StartMenuScene :
    public Scene
{
public:
    StartMenuScene() = default;
    ~StartMenuScene() = default;

    StartMenuScene(const std::string& id) : Scene(id) {}
    StartMenuScene(const std::string& id, int num) : Scene(id, num) {}

    DEFINE_TYPE_NAME(StartMenuScene);

    virtual void on_init() override;

private:
    TreeNode_WP bg;
    TreeNode_WP btn_xcz;
    TreeNode_WP btn_kdws;
    TreeNode_WP btn_dld;
    TreeNode_WP btn_zmdj;
    TreeNode_WP btn_phf;
    TreeNode_WP btn_exit;
};