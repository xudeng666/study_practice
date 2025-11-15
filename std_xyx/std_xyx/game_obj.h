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
    /*id包含判定*/
    bool id_contains(const std::string& str);
    /*设置坐标*/
    void set_position(const Vector2& pos);
    /*设置坐标*/
    void set_position(const float x, const float y);
    /*获取坐标*/
    const Vector2& get_position() const;
    /*获取全局坐标
    * （获取锚定点的全局坐标）
    */
    const Vector2& get_rect_position();
    /*设置尺寸*/
    virtual void set_size(const SDL_Point& size);
    /*设置尺寸*/
    virtual void set_size(const int w, const int h);
    /*获取尺寸*/
    virtual const SDL_Point& get_size() const;
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
    /*设置点击区域状态*/
    void set_click_enabled(bool enable);
    /*获取点击区域状态*/
    bool get_click_enabled();
    /// <summary>
    /// 获取区域锚点坐标
    /// </summary>
    /// <param name="m">锚点类型</param>
    /// <returns>Vector2</returns>
    Vector2 get_rect_pos(const AnchorMode m);
    /*获取对象区域*/
    SDL_FRect get_FRect();
    /*获取对象区域*/
    SDL_Rect get_Rect();
    /// <summary>
    /// 获取两个锚点向量差值
    /// </summary>
    /// <param name="p">减数锚点类型</param>
    /// <param name="t">被减数锚点类型</param>
    /// <param name="t_size">设定计算尺寸</param>
    /// <returns>Vector t-p</returns>
    Vector2 get_anchor_difference(const AnchorMode p, const AnchorMode t, Vector2 t_size);
    /// <summary>
    /// 获取两个锚点向量差值
    /// </summary>
    /// <param name="p">减数锚点类型</param>
    /// <param name="t">被减数锚点类型</param>
    /// <returns>Vector t-p</returns>
    Vector2 get_anchor_difference(const AnchorMode p, const AnchorMode t);
    /// <summary>
    /// 获取旋转中心全局坐标
    /// </summary>
    /// <param name="pos">参照锚点坐标</param>
    /// <param name="mode">参照锚点类型</param>
    /// <returns></returns>
    Vector2 get_rotatio_center_position();
    /// <summary>
    /// 获取几何中心点全局坐标
    /// </summary>
    /// <returns></returns>
    Vector2 get_center_position();
    /// <summary>
    /// 获取自身某锚点的全局实际坐标
    /// </summary>
    /// <param name="mode">计算锚点</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(const AnchorMode mode);
    /// <summary>
    /// 检测是否在屏幕内
    /// </summary>
    /// <param name="val">-1 0 1 横向，整体，纵向</param>
    /// <returns>true/false 在/不在</returns>
    bool check_in_screen(int val = 0);
    // 判断点是否在控件范围内
    bool contains_point(const SDL_Point* point);
    /*设置旋转中心坐标*/
    void set_center(const Vector2& pos);
    /*设置旋转中心坐标*/
    void set_center(const float x, const float y);
    /*获取旋转中心坐标*/
    Vector2 get_center();
    /*获取旋转中心左上角坐标*/
    SDL_FPoint get_center_point();
    /*设置旋转中心锚点*/
    void set_angle_anchor_mode(const AnchorMode mode);
    /*获取旋转中心锚点*/
    AnchorMode get_angle_anchor_mode();
    /*设置转动开启状态*/
    void set_enable_angle(bool tga);
    /*获取转动开启状态*/
    bool get_enable_angle();
    /*获取转动开启状态（全局）*/
    bool get_extend_enable_angle();
    /*设置角度*/
    void set_rotation(double val);
    /*获取弧度*/
    double get_rotation();
    /*获取角度*/
    double get_angle();
    /*获取路径ID*/
    std::string get_path_ID();
    /*设置路径ID*/
    void set_path_ID();

protected:
    bool click_enabled = true;  // 点击区域开关状态（默认开启）
    // 是否显示
    bool is_display = true;
	/*相对父节点坐标*/
    Vector2 position = { 0.0f, 0.0f };
    // 点击区域 暂时不单独列出
    // SDL_FRect click_rect;
	/*尺寸*/
    SDL_Point size = { 100, 100 };
	/*自身锚点*/
    AnchorMode anchor_mode = AnchorMode::TOPLEFT;
    /*锚定对象锚点*/
    AnchorMode anchor_referent_mode = AnchorMode::TOPLEFT;
    /*锚定对象节点*/
    TreeNode_WP anchor_referent_node;

    // 旋转角度
    double angle = 0.0;
    /*开启角度计算(默认false)*/
    bool enable_angle = false;
    // 旋转中心坐标点
    Vector2 center = { 0.0f, 0.0f };
    // 旋转锚点(默认中心点)
    AnchorMode angle_anchor_mode = AnchorMode::CENTER;
    
    std::string path_id;
};