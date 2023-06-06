/**
 *  File: EntityManager.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 10:26:51
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 00:28:19
 *  Description: Objects Manager Class
 */

#include "core/EntityManager.hpp"

using namespace Dungeon;

EntityManager::EntityManager() {}

void EntityManager::addEntity(Entity *e)
{
    this->entities.push_back(e);
}

const std::vector<Entity *> &EntityManager::getEntities() const
{
    return this->entities;
}

bool EntityManager::intersects(const sf::FloatRect &frect)
{
    bool intersects = false;
    for ( const auto &en : this->entities )
        intersects |= en->intersects(frect);

    return intersects;
}

void EntityManager::init()
{
    for ( Entity *en : this->entities )
        en->init();
}

void EntityManager::logic(KeyInput *keyInput, sf::Time &dt)
{
    for ( Entity *en : this->entities )
        en->logic(keyInput, dt);
}

void EntityManager::render(sf::RenderWindow &window)
{
    for ( Entity *en : this->entities )
        en->render(window);
}