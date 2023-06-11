/**
 *  File: Creature.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 20:49:35
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 02:33:59
 *  Description: Creature Class
 */

#pragma once

#include "../Entity.hpp"
#include "ai_engine/AICreatureEngine.hpp"

namespace Dungeon
{
    // Forward declarations
    class World;

    class Creature : public Entity
    {
    private:
        AICreatureEngine *aiEngine;

    protected:
        float hp;
        bool underAttack{false};
        sf::Time damageTime;

    public:
        Creature(float hp = 100);
        Creature(World *world, Player *followPlayer, float hp = 100);
        Creature(AICreatureEngine *aiEngine, float hp = 100);

    public:
        inline void setAIEngine(AICreatureEngine *engine)
        {
            this->aiEngine = engine;
        }

        inline float getHP() const { return this->hp; }

        inline void setHP(float hp) { this->hp = hp; }

        inline bool isDead() const { return this->hp <= 0; }

        inline bool isUnderAttack() const { return this->underAttack; }

    public:
        void damage(float damage);

    public:
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
    };

}