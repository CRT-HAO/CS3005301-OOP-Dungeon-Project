/**
 *  File: Creature.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 22:57:45
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/09 23:11:34
 *  Description: Creature Class
 */

#include "core/creature/Creature.hpp"
#include "core/creature/ai_engine/AICreatureEngine.hpp"

using namespace Dungeon;

Creature::Creature() : aiEngine(nullptr) {}

Creature::Creature(Entity *followEntity)
{
    this->aiEngine = new AICreatureEngine(this, followEntity);
}

Creature::Creature(AICreatureEngine *aiEngine) : aiEngine(aiEngine) {}

void Creature::logic(KeyInput *keyInput, sf::Time &dt)
{
    if ( this->aiEngine != nullptr )
        this->aiEngine->updatePosition(dt);
}

void Creature::render(sf::RenderWindow &window) { window.draw(this->sprite); }