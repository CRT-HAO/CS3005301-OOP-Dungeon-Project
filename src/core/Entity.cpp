/**
 *  File: Entity.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 23:05:30
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 00:17:26
 *  Description: Entity Class
 */

#include "core/Entity.hpp"

using namespace Dungeon;

bool Entity::intersects(const sf::FloatRect &frect)
{
    return this->hitbox.intersects(frect);
}