/**
 *  File: AICreatureEngine.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 22:30:00
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/10 00:08:34
 *  Description: AI Creature Engine Class
 */

#pragma once

#include "../../Entity.hpp"

#include <random>

namespace Dungeon
{

    class AICreatureEngine
    {
    private:
        Entity *creature;
        Entity *follow;
        float speed;
        std::default_random_engine randomEngine;

    public:
        AICreatureEngine(Entity *creature, Entity *follow, float speed = 3);

    public:
        void updatePosition(sf::Time &dt);
    };

}