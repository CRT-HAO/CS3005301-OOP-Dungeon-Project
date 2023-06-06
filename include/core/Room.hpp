/**
 *  File: Room.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:11:06
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 00:29:40
 *  Description: Room Class
 */

#pragma once

#include "EntityManager.hpp"
#include "Object.hpp"
#include "Position.hpp"
#include "PositionFloat.hpp"
#include "block/Block.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

namespace Dungeon
{

    class Room : public EntityManager
    {
    public:
        Room();
        ~Room();

    public:
        void autoGen(const sf::Vector2f &pos, size_t width = 10, size_t height = 10);

        void addBlock(Block *block);
    };

}