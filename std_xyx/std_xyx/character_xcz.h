#pragma once
#include "character.h"

/// <summary>
/// �Ҵ��߽�ɫ����
/// </summary>
class CharacterXcz :
    public Character
{
public:
    CharacterXcz() = default;
    virtual ~CharacterXcz() = default;

    CharacterXcz(const std::string& id) : Character(id) {}
    CharacterXcz(const std::string& id, int num) : Character(id, num) {}

    DEFINE_TYPE_NAME(CharacterXcz);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    /// <summary>
    /// �ܵ�����
    /// </summary>
    virtual void on_hurt() override;
    /// <summary>
    /// �ܵ�����
    /// </summary>
    virtual void on_hit() override;
    /// <summary>
    /// �ƶ�
    /// </summary>
    virtual void on_move(float delta);
    /// <summary>
    /// ���ý�ɫ����
    /// </summary>
    /// <param name="is_left">�Ƿ�����</param>
    virtual void set_face(bool is_left);
    /// <summary>
    /// ���ö���֡���ʱ�������ݶ����ƶ��ٶȣ�
    /// </summary>
    void set_interval();
    /// <summary>
    /// �����ƶ�״̬
    /// </summary>
    /// <param name="sub">�±�0123</param>
    /// <param name="flg">�ƶ�/ֹͣ true/false</param>
    void set_move_status(int sub, bool flg);
    /// <summary>
    /// ���ý�ɫ����
    /// </summary>
    /// <param name="val"></param>
    void set_step_length(float val);
    /// <summary>
    /// ���ý�ɫ�ٶ�
    /// </summary>
    /// <param name="val"></param>
    void set_speed(float val);

protected:
    // �ŵ���Ӱ
    TreeNode_WP img_shade;
    // �ƶ���ť״̬����������-0123��
    bool move_status[4];
    // ����
    float step_length = 48;
    // �ƶ��ٶ�(����/��)
    float speed = 50;
};