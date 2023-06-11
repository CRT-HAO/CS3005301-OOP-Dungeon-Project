/**
 *  File: Creature.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 22:57:45
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/11 16:28:45
 *  Description: Creature Class
 */

#include "core/creature/Creature.hpp"
#include "core/creature/ai_engine/AICreatureEngine.hpp"

using namespace Dungeon;

Creature::Creature() : aiEngine(nullptr) { this->setZIndex(100); }

Creature::Creature(World *world, Player *followPlayer)
{
    this->setZIndex(100);
    this->aiEngine = new AICreatureEngine(world, this, followPlayer);
}

Creature::Creature(AICreatureEngine *aiEngine) : aiEngine(aiEngine)
{
    this->setZIndex(100);
}

void Creature::logic(KeyInput *keyInput, sf::Time &dt)
{
    if ( this->aiEngine != nullptr )
    {
        this->aiEngine->updatePosition(dt);
        this->aiEngine->updateAttack(dt, 5);
    }
}

void Creature::render(sf::RenderWindow &window) { window.draw(this->sprite); }