/**
 *  File: AICreatureEngine.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 22:35:07
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/10 00:18:46
 *  Description: AI Creature Engine Class
 */

#include "core/creature/ai_engine/AICreatureEngine.hpp"
#include "Config.hpp"
#include "core/Utilities.hpp"

#include <SFML/System/Vector2.hpp>

using namespace Dungeon;

AICreatureEngine::AICreatureEngine(Entity *creature, Entity *follow,
                                   float speed)
    : creature(creature), follow(follow), speed(speed)
{
    this->randomEngine.seed(rand());
}

void AICreatureEngine::updatePosition(sf::Time &dt)
{
    std::uniform_real_distribution<double> unif(-7, 7);

    sf::Vector2f rand(unif(this->randomEngine), unif(this->randomEngine));

    sf::Vector2f direction = Utilities::normalize(this->follow->getCenter() -
                                                  this->creature->getCenter()) +
                             rand;

    this->creature->setPos(
        this->creature->getPos() +
        (dt.asSeconds() * (this->speed * GRID_SIZE) * direction));
}