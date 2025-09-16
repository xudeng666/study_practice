#pragma once

//#include <forward_list>
#include <functional>

#include "game_type.h"
#include "vector2.h"
#include "obj.h"

template <typename T>
class Base {
public:
    // ÿ�����������һ��Ψһ��TypeID
    static const size_t TypeID;
    virtual size_t get_type_id() const = 0;
};

template <typename T> const size_t Base<T>::TypeID = typeid<size_t>.hash_code();

//class GameObj;
//
//typedef std::unique_ptr<GameObj> uqp_obj;

/*��Ϸ�������*/
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
    /*����ID*/
    void set_ID(const std::string str);
    void set_ID(const std::string str, const int num);
    /*��ȡID*/
    std::string get_ID();
    /*��ȡ·��ID*/
    std::string get_path_ID();
    /*id�����ж�*/
    bool id_contains(const std::string& str);
    /*��������*/
    void set_position(const Vector2& pos);
    /*��ȡ����*/
    const Vector2& get_position() const;
    /*���óߴ�*/
    virtual void set_size(const SDL_Point& size);
    /*��ȡ�ߴ�*/
    const SDL_Point& get_size() const;
    /*������ʾ״̬*/
    virtual void set_display(bool display);
    /*��ȡ��ʾ״̬*/
    virtual const bool get_display() const;
    /*����ê��*/
    void set_anchor_mode(const AnchorMode mode);
    /*��ȡê��*/
    const AnchorMode get_anchor_mode() const;
    /*����ê������ê��*/
    void set_anchor_referent_mode(const AnchorMode mode);
    /*��ȡê������ê��*/
    const AnchorMode get_anchor_referent_mode() const;
    /*����ê������*/
    void set_anchor_referent_obj(GameObj* obj);
    /*��ȡê������*/
    const GameObj* get_anchor_referent_obj();
    /*������ת����*/
    void set_center(const SDL_FPoint& pos);
    /*���ýǶ�*/
    void set_rotation(double val);
    /*���õ������״̬*/
    void set_click_enabled(bool enable);
    /*��ȡ�������״̬*/
    bool get_click_enabled();
    /*��ȡ��������*/
    SDL_FRect get_FRect();
    /*��ȡ��������*/
    SDL_Rect get_Rect();
    /// <summary>
    /// ��ȡ����ĳê���ȫ������
    /// </summary>
    /// <param name="mode">Ŀ��ê��</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(const AnchorMode mode);
    /// <summary>
    /// ��ȡ����ĳê���ȫ������
    /// </summary>
    /// <remarks>
    /// ���㱾�ڵ��ָ��ê�������ê��ȫ�����꣨�����޸�ʵ��ê������
    /// </remarks>
    /// <param name="obj">ê������</param>
    /// <param name="mode">Ŀ��ê��</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(GameObj* obj, const AnchorMode mode);
    /// <summary>
    /// ��ȡ���ӽڵ�ê���ȫ������
    /// </summary>
    /// <remarks>
    /// ĳ�������Ա��ڵ�Ϊê�㣬����ö����ĳ��ê��ȫ������
    /// </remarks>
    /// <param name="aligned">�������ê��</param>
    /// <param name="reference">Ŀ�����ê��</param>
    /// <param name="target">Ŀ�����ê��</param>
    /// <param name="pos">Ŀ���������</param>
    /// <param name="p_size">Ŀ��ߴ�</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(const AnchorMode aligned, const AnchorMode reference, const AnchorMode target, Vector2 pos, SDL_Point p_size);
    /// <summary>
    /// ����Ƿ�����Ļ��
    /// </summary>
    /// <param name="val">-1 0 1 �������壬����</param>
    /// <returns>true/false ��/����</returns>
    bool check_in_screen(int val = 0);

protected:
    std::string ID;
    // ��ת�Ƕ�
    double angle = 0.0;
    /*������򿪹�״̬*/
    bool click_enabled = true;
    // �Ƿ���ʾ
    bool is_display = true;
	/*��Ը��ڵ�����*/
    Vector2 position = { 0.0f, 0.0f };
    // ������� ��ʱ�������г�
    // SDL_FRect click_rect;
	/*�ߴ�*/
    SDL_Point size = { 0, 0 };
    // ���ĵ�
    SDL_FPoint center = { 0.0f, 0.0f };
	/*����ê��*/
    AnchorMode anchor_mode = AnchorMode::TOPLEFT;
    /*ê������ê��*/
    AnchorMode anchor_referent_mode = AnchorMode::TOPLEFT;

//protected:
//    // ���ڵ�
//    GameObj* parent = nullptr;
//    // ê������
//    GameObj* anchor_referent_obj = nullptr;
//    // �ӽڵ�
//    std::list<uqp_obj> children;
//
//public:
//    /*���ø��ڵ�*/
//    void set_parent(GameObj* p);
//    /*��ȡ���ڵ�*/
//    GameObj* get_parent();
//    /*��ȡ�ӽڵ�����*/
//    //std::list<uqp_obj>& get_children();
//    /*�Ƴ��ӽڵ�*/
//    uqp_obj remove_children(GameObj* obj);
//    /*ɾ���ӽڵ�*/
//    void delete_children(GameObj* obj);
//    /// <summary>
//    /// ����ӽڵ㣨Ĭ�ϱ�β��ӣ�
//    /// </summary>
//    /// <param name="obj">�ڵ�����ָ��</param>
//    /// <param name="is_front">true/false �Ƿ��ͷ��� Ĭ��false</param>
//    void add_children(uqp_obj obj, bool is_front = false);
//    /// <summary>
//    /// ���������Ӷ���
//    /// </summary>
//    /// <param name="func">�ⲿ����ĺ���������Ϊ�Ӷ������ָ��</param>
//    void for_each_child(const std::function<void(GameObj*)>& func);
//    /// <summary>
//    /// �ӽڵ�����
//    /// </summary>
//    /// <param name="func">����˳����</param>
//    void sort_children(const std::function<bool (const uqp_obj&, const uqp_obj&)>& func);
//    /// <summary>
//    /// ɾ�������������ӽڵ�
//    /// </summary>
//    /// <param name="func"></param>
//    void remove_children_if(const std::function<bool(const uqp_obj&)>& func);
//    /// <summary>
//    /// �����ӽڵ�
//    /// </summary>
//    void clear_children();
//    /// <summary>
//    /// ��ȡ�ӽڵ�����
//    /// </summary>
//    /// <returns>int</returns>
//    int get_children_size();
};

INIT_TYPE_NAME(GameObj);