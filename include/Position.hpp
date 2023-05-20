/**
 *  File: Position.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/11 00:52:31
 *  Description: Position.h
 */

#pragma once

#include <iostream>

//************************************************************
// The location in the board
//************************************************************
class Position
{
public:
    int x, y; // X, y Coordinate

    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}
    Position(const Position &ref) { *this = ref; }

    // Operator overloading
    Position operator+(const Position &rhs) const
    {
        return Position(x + rhs.x, y + rhs.y);
    }
    Position &operator+=(const Position &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Position operator-(const Position &rhs) const
    {
        return Position(x - rhs.x, y - rhs.y);
    }
    Position &operator-=(const Position &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    Position operator*(int scale) const
    {
        return Position(x * scale, y * scale);
    }
    bool operator==(const Position &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    bool operator!=(const Position &rhs) const
    {
        return !(*this == rhs);
    }

    friend std::ostream &operator<<(std::ostream &oStream, const Position &pos)
    {
        return oStream << pos.x << " " << pos.y;
    }
    friend std::istream &operator>>(std::istream &iStream, Position &pos)
    {
        return iStream >> pos.x >> pos.y;
    }
};
