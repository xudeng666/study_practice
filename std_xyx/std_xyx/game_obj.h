#pragma once

#include "game_type.h"
#include "vector2.h"
#include "obj.h"
#include "tree_node.h"


/*游戏对象基类*/
class GameObj: public Obj,public TreeNode
{
public:
    GameObj() = default;
    GameObj(const std::string id);
    GameObj(const std::string id, const int num);
    virtual ~GameObj();

    DEFINE_TYPE_NAME(GameObj);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;

    /*设置ID*/
    virtual void set_ID(const std::string& str) override;
    virtual void set_ID(const std::string& str, const int num) override;
    /*获取ID*/
    virtual std::string get_ID() override;
    /*获取路径ID*/
    virtual std::string get_path_ID();
    /*id包含判定*/
    bool id_contains(const std::string& str);
    /*设置坐标*/
    void set_position(const Vector2& pos);
    /*获取坐标*/
    const Vector2& get_position() const;
    /*设置尺寸*/
    virtual void set_size(const SDL_Point& size);
    /*获取尺寸*/
    const SDL_Point& get_size() const;
    /*设置显示状态*/
    virtual void set_display(bool display);
    /*获取显示状态*/
    virtual const bool get_display() const;
    /*设置锚点*/
    void set_anchor_mode(const AnchorMode mode);
    /*获取锚点*/
    const AnchorMode get_anchor_mode() const;
    /*设置锚定对象锚点*/
    void set_anchor_referent_mode(const AnchorMode mode);
    /*获取锚定对象锚点*/
    const AnchorMode get_anchor_referent_mode() const;
    /*设置锚定对象*/
    void set_anchor_referent_node(TreeNode_WP node);
    /*获取锚定对象*/
    TreeNode_SP get_anchor_referent();
    /*设置旋转中心*/
    void set_center(const SDL_FPoint& pos);
    /*设置角度*/
    void set_rotation(double val);
    /*设置角度*/
    double get_rotation();
    /*设置点击区域状态*/
    void set_click_enabled(bool enable);
    /*获取点击区域状态*/
    bool get_click_enabled();
    /*获取对象区域*/
    SDL_FRect get_FRect();
    /*获取对象区域*/
    SDL_Rect get_Rect();
    /// <summary>
    /// 获取自身某锚点的全局坐标
    /// </summary>
    /// <param name="mode">计算锚点</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(const AnchorMode mode);
    /// <summary>
    /// 获取自身某锚点的全局坐标
    /// </summary>
    /// <remarks>
    /// 指自身坐标数据相对于某个节点的结果
    /// </remarks>
    /// <param name="node">指定节点</param>
    /// <param name="mode">计算锚点</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(TreeNode_WP node, const AnchorMode mode);
    /// <summary>
    /// 获取假子节点锚点的全局坐标
    /// </summary>
    /// <remarks>
    /// 假设有个字节的锚定本节点，获取该子节点的某个锚点全局坐标
    /// </remarks>
    /// <param name="aligned">被子节点锚定的锚点</param>
    /// <param name="reference">子节点锚定锚点</param>
    /// <param name="target">子节点计算锚点</param>
    /// <param name="pos">子节点坐标</param>
    /// <param name="p_size">子节点大小</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(const AnchorMode aligned, const AnchorMode reference, const AnchorMode target, Vector2 pos, SDL_Point p_size);
    /// <summary>
    /// 检测是否在屏幕内
    /// </summary>
    /// <param name="val">-1 0 1 横向，整体，纵向</param>
    /// <returns>true/false 在/不在</returns>
    bool check_in_screen(int val = 0);


    // 判断点是否在控件范围内
    bool contains_point(const SDL_Point* point);

protected:
    // 旋转角度
    double angle = 0.0;
    /*点击区域开关状态*/
    bool click_enabled = true;
    // 是否显示
    bool is_display = true;
	/*相对父节点坐标*/
    Vector2 position = { 0.0f, 0.0f };
    // 点击区域 暂时不单独列出
    // SDL_FRect click_rect;
	/*尺寸*/
    SDL_Point size = { 0, 0 };
    // 中心点
    SDL_FPoint center = { 0.0f, 0.0f };
	/*自身锚点*/
    AnchorMode anchor_mode = AnchorMode::TOPLEFT;
    /*锚定对象锚点*/
    AnchorMode anchor_referent_mode = AnchorMode::TOPLEFT;
    /*锚定对象节点*/
    TreeNode_WP anchor_referent_node;
};