/**
 *  File: Player.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 00:43:07
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 02:44:15
 *  Description: Player Class
 */

#include "core/Player.hpp"

#include <cmath>

using namespace Dungeon;

Player::Player(World *world) : world(world) {}

Player::Player(World *world, const PositionFloat &pos) : world(world), pos(pos) {}

const PositionFloat &Player::getPos() const { return this->pos; }

bool Player::checkCollision(const PositionFloat &newPos)
{
    Position posF, posC;
    posF.x = std::floor(newPos.x);
    posF.y = std::floor(newPos.y);
    posC.x = std::ceil(newPos.x);
    posC.y = std::ceil(newPos.y);
    for ( Room *room : this->world->getRooms() )
    {
        Block *blockF = room->getBlockByWorldPos(posF);
        Block *blockC = room->getBlockByWorldPos(posC);
        if ( blockF == nullptr || blockC == nullptr )
            return false;

        if ( blockF->isSolid() || blockC->isSolid() )
            return true;
    }

    return false;
}

void Player::logic(KeyInput *keyInput)
{
    if ( keyInput->isUp() )
    {
        PositionFloat newPos = this->pos;
        newPos.y -= 0.5;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
            this->pos = newPos;
    }

    if ( keyInput->isDown() )
    {
        PositionFloat newPos = this->pos;
        newPos.y += 0.5;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
            this->pos = newPos;
    }

    if ( keyInput->isLeft() )
    {
        PositionFloat newPos = this->pos;
        newPos.x -= 0.5;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
            this->pos = newPos;
    }

    if ( keyInput->isRight() )
    {
        PositionFloat newPos = this->pos;
        newPos.x += 0.5;
        // 如果新位置不是實體，則移動到新位置
        if ( !this->checkCollision(newPos) )
            this->pos = newPos;
    }
}

void Player::render(View *view)
{
    Json data;
    data["type"] = "player";
    data["asset"] = 0;
    view->addObject(this->pos, data);
}
