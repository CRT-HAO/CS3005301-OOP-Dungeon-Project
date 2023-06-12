/**
 *  File: World.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 02:58:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 17:37:55
 *  Description: World Class
 */

#include "core/World.hpp"
#include "core/Room.hpp"
#include "core/creature/CreatureB.hpp"
#include "core/creature/CreatureS.hpp"

using namespace Dungeon;

World::World(Player *player) : player(player) {}

void World::clear()
{
    this->rooms.clear();
    this->creatureManager.clear();
}

const std::vector<Room *> &World::getRooms() { return this->rooms; }

void World::addRoom(Room *room) { this->rooms.push_back(room); }

void World::addCreature(Creature *creature)
{
    this->creatureManager.addCreature(creature);
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

    this->creatureManager.init();
}

void World::logic(KeyInput *keyInput, sf::Time &dt)
{
    for ( Room *r : this->rooms )
        r->logic(keyInput, dt);

    this->creatureManager.logic(keyInput, dt);
}

void World::render(sf::RenderWindow &window)
{
    for ( Room *r : this->rooms )
        r->render(window);

    this->creatureManager.render(window);
}

Json World::toJson() const
{
    Json j;
    j["rooms"] = Json::array();
    for ( const auto &r : this->rooms )
        j["rooms"].push_back(r->toJson());
    j["creature_manager"] = this->creatureManager.toJson();
    return j;
}

void World::fromJson(const Json &json)
{
    this->rooms.clear();
    for ( const auto &r : json["rooms"] )
    {
        Room *room = new Room(this, this->player);
        room->fromJson(r);
        this->rooms.push_back(room);
    }

    this->creatureManager.clear();
    for ( const auto &c : json["creature_manager"]["entities"] )
    {
        if ( c["type"].get<std::string>() == "CreatureS" )
        {
            CreatureS *creature = new CreatureS(this, this->player);
            creature->fromJson(c);
            this->creatureManager.addCreature(creature);
        }
        else if ( c["type"].get<std::string>() == "CreatureB" )
        {
            CreatureB *creature = new CreatureB(this, this->player);
            creature->fromJson(c);
            this->creatureManager.addCreature(creature);
        }
    }
}
