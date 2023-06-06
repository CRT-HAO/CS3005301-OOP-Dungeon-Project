/**
 *  File: Block.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:15:11
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 15:43:38
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
        bool solid;
        size_t size;

    public:
        Block(TBlock type, bool solid = false, size_t size = 24)
            : type(type), solid(solid), size(size) {}

    public:
        inline TBlock getType() const { return this->type; }
        inline bool isSolid() const { return this->solid; }
        inline void setSolid(bool solid) { this->solid = solid; }
        inline size_t getSize() const { return this->size; }
        inline void setSize(size_t size) { this->size = size; };
    };
}