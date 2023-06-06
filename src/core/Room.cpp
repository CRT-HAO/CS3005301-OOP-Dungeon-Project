/**
 *  File: Room.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:33:29
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 16:24:47
 *  Description: Room Class
 */

#include "core/Room.hpp"
#include "core/block/Ground.hpp"
#include "core/block/Wall.hpp"

using namespace Dungeon;

Room::Room(const Position &pos, size_t width, size_t height, bool autoGen)
    : pos(pos), width(width), height(height)
{
    this->data.resize(height, std::vector<Block *>(width, nullptr));

    // 把房間方塊都設為地板
    Position p;
    for ( p.y = 0; p.y < height; ++p.y )
    {
        for ( p.x = 0; p.x < width; ++p.x )
        {
            this->setBlock(p, new Ground());
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
    Position p;
    for ( p.y = 0; p.y < height; ++p.y )
    {
        for ( p.x = 0; p.x < width; ++p.x )
        {
            if ( p.y == 0 )
                this->setBlock(p, new Wall());
            else if ( p.x == 0 )
                this->setBlock(p, new Wall());
            else if ( p.y == height - 1 )
                this->setBlock(p, new Wall());
            else if ( p.x == width - 1 )
                this->setBlock(p, new Wall());
            else
                this->setBlock(p, new Ground());
        }
    }
}

Block *Room::getBlock(const Position &pos)
{
    if ( pos.y < 0 || pos.y > this->data.size() - 1 ||
         pos.x < 0 || pos.x > this->data[pos.y].size() - 1 )
        return nullptr;

    return this->data[pos.y][pos.x];
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

Block *Room::getBlockByWorldPos(const Position &worldPos)
{
    Position p = worldPos - this->pos;
    if ( p.y < 0 || p.y > this->data.size() - 1 ||
         p.x < 0 || p.x > this->data[p.y].size() - 1 )
        return nullptr;

    return this->data[p.y][p.x];
}

void Room::logic(KeyInput *keyInput, sf::Time &dt)
{
}

void Room::render(sf::RenderWindow &window)
{
    Position p;
    for ( const auto &i : this->data )
    {
        p.x = 0;
        for ( const auto &j : i )
        {
            sf::RectangleShape shape(sf::Vector2f(j->getSize(), j->getSize()));
            shape.setPosition((this->pos.x + p.x) * static_cast<int>(j->getSize()),
                              (this->pos.y + p.y) * static_cast<int>(j->getSize()));
            shape.setFillColor(j->getType() == TBlock::kWall
                                   ? sf::Color::Green
                                   : sf::Color::White);
            window.draw(shape);

            p.x += 1;
        }
        p.y += 1;
    }
}