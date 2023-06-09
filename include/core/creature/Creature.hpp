/**
 *  File: Creature.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 20:49:35
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/09 23:22:52
 *  Description: Creature Class
 */

#pragma once

#include "../Entity.hpp"
#include "ai_engine/AICreatureEngine.hpp"

namespace Dungeon
{

    class Creature : public Entity
    {
    private:
        AICreatureEngine *aiEngine;

    public:
        Creature();
        Creature(Entity *followEntity);
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