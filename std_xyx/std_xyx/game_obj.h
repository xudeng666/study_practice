#pragma once

#include "game_type.h"
#include "vector2.h"
#include "obj.h"
#include "tree_node.h"


/*��Ϸ�������*/
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

    /*����ID*/
    virtual void set_ID(const std::string& str) override;
    virtual void set_ID(const std::string& str, const int num) override;
    /*��ȡID*/
    virtual std::string get_ID() override;
    /*��ȡ·��ID*/
    virtual std::string get_path_ID();
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
    void set_anchor_referent_node(TreeNode_WP node);
    /*��ȡê������*/
    TreeNode_SP get_anchor_referent();
    /*������ת����*/
    void set_center(const SDL_FPoint& pos);
    /*���ýǶ�*/
    void set_rotation(double val);
    /*���ýǶ�*/
    double get_rotation();
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
    /// <param name="mode">����ê��</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(const AnchorMode mode);
    /// <summary>
    /// ��ȡ����ĳê���ȫ������
    /// </summary>
    /// <remarks>
    /// ָ�����������������ĳ���ڵ�Ľ��
    /// </remarks>
    /// <param name="node">ָ���ڵ�</param>
    /// <param name="mode">����ê��</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(TreeNode_WP node, const AnchorMode mode);
    /// <summary>
    /// ��ȡ���ӽڵ�ê���ȫ������
    /// </summary>
    /// <remarks>
    /// �����и��ֽڵ�ê�����ڵ㣬��ȡ���ӽڵ��ĳ��ê��ȫ������
    /// </remarks>
    /// <param name="aligned">���ӽڵ�ê����ê��</param>
    /// <param name="reference">�ӽڵ�ê��ê��</param>
    /// <param name="target">�ӽڵ����ê��</param>
    /// <param name="pos">�ӽڵ�����</param>
    /// <param name="p_size">�ӽڵ��С</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(const AnchorMode aligned, const AnchorMode reference, const AnchorMode target, Vector2 pos, SDL_Point p_size);
    /// <summary>
    /// ����Ƿ�����Ļ��
    /// </summary>
    /// <param name="val">-1 0 1 �������壬����</param>
    /// <returns>true/false ��/����</returns>
    bool check_in_screen(int val = 0);


    // �жϵ��Ƿ��ڿؼ���Χ��
    bool contains_point(const SDL_Point* point);

protected:
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
    /*ê������ڵ�*/
    TreeNode_WP anchor_referent_node;
};