/**
 *  File: EntityManager.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 10:26:51
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 06:41:15
 *  Description: Objects Manager Class
 */

#include "core/EntityManager.hpp"
#include "core/Entity.hpp"

using namespace Dungeon;

EntityManager::EntityManager() {}

void EntityManager::addEntity(Entity *e) { this->entities.insert(e); }

void EntityManager::removeEntity(Entity *e) { this->entities.erase(e); }

const std::unordered_set<Entity *> &EntityManager::getEntities() const
{
    return this->entities;
}

void EntityManager::clear() { this->entities.clear(); }

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

Json EntityManager::toJson() const
{
    Json j;
    j["entities"] = Json::array();
    for ( const auto &e : this->entities )
        j["entities"].push_back(e->toJson());
    return j;
}
