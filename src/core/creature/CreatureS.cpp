/**
 *  File: CreatureS.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 23:12:10
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/11 16:19:39
 *  Description: Creature S Class
 */

#include "core/creature/CreatureS.hpp"
#include "Config.hpp"
#include "core/File.hpp"

using namespace Dungeon;

CreatureS::CreatureS(World *world, Player *followPlayer)
    : Creature(world, followPlayer)
{
}

void CreatureS::init()
{
    int spriteSize = 8;
    this->texture.loadFromFile(
        fs::path(File::getResPath() / "images/spritesheet_enemy.png").string());
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(0, 0, spriteSize, spriteSize));
    sprite.setScale(GRID_SIZE / spriteSize, GRID_SIZE / spriteSize);
}

void CreatureS::logic(KeyInput *keyInput, sf::Time &dt)
{
    Creature::logic(keyInput, dt);
}
