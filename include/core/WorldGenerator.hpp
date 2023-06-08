/**
 *  File: WorldGenerator.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:28:39
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/09 00:40:08
 *  Description: World Generator Class
 */

#pragma once

#include "Config.hpp"
#include "SFML/System/Vector2.hpp"
#include "World.hpp"

#include <vector>

namespace Dungeon
{

    class WorldGenerator
    {
    public:
        static void genDefaultWorld(World *world, Player *player,
                                    size_t roomNum = 20,
                                    size_t gridSize = GRID_SIZE);

    private:
        static void
        genRoomsTool(World *world, Player *player, const sf::Vector2i &roomSize,
                     const sf::Vector2f &pos, size_t roomNum, size_t &gridSize,
                     std::vector<sf::Vector2i> &existingRooms,
                     sf::Vector2i roomPos = {0, 0}, int srcDirection = -1);
    };

}