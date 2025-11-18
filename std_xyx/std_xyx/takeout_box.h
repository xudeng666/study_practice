#pragma once
#include "phf_obj.h"
#include "meal.h"

class TakeoutBox :
    public PhfObj
{
public:
    TakeoutBox() = default;
    virtual ~TakeoutBox() = default;

    TakeoutBox(const std::string& id) : PhfObj(id) {}
    TakeoutBox(const std::string& id, int num) : PhfObj(id, num) {}

    DEFINE_TYPE_NAME(TakeoutBox);

    virtual void on_init() override;
    virtual void on_update(float delta) override;
    virtual void on_cursor_down() override;
    virtual void on_cursor_up() override;

    std::string get_res_name();

protected:
    bool can_place(Meal m);         // 是否可以放置
};