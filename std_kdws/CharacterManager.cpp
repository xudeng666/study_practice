#include "Player.h"
#include "CharacterManager.h"

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