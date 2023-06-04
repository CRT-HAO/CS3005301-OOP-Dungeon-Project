/**
 *  File: PositionFloat.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 10:36:58
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/30 10:39:41
 *  Description: PositionFloat Class
 */

#include "core/PositionFloat.hpp"
#include "core/Position.hpp"

using namespace Dungeon;

PositionFloat::PositionFloat(const Position &pos)
{
    this->x = static_cast<double>(pos.x);
    this->y = static_cast<double>(pos.y);
}