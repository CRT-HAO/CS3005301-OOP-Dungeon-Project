/**
 *  File: CreatureS.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 23:07:16
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/09 23:18:44
 *  Description: Creature S Class
 */

#pragma once

#include "Creature.hpp"

namespace Dungeon
{

    class CreatureS : public Creature
    {
    public:
        CreatureS(Entity *followEntity);

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
    };

}