#pragma once
#include "phf_obj.h"
#include "timer.h"

class DeliveryPeple :
    public PhfObj
{
public:
    DeliveryPeple() = default;
    virtual ~DeliveryPeple() = default;

    DeliveryPeple(const std::string& id) : PhfObj(id) {}
    DeliveryPeple(const std::string& id, int num) : PhfObj(id, num) {}

    DEFINE_TYPE_NAME(DeliveryPeple);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_update(float delta) override;
    virtual void on_cursor_up() override;

private:
    // 刷新外卖员
    void refresh();
    /// <summary>
    /// 放置餐品
    /// </summary>
    /// <param name="target">餐品类型</param>
    /// <returns></returns>
    bool check_and_place(Meal target);

private:
    // 餐品状态
    enum class Status
    {
        Waiting,   // 正在等待
        Completed  // 已经完成
    };

private:
    Timer timer_refresh;                // 外卖员刷新计时器
    float time_waited = 0;              // 已经等待的时间
    bool is_waiting = false;            // 当前是否正在等待
    bool is_meituan = false;            // 是否是美团外卖员
    std::vector<Meal> meal_list;        // 餐品列表
    std::vector<Status> status_list;    // 餐品状态列表
    int num_drink = 0, num_dish = 0;    // 饮料和菜品数量
    const float time_waited_limit = 60; // 等待时间上限

    TreeNode_WP hert_bar;               // 心情条
};

