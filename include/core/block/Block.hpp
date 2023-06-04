/**
 *  File: Block.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:15:11
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/30 10:13:58
 *  Description: Block Class
 */

#pragma once

#include "TBlock.hpp"

namespace Dungeon
{

    class Block
    {
    private:
        TBlock type{TBlock::kUndefined};
        bool solid{false};

    public:
        Block(TBlock type, bool solid = false)
            : type(type), solid(solid) {}

    public:
        inline TBlock getType() const { return this->type; }
        inline bool isSolid() const { return this->solid; }
        inline void setSolid(bool solid) { this->solid = solid; }
    };

}