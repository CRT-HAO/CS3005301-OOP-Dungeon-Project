/**
 *  File: Player.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 00:40:17
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 15:47:48
 *  Description: Player Class
 */

#pragma once

#include "Object.hpp"
#include "PositionFloat.hpp"
#include "World.hpp"

#include <vector>

namespace Dungeon
{

    class Player : public Object
    {
    private:
        PositionFloat pos;
        World *world;
        size_t size{24};

    public:
        Player(World *world);
        Player(World *world, const PositionFloat &pos);

    public:
        const PositionFloat &getPos() const;
        bool checkCollision(const PositionFloat &newPos);

    public:
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
    };
}