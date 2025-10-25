#pragma once
#include "character.h"

enum class ZmdjEnemyType
{
    E_S = 0,
    E_M,
    E_F
};

class EnemyZmdj :
    public Character
{
public:
    EnemyZmdj() = default;
    virtual ~EnemyZmdj() = default;

    EnemyZmdj(const std::string& id) : Character(id) {}
    EnemyZmdj(const std::string& id, int num) : Character(id, num) {}

    DEFINE_TYPE_NAME(EnemyZmdj);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    virtual void on_move(float delta);

private:
    // ��ȡ��������
    ZmdjEnemyType get_rand_enemy_type();
    // ���ù�������
    void set_enemy_of_type(ZmdjEnemyType type);
};

