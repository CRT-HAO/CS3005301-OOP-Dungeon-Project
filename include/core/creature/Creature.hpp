/**
 *  File: Creature.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 20:49:35
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/11 16:18:02
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

    public:
        Creature();
        Creature(World *world, Player *followPlayer);
        Creature(AICreatureEngine *aiEngine);

    public:
        inline void setAIEngine(AICreatureEngine *engine)
        {
            this->aiEngine = engine;
        }

        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
    };

}