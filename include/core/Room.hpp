/**
 *  File: Room.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:11:06
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/30 10:54:09
 *  Description: Room Class
 */

#pragma once

#include "Object.hpp"
#include "Position.hpp"
#include "PositionFloat.hpp"
#include "View.hpp"
#include "block/Block.hpp"

#include <vector>

namespace Dungeon
{

    class Room : public Object
    {
    private:
        std::vector<std::vector<Block *>> data;
        PositionFloat pos;
        size_t width;
        size_t height;

    public:
        Room(const PositionFloat &pos, size_t width = 10, size_t height = 10,
             bool autoGen = true);
        ~Room();

    public:
        void autoGen();

        void setBlock(const Position &pos, Block *block);

        virtual void logic() override;
        virtual void render(View *view) override;
    };

}