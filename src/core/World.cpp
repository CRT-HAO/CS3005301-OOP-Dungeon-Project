/**
 *  File: World.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 02:58:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 16:59:24
 *  Description: World Class
 */

#include "core/World.hpp"

using namespace Dungeon;

World::World() {}

void World::clear()
{
    this->rooms.clear();
}

const std::vector<Room *> &World::getRooms()
{
    return this->rooms;
}

void World::addRoom(Room *room)
{
    this->rooms.push_back(room);
}

void World::logic(KeyInput *keyInput, sf::Time &dt)
{
    for ( Room *r : this->rooms )
        r->logic(keyInput, dt);
}

void World::render(sf::RenderWindow &window)
{
    for ( Room *r : this->rooms )
        r->render(window);
}