#pragma once
#include "phf_obj.h"
#include "timer.h"

class MicrowaveOven :
    public PhfObj
{
public:
    MicrowaveOven() = default;
    virtual ~MicrowaveOven() = default;

    MicrowaveOven(const std::string& id) : PhfObj(id) {}
    MicrowaveOven(const std::string& id, int num) : PhfObj(id, num) {}

    DEFINE_TYPE_NAME(MicrowaveOven);

    virtual void on_init() override;
    virtual void on_update(float delta) override;
    virtual void on_cursor_up() override;
    virtual void on_cursor_down() override;
private:
    bool can_place(Meal target);    // 能否放置
    void change_render();           // 工作状态切换

private:
    Timer timer;                  // 工作定时器
    bool is_working = false;      // 当前是否正在工作
    TreeNode_WP food;
};

