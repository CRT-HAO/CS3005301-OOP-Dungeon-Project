/**
 *  File: Position.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 10:36:58
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/30 10:38:48
 *  Description: Position Class
 */

#include "core/Position.hpp"
#include "core/PositionFloat.hpp"

using namespace Dungeon;

Position::Position(const PositionFloat &pos)
{
    this->x = static_cast<int>(pos.x);
    this->y = static_cast<int>(pos.y);
}