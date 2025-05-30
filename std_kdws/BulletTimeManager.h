#pragma once
/// <summary>
/// 子弹时间管理
/// </summary>
class BulletTimeManager
{
public:
    /// <summary>
    /// 标注进入/退出子弹时间
    /// </summary>
    enum class Status
    {
        Entering,   //进入子弹时间
        Exiting     //退出子弹时间
    };

public:
    static BulletTimeManager* instance();
    /// <summary>
    /// 全屏暗化
    /// （除了玩家外，其他全部暗化）
    /// </summary>
    void post_process();
    void set_status(Status status);

    float on_update(float delta);

private:
    static BulletTimeManager* manager;

private:
    /**
    * @brief 	标记进入子弹时间进度
    * @details 	取值范围0.0~1.0  0表示完全没进去，1表示完全进去
    */
    float progress = 0;
    Status status = Status::Exiting;        // 标记当前子弹时间当前状态
    const float SPEED_PROGRESS = 2.0f;      // 进入/退出子弹时间的速度
    const float DST_DELTA_FACTOR = 0.35f;   // 子弹时间的帧更新时间的缩放值
    const float DST_COLOR_FACTOR = 0.35f;   // 子弹时间的画面色彩改变比例

private:
    BulletTimeManager();
    ~BulletTimeManager();

    /**
    * @brief 	    差值函数
    * @param start  起始值
    * @param end    结束值
    * @param t      进度0.0~1.0
    * @return       返回start过度到end时，进度到t时的值
    */
    float lerp(float start, float end, float t)
    {
        return (1 - t) * start + t * end;
    }
};

