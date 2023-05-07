/**
 *  File: Position.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/06 10:56:37
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/07 02:01:39
 *  Description: Position Class
 */

#pragma once

#include <fstream>

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

    /*Please implement your code here*/
    friend inline void operator<<(std::ofstream &ofs, const Position &pos)
    {
        ofs << pos.x << pos.y;
    }

    friend inline void operator>>(std::ifstream &ifs, Position &pos)
    {
        ifs >> pos.x >> pos.y;
    }
    /************************************************************************/
};
