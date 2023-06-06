/**
 *  File: Camera.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:09:20
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 17:00:44
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

void Camera::logic(KeyInput *keyInput, sf::Time &dt)
{
    if ( !this->smoothMove )
    {
        this->pos = this->targetPos;
    }
    else
    {
        PositionFloat diff = this->targetPos - this->pos;
        double x = diff.x * this->smoothMoveSpeed * dt.asSeconds();
        double y = diff.y * this->smoothMoveSpeed * dt.asSeconds();
        this->pos.x += x;
        this->pos.y += y;
    }
}

void Camera::render(sf::RenderWindow &window) {}

void Camera::updateView(sf::View &view)
{
    view.setCenter(sf::Vector2f(this->pos.x * 24, this->pos.y * 24));
}
