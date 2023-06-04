/**
 *  File: Room.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:33:29
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/30 10:54:19
 *  Description: Room Class
 */

#include "core/Room.hpp"
#include "core/block/Ground.hpp"
#include "core/block/Wall.hpp"

using namespace Dungeon;

Room::Room(const PositionFloat &pos, size_t width, size_t height, bool autoGen)
    : pos(pos), width(width), height(height)
{
    this->data.resize(height, std::vector<Block *>(width, nullptr));

    // 把房間方塊都設為地板
    Position p;
    for ( p.y = 0; p.y < height; ++p.y )
    {
        for ( p.x = 0; p.x < width; ++p.x )
        {
            this->setBlock(pos, new Ground());
        }
    }

    // 自動產生
    if ( autoGen )
        this->autoGen();
}

Room::~Room()
{
    // 釋放方塊
    for ( auto i : this->data )
    {
        for ( auto j : i )
        {
            if ( j != nullptr )
                delete j;
        }
    }
    this->data.clear();
}

void Room::autoGen()
{
    Position pos;
    for ( pos.y = 0; pos.y < height; ++pos.y )
    {
        for ( pos.x = 0; pos.x < width; ++pos.x )
        {
            if ( pos.y == 0 )
                this->setBlock(pos, new Wall());
            else if ( pos.x == 0 )
                this->setBlock(pos, new Wall());
            else if ( pos.y == height - 1 )
                this->setBlock(pos, new Wall());
            else if ( pos.x == width - 1 )
                this->setBlock(pos, new Wall());
            else
                this->setBlock(pos, new Ground());
        }
    }
}

void Room::setBlock(const Position &pos, Block *block)
{
    // 如果該位置已有方塊，釋放元素
    if ( this->data[pos.y][pos.x] != nullptr )
    {
        delete this->data[pos.y][pos.x];
        this->data[pos.y][pos.x] = nullptr;
    }

    this->data[pos.y][pos.x] = block;
}

void Room::logic() {}

void Room::render(View *view)
{
    PositionFloat pos;
    for ( const auto &i : this->data )
    {
        pos.x = 0;
        for ( const auto &j : i )
        {
            Json data;
            data["type"] = "block";
            data["asset"] = static_cast<int>(j->getType());
            view->addObject(pos, data);

            pos.x += 1;
        }
        pos.y += 1;
    }
}