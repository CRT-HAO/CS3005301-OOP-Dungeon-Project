/**
 *  File: Ground.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:29:15
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/29 23:30:22
 *  Description: Ground Block Class
 */

#pragma once

#include "Block.hpp"

namespace Dungeon
{

    class Ground : public Block
    {
    public:
        Ground() : Block(TBlock::kGround, false) {}
    };

}