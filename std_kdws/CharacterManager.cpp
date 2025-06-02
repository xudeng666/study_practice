#include "Player.h"
#include "Enemy.h"
#include "CharacterManager.h"
#include "BulletTimeManager.h"

CharacterManager* CharacterManager::manager = nullptr;

CharacterManager* CharacterManager::instance()
{
    if (!manager)
        manager = new CharacterManager();

    return manager;
}

void CharacterManager::on_input(const ExMessage& msg)
{
    player->on_input(msg);
}

void CharacterManager::on_update(float delta)
{
    enemy->on_update(delta);
    player->on_update(delta);
}

void CharacterManager::on_draw()
{
    enemy->on_draw();
    BulletTimeManager::instance()->post_process();// 在玩家绘制前调用，就不会影响玩家效果
    player->on_draw();
}

CharacterManager::CharacterManager()
{
    enemy = (Character*)new Enemy();
    player = (Character*)new Player();
}

CharacterManager::~CharacterManager()
{
    delete enemy;
    delete player;
}