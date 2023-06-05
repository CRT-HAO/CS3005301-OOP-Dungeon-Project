/**
 *  File: Camera.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:06:30
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 01:39:09
 *  Description: Camera Class
 */

#pragma once

#include "Object.hpp"
#include "Player.hpp"
#include "PositionFloat.hpp"

namespace Dungeon
{

    class Camera : public Object
    {
    private:
        PositionFloat pos;
        PositionFloat targetPos;
        bool smoothMove{true};
        double smoothMoveSpeed{0.05};

    public:
        Camera() {}
        Camera(const PositionFloat &pos) : pos(pos) {}

    public:
        void setPos(const PositionFloat &pos);
        void focus(Player *player);

    public:
        virtual void logic(KeyInput *keyInput) override;
        virtual void render(View *view) override;
    };

}