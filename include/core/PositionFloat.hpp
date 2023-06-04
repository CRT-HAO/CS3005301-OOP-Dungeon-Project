/**
 *  File: PositionFloat.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:36:45
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/30 10:39:23
 *  Description: Position Float Class
 */

#pragma once

namespace Dungeon
{
    class Position;

    class PositionFloat
    {
    public:
        double x;
        double y;

    public:
        PositionFloat() : x(0), y(0) {}
        PositionFloat(double x, double y) : x(x), y(y) {}
        PositionFloat(const Position &pos);

    public:
        friend inline PositionFloat operator+(const PositionFloat &a, const PositionFloat &b)
        {
            PositionFloat p;
            p.x = a.x + b.x;
            p.y = a.y + b.y;
            return p;
        }

        friend inline PositionFloat operator-(const PositionFloat &a, const PositionFloat &b)
        {
            PositionFloat p;
            p.x = a.x - b.x;
            p.y = a.y - b.y;
            return p;
        }

        friend inline bool operator==(const PositionFloat &a, const PositionFloat &b)
        {
            return (a.x == b.x && a.y == b.y);
        }

        friend inline bool operator!=(const PositionFloat &a, const PositionFloat &b)
        {
            return (a.x != b.x || a.y != b.y);
        }
    };

}