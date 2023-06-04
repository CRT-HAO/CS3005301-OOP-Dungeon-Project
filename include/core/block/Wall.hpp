/**
 *  File: Wall.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:29:15
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/30 01:33:23
 *  Description: Wall Block Class
 */

#pragma once

#include "Block.hpp"

namespace Dungeon
{

    class Wall : public Block
    {
    public:
        Wall() : Block(TBlock::kWall, true) {}
    };

}