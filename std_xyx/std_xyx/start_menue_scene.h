#pragma once

#include "scene.h"
#include "game_btn.h"

class StartMenueScene :
    public Scene
{
public:
    StartMenueScene() = default;
    ~StartMenueScene() = default;

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

