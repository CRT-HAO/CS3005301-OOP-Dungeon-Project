/**
 *  File: Player.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 00:40:17
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 01:51:03
 *  Description: Player Class
 */

#pragma once

#include "Object.hpp"
#include "PositionFloat.hpp"
#include "View.hpp"
#include "World.hpp"

#include <vector>

namespace Dungeon
{

    class Player : public Object
    {
    private:
        PositionFloat pos;
        World *world;

    public:
        Player(World *world);
        Player(World *world, const PositionFloat &pos);

    public:
        const PositionFloat &getPos() const;
        bool checkCollision(const PositionFloat &newPos);

    public:
        virtual void
        logic(KeyInput *keyInput) override;
        virtual void render(View *view) override;
    };
}