#pragma once
#include "scene.h"
#include "game_btn.h"

class XczMenuScene :
    public Scene
{
public:
    XczMenuScene() = default;
    virtual ~XczMenuScene() = default;

    XczMenuScene(const std::string& id) : Scene(id) {}
    XczMenuScene(const std::string& id, int num) : Scene(id, num) {}

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;

private:
    TreeNode_WP bg;
    TreeNode_WP btn_start;
    TreeNode_WP btn_end;
};

