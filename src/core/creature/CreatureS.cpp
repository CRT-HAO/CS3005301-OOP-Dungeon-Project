/**
 *  File: CreatureS.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 23:12:10
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 02:34:25
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
    sprite.setScale(GRID_SIZE / spriteSize, GRID_SIZE / spriteSize);

    this->animationManager.addAnimation("Flying_Left", 0.1, 0, 0, 1, 0,
                                        spriteSize, spriteSize);
    this->animationManager.addAnimation("Damage_Left", 0.1, 2, 0, 3, 0,
                                        spriteSize, spriteSize);
}

void CreatureS::logic(KeyInput *keyInput, sf::Time &dt)
{
    if ( this->isUnderAttack() )
        this->animationManager.play("Damage_Left", dt);
    else
        this->animationManager.play("Flying_Left", dt);

    Creature::logic(keyInput, dt);
}
