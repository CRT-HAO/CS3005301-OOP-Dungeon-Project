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

void World::logic(KeyInput *keyInput)
{
    for ( Room *r : this->rooms )
        r->logic(keyInput);
}

void World::render(View *view)
{
    for ( Room *r : this->rooms )
        r->render(view);
}