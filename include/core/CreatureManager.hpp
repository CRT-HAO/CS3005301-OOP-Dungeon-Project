/**
 *  File: CreatureManager.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/11 15:28:23
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/11 15:32:20
 *  Description: Creature Manager Class
 */

#pragma once

#include "EntityManager.hpp"
#include "creature/Creature.hpp"

#include <unordered_set>

namespace Dungeon
{

    class CreatureManager : public EntityManager
    {
    private:
        std::unordered_set<Creature *> creatures;

    public:
        CreatureManager();

    public:
        void addCreature(Creature *creature);
    };

}