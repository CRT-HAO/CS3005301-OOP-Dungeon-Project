/**
 *  File: Room.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:33:29
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 14:55:24
 *  Description: Room Class
 */

#include "core/Room.hpp"
#include "Config.hpp"
#include "core/block/Door.hpp"
#include "core/block/Ground.hpp"
#include "core/block/Heal.hpp"
#include "core/block/Torch.hpp"
#include "core/block/Wall.hpp"

#include <iostream>

using namespace Dungeon;

Room::Room(World *world, Player *player)
    : EntityManager(), world(world), player(player)
{
}

Room::~Room() {}

void Room::autoGen(const sf::Vector2f &pos, size_t width, size_t height)
{
    sf::Vector2f p;
    for ( p.y = 0; p.y < height; ++p.y )
    {
        for ( p.x = 0; p.x < width; ++p.x )
        {
            sf::Vector2f newPos = p;
            newPos.x *= GRID_SIZE;
            newPos.y *= GRID_SIZE;
            newPos += pos;
            if ( p.y == 0 )
                this->addBlock(new Wall(newPos));
            else if ( p.x == 0 )
                this->addBlock(new Wall(newPos));
            else if ( p.y == height - 1 )
                this->addBlock(new Wall(newPos));
            else if ( p.x == width - 1 )
                this->addBlock(new Wall(newPos));
            else
                this->addBlock(new Ground(newPos));
        }
    }

    // 火把
    this->addBlock(new Torch(pos + sf::Vector2f(1 * GRID_SIZE, 1 * GRID_SIZE)));
    this->addBlock(
        new Torch(pos + sf::Vector2f((width - 2) * GRID_SIZE, 1 * GRID_SIZE)));
    this->addBlock(
        new Torch(pos + sf::Vector2f(1 * GRID_SIZE, (height - 2) * GRID_SIZE)));
    this->addBlock(new Torch(
        pos + sf::Vector2f((width - 2) * GRID_SIZE, (height - 2) * GRID_SIZE)));

    this->addBlock(new Door(this->player,
                            pos + sf::Vector2f(8 * GRID_SIZE, 7 * GRID_SIZE)));
}

void Room::addBlock(Block *block) { this->addEntity(block); }

void Room::fromJson(const Json &json)
{
    this->clear();
    for ( const auto &b : json["entities"] )
    {
        if ( b["type"].get<std::string>() == "Ground" )
        {
            Ground *ground = new Ground();
            ground->fromJson(b);
            this->addBlock(ground);
        }
        else if ( b["type"].get<std::string>() == "Wall" )
        {
            Wall *wall = new Wall();
            wall->fromJson(b);
            this->addBlock(wall);
        }
        else if ( b["type"].get<std::string>() == "Torch" )
        {
            Torch *torch = new Torch();
            torch->fromJson(b);
            this->addBlock(torch);
        }
        else if ( b["type"].get<std::string>() == "Door" )
        {
            Door *door = new Door(this->player);
            door->fromJson(b);
            this->addBlock(door);
        }
        else if ( b["type"].get<std::string>() == "Heal" )
        {
            Heal *heal = new Heal(this->player);
            heal->fromJson(b);
            this->addBlock(heal);
        }
    }
}