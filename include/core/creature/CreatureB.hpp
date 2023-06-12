/**
 *  File: CreatureB.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 23:07:16
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 17:19:18
 *  Description: Creature S Class
 */

#pragma once

#include "../AnimationManager.hpp"
#include "Creature.hpp"

namespace Dungeon
{
    // Forwawd declarations
    class World;

    class CreatureB : public Creature
    {
    private:
        AnimationManager animationManager{sprite, texture};

    public:
        CreatureB(World *world, Player *followPlayer);

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual Json toJson() const override;
    };

}