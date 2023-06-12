/**
 *  File: CreatureB.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 23:12:10
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 17:26:59
 *  Description: Creature S Class
 */

#include "core/creature/CreatureB.hpp"
#include "Config.hpp"
#include "core/File.hpp"
#include "core/creature/Creature.hpp"

using namespace Dungeon;

CreatureB::CreatureB(World *world, Player *followPlayer)
    : Creature(world, followPlayer)
{
    this->aiEngine->setShake(5);
    this->aiEngine->setSpeed(5);
}

void CreatureB::init()
{
    int spriteSize = 16;
    this->texture.loadFromFile(
        fs::path(File::getResPath() / "images/sb_16x16.png").string());
    this->sprite.setTexture(this->texture);
    sprite.setScale(GRID_SIZE / spriteSize, GRID_SIZE / spriteSize);

    this->animationManager.addAnimation("Flying_Left", 0.1, 0, 0, 3, 0,
                                        spriteSize, spriteSize);
    this->animationManager.addAnimation("Damage_Left", 0.1, 4, 0, 7, 0,
                                        spriteSize, spriteSize);
}

void CreatureB::logic(KeyInput *keyInput, sf::Time &dt)
{
    if ( this->isUnderAttack() )
        this->animationManager.play("Damage_Left", dt);
    else
        this->animationManager.play("Flying_Left", dt);

    Creature::logic(keyInput, dt);
}

Json CreatureB::toJson() const
{
    Json j;
    j["type"] = "CreatureB";
    j.update(Creature::toJson());
    return j;
}