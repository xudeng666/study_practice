#include "Player.h"
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
    player->on_update(delta);
}

void CharacterManager::on_draw()
{
    BulletTimeManager::instance()->post_process();// 在玩家绘制前调用，就不会影响玩家效果
    player->on_draw();
}

CharacterManager::CharacterManager()
{
    player = (Character*)new Player();
}

CharacterManager::~CharacterManager()
{
    delete enemy;
    delete player;
}