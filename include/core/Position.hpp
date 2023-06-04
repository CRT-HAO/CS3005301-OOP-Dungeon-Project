/**
 *  File: Position.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:36:45
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/30 10:36:14
 *  Description: Position Class
 */

#pragma once

namespace Dungeon
{
    class PositionFloat;

    class Position
    {
    public:
        int x;
        int y;

    public:
        Position() : x(0), y(0) {}
        Position(int x, int y) : x(x), y(y) {}
        Position(const PositionFloat &pos);

    public:
        friend inline Position operator+(const Position &a, const Position &b)
        {
            Position p;
            p.x = a.x + b.x;
            p.y = a.y + b.y;
            return p;
        }

        friend inline Position operator-(const Position &a, const Position &b)
        {
            Position p;
            p.x = a.x - b.x;
            p.y = a.y - b.y;
            return p;
        }

        friend inline bool operator==(const Position &a, const Position &b)
        {
            return (a.x == b.x && a.y == b.y);
        }

        friend inline bool operator!=(const Position &a, const Position &b)
        {
            return (a.x != b.x || a.y != b.y);
        }
    };

}