/**
 *  File: AICreatureEngine.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 22:30:00
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 17:26:18
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
        float shake;
        sf::Time lastAttack;
        sf::Time lastDamage;
        std::default_random_engine randomEngine;

    public:
        AICreatureEngine(World *world, Entity *creature, Player *follow,
                         float speed = 3, float shake = 7);

    public:
        inline void setSpeed(float speed) { this->speed = speed; }
        inline void setShake(float shake) { this->shake = shake; }

    public:
        void updatePosition(sf::Time &dt);

        void updateAttack(sf::Time &dt, float attackHP);

    public:
        Json toJson() const;
        void fromJson(const Json &json);
    };

}