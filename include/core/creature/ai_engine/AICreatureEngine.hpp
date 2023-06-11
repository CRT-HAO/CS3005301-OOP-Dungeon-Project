/**
 *  File: AICreatureEngine.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 22:30:00
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/11 16:47:33
 *  Description: AI Creature Engine Class
 */

#pragma once

#include "../../Entity.hpp"

#include <random>

namespace Dungeon
{
    // Forward declarations
    class World;
    class Player;

    class AICreatureEngine
    {
    private:
        World *world;
        Entity *creature;
        Player *follow;
        float speed;
        float attackInterval{1};
        sf::Time lastAttack;
        sf::Time lastDamage;
        std::default_random_engine randomEngine;

    public:
        AICreatureEngine(World *world, Entity *creature, Player *follow,
                         float speed = 3);

    public:
        void updatePosition(sf::Time &dt);

        void updateAttack(sf::Time &dt, float attackHP);
    };

}