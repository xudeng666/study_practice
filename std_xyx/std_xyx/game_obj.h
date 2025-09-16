#pragma once

//#include <forward_list>
#include <functional>

#include "game_type.h"
#include "vector2.h"
#include "obj.h"

template <typename T>
class Base {
public:
    // 每个派生类会有一个唯一的TypeID
    static const size_t TypeID;
    virtual size_t get_type_id() const = 0;
};

template <typename T> const size_t Base<T>::TypeID = typeid<size_t>.hash_code();

//class GameObj;
//
//typedef std::unique_ptr<GameObj> uqp_obj;

/*游戏对象基类*/
class GameObj: public Obj
{
public:
    GameObj();
    //GameObj(const Vector2 pos);
    virtual ~GameObj();

    DEFINE_TYPE_NAME(GameObj);

    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;

    template <typename T> bool is_type()const
    {
        return typeid(*this) == typeid(T);
    }
    /*
    virtual void on_cursor_down() {}
    virtual void on_cursor_up() {}
    virtual void on_cursor_hover(bool is_hover) {}*/
    /*设置ID*/
    void set_ID(const std::string str);
    void set_ID(const std::string str, const int num);
    /*获取ID*/
    std::string get_ID();
    /*获取路径ID*/
    std::string get_path_ID();
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
    void set_anchor_referent_obj(GameObj* obj);
    /*获取锚定对象*/
    const GameObj* get_anchor_referent_obj();
    /*设置旋转中心*/
    void set_center(const SDL_FPoint& pos);
    /*设置角度*/
    void set_rotation(double val);
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
    /// <param name="mode">目标锚点</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(const AnchorMode mode);
    /// <summary>
    /// 获取自身某锚点的全局坐标
    /// </summary>
    /// <remarks>
    /// 计算本节点和指定锚定对象的锚点全局坐标（不会修改实际锚定对象）
    /// </remarks>
    /// <param name="obj">锚定对象</param>
    /// <param name="mode">目标锚点</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(GameObj* obj, const AnchorMode mode);
    /// <summary>
    /// 获取假子节点锚点的全局坐标
    /// </summary>
    /// <remarks>
    /// 某个对象以本节点为锚点，计算该对象的某个锚点全局坐标
    /// </remarks>
    /// <param name="aligned">自身对齐锚点</param>
    /// <param name="reference">目标参照锚点</param>
    /// <param name="target">目标计算锚点</param>
    /// <param name="pos">目标相对坐标</param>
    /// <param name="p_size">目标尺寸</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(const AnchorMode aligned, const AnchorMode reference, const AnchorMode target, Vector2 pos, SDL_Point p_size);
    /// <summary>
    /// 检测是否在屏幕内
    /// </summary>
    /// <param name="val">-1 0 1 横向，整体，纵向</param>
    /// <returns>true/false 在/不在</returns>
    bool check_in_screen(int val = 0);

protected:
    std::string ID;
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

//protected:
//    // 父节点
//    GameObj* parent = nullptr;
//    // 锚定对象
//    GameObj* anchor_referent_obj = nullptr;
//    // 子节点
//    std::list<uqp_obj> children;
//
//public:
//    /*设置父节点*/
//    void set_parent(GameObj* p);
//    /*获取父节点*/
//    GameObj* get_parent();
//    /*获取子节点数组*/
//    //std::list<uqp_obj>& get_children();
//    /*移除子节点*/
//    uqp_obj remove_children(GameObj* obj);
//    /*删除子节点*/
//    void delete_children(GameObj* obj);
//    /// <summary>
//    /// 添加子节点（默认表尾添加）
//    /// </summary>
//    /// <param name="obj">节点智能指针</param>
//    /// <param name="is_front">true/false 是否表头添加 默认false</param>
//    void add_children(uqp_obj obj, bool is_front = false);
//    /// <summary>
//    /// 遍历所有子对象
//    /// </summary>
//    /// <param name="func">外部传入的函数，参数为子对象的裸指针</param>
//    void for_each_child(const std::function<void(GameObj*)>& func);
//    /// <summary>
//    /// 子节点排序
//    /// </summary>
//    /// <param name="func">排序顺序函数</param>
//    void sort_children(const std::function<bool (const uqp_obj&, const uqp_obj&)>& func);
//    /// <summary>
//    /// 删除符合条件的子节点
//    /// </summary>
//    /// <param name="func"></param>
//    void remove_children_if(const std::function<bool(const uqp_obj&)>& func);
//    /// <summary>
//    /// 清理子节点
//    /// </summary>
//    void clear_children();
//    /// <summary>
//    /// 获取子节点数量
//    /// </summary>
//    /// <returns>int</returns>
//    int get_children_size();
};

INIT_TYPE_NAME(GameObj);