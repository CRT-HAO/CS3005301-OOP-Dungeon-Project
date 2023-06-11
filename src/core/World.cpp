/**
 *  File: World.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 02:58:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/11 15:37:18
 *  Description: World Class
 */

#include "core/World.hpp"

using namespace Dungeon;

World::World() {}

void World::clear() { this->rooms.clear(); }

const std::vector<Room *> &World::getRooms() { return this->rooms; }

void World::addRoom(Room *room) { this->rooms.push_back(room); }

void World::addCreature(Creature *creature)
{
    this->creatorManager.addCreature(creature);
}

bool World::intersects(const sf::FloatRect &frect)
{
    for ( const auto &room : this->rooms )
    {
        if ( room->intersects(frect) )
            return true;
    }
    return false;
}

void World::init()
{
    for ( Room *r : this->rooms )
        r->init();

    this->creatorManager.init();
}

void World::logic(KeyInput *keyInput, sf::Time &dt)
{
    for ( Room *r : this->rooms )
        r->logic(keyInput, dt);

    this->creatorManager.logic(keyInput, dt);
}

void World::render(sf::RenderWindow &window)
{
    for ( Room *r : this->rooms )
        r->render(window);

    this->creatorManager.render(window);
}