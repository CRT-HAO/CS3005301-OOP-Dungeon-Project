/**
 *  File: WorldGenerator.pp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:28:39
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 17:32:35
 *  Description: World Generator Class
 */

#include "core/WorldGenerator.hpp"
#include "core/Room.hpp"
#include "core/block/Door.hpp"
#include "core/block/Ground.hpp"
#include "core/block/Heal.hpp"
#include "core/block/Torch.hpp"
#include "core/block/Wall.hpp"
#include "core/creature/CreatureB.hpp"
#include "core/creature/CreatureS.hpp"

#include <algorithm>
#include <map>

using namespace Dungeon;

void WorldGenerator::genDefaultWorld(World *world, Player *player,
                                     size_t roomNum, size_t gridSize)
{
    world->clear();

    const size_t WIDTH = 11;
    const size_t HEIGHT = 11;

    sf::Vector2i roomSize(WIDTH, HEIGHT);

    sf::Vector2f pos((static_cast<float>(WIDTH) / -2) * gridSize,
                     (static_cast<float>(HEIGHT) / -2) * gridSize);

    std::vector<sf::Vector2i> existingRooms;

    WorldGenerator::genRoomsTool(world, player, roomSize, pos, roomNum,
                                 gridSize, existingRooms);
}

void WorldGenerator::genRoomsTool(World *world, Player *player,
                                  const sf::Vector2i &roomSize,
                                  const sf::Vector2f &pos, size_t roomNum,
                                  size_t &gridSize,
                                  std::vector<sf::Vector2i> &existingRooms,
                                  sf::Vector2i roomPos, int srcDirection)
{
    if ( roomNum <= 0 )
        return;

    Room *room = new Room(world, player);

    std::map<int, Wall *> doorsWall;

    sf::Vector2i p;
    for ( p.y = 0; p.y < roomSize.y; ++p.y )
    {
        for ( p.x = 0; p.x < roomSize.x; ++p.x )
        {
            sf::Vector2f newPos(p.x, p.y);
            newPos.x *= GRID_SIZE;
            newPos.y *= GRID_SIZE;
            newPos += pos;
            if ( p.y == 0 )
            {
                // UP
                if ( srcDirection == 0 && (p.x == roomSize.y / 2) )
                    room->addBlock(new Ground(newPos));
                else
                {
                    Wall *wall = new Wall(newPos);
                    room->addBlock(wall);
                    if ( p.x == roomSize.x / 2 )
                        doorsWall[0] = wall;
                }
            }
            else if ( p.x == 0 )
            {
                // LEFT
                if ( srcDirection == 3 && (p.y == roomSize.y / 2) )
                    room->addBlock(new Ground(newPos));
                else
                {
                    Wall *wall = new Wall(newPos);
                    room->addBlock(wall);
                    if ( p.y == roomSize.y / 2 )
                        doorsWall[3] = wall;
                }
            }
            else if ( p.y == roomSize.x - 1 )
            {
                // DOWN
                if ( srcDirection == 2 && (p.x == roomSize.y / 2) )
                    room->addBlock(new Ground(newPos));
                else
                {
                    Wall *wall = new Wall(newPos);
                    room->addBlock(wall);
                    if ( p.x == roomSize.x / 2 )
                        doorsWall[2] = wall;
                }
            }
            else if ( p.x == roomSize.x - 1 )
            {
                // RIGHT
                if ( srcDirection == 1 && (p.y == roomSize.y / 2) )
                    room->addBlock(new Ground(newPos));
                else
                {
                    Wall *wall = new Wall(newPos);
                    room->addBlock(wall);
                    if ( p.y == roomSize.y / 2 )
                        doorsWall[1] = wall;
                }
            }
            else
                room->addBlock(new Ground(newPos));
        }
    }

    // 火把
    room->addBlock(new Torch(pos + sf::Vector2f(1 * GRID_SIZE, 1 * GRID_SIZE)));
    room->addBlock(new Torch(
        pos + sf::Vector2f((roomSize.x - 2) * GRID_SIZE, 1 * GRID_SIZE)));
    room->addBlock(new Torch(
        pos + sf::Vector2f(1 * GRID_SIZE, (roomSize.y - 2) * GRID_SIZE)));
    room->addBlock(new Torch(pos + sf::Vector2f((roomSize.x - 2) * GRID_SIZE,
                                                (roomSize.y - 2) * GRID_SIZE)));

    room->addBlock(
        new Door(player, pos + sf::Vector2f(8 * GRID_SIZE, 7 * GRID_SIZE)));

    // 產生怪物
    for ( size_t i = 0; i < 3; ++i )
    {
        Creature *creature = new CreatureS(world, player);
        creature->setPos(pos + sf::Vector2f(5 * GRID_SIZE, 5 * GRID_SIZE));
        world->addCreature(creature);
    }

    // 產生怪物
    for ( size_t i = 0; i < 3; ++i )
    {
        Creature *creature = new CreatureB(world, player);
        creature->setPos(pos + sf::Vector2f(5 * GRID_SIZE, 5 * GRID_SIZE));
        world->addCreature(creature);
    }

    // 補包
    room->addBlock(
        new Heal(player, pos + sf::Vector2f(4 * GRID_SIZE, 6 * GRID_SIZE)));

    world->addRoom(room);

    existingRooms.push_back(roomPos);

    int randRoomNum = (rand() % 3) + 1;

    roomNum -= 1;

    // 隨機挑0~3個方向產生房間
    for ( size_t i = 0, newDirI = rand();
          i < std::min(randRoomNum, static_cast<int>(roomNum)); ++newDirI )
    {
        sf::Vector2f newPos = pos;
        sf::Vector2i newRoomPos = roomPos;

        int newDir = newDirI % 4;

        // 如果新房間的方向是原來房間的方向，則往下一個方向
        if ( newDir == srcDirection )
            continue;

        if ( newDir == 0 )
        {
            // UP
            newPos.y -= roomSize.y * gridSize;
            newRoomPos.y -= 1;
        }
        else if ( newDir == 1 )
        {
            // RIGHT
            newPos.x += roomSize.x * gridSize;
            newRoomPos.x += 1;
        }
        else if ( newDir == 2 )
        {
            // DOWN
            newPos.y += roomSize.y * gridSize;
            newRoomPos.y += 1;
        }
        else if ( newDir == 3 )
        {
            // LEFT
            newPos.x -= roomSize.x * gridSize;
            newRoomPos.x -= 1;
        }
        int dir = newDir - 2;
        int srcDir = (dir >= 0) ? dir : (newDir + 2);

        if ( std::find(existingRooms.begin(), existingRooms.end(),
                       newRoomPos) != existingRooms.end() )
            continue;

        // 移除該方向上的牆壁
        room->removeEntity(doorsWall[newDir]);

        WorldGenerator::genRoomsTool(world, player, roomSize, newPos,
                                     rand() % roomNum, gridSize, existingRooms,
                                     newRoomPos, srcDir);
        ++i;
    }
}