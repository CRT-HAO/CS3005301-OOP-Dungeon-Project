/**
 *  File: Camera.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:09:20
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 01:38:02
 *  Description: Camera Class
 */

#include "core/Camera.hpp"

using namespace Dungeon;

void Camera::setPos(const PositionFloat &pos)
{
    this->targetPos = pos;
}

void Camera::focus(Player *player)
{
    this->targetPos = player->getPos();
}

void Camera::logic(KeyInput *keyInput)
{
}

void Camera::render(View *view)
{
    if ( !this->smoothMove )
    {
        this->pos = this->targetPos;
    }
    else
    {
        PositionFloat diff = this->targetPos - this->pos;
        double x = diff.x * this->smoothMoveSpeed;
        double y = diff.y * this->smoothMoveSpeed;
        this->pos.x += x;
        this->pos.y += y;
    }

    view->setCamera(this->pos);
}