/**
 *  File: AICreatureEngine.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/09 22:35:07
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/11 16:49:27
 *  Description: AI Creature Engine Class
 */

#include "core/creature/ai_engine/AICreatureEngine.hpp"
#include "Config.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Time.hpp"
#include "core/Player.hpp"
#include "core/Utilities.hpp"
#include "core/World.hpp"

#include <SFML/System/Vector2.hpp>
#include <iostream>

using namespace Dungeon;

AICreatureEngine::AICreatureEngine(World *world, Entity *creature,
                                   Player *follow, float speed)
    : world(world), creature(creature), follow(follow), speed(speed)
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

    sf::Vector2f newPos =
        this->creature->getPos() +
        (dt.asSeconds() * (this->speed * GRID_SIZE) * direction);

    sf::FloatRect newHitBox = this->creature->getGlobalBounds();
    newHitBox.left = newPos.x;
    newHitBox.top = newPos.y;

    if ( !this->world->intersects(newHitBox) )
    {
        this->creature->setPos(newPos);
    }
}

void AICreatureEngine::updateAttack(sf::Time &dt, float attackHP)
{
    sf::FloatRect hitBox = this->creature->getGlobalBounds();
    sf::FloatRect followHitBox = this->follow->getHitBox();

    if ( this->lastAttack.asSeconds() > this->attackInterval )
    {
        if ( followHitBox.intersects(hitBox) )
            this->follow->damage(attackHP);
        this->lastAttack = sf::Time::Zero;
    }
    else
        this->lastAttack += dt;
}