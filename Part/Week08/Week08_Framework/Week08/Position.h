/**
 *  File: Position.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/04/25 21:08:31
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/04/25 21:18:46
 *  Description: Position Class
 */

#pragma once

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
    /*Please implement your code here*/
    inline Position operator+(const Position &pos) const
    {
        Position r = (*this);
        r.x += pos.x, r.y += pos.y;
        return r;
    }

    inline Position &operator+=(const Position &pos)
    {
        this->x += pos.x, this->y += pos.y;
        return (*this);
    }

    inline Position operator-(const Position &pos) const
    {
        Position r = (*this);
        r.x -= pos.x, r.y -= pos.y;
        return r;
    }

    inline Position &operator-=(const Position &pos)
    {
        this->x -= pos.x, this->y -= pos.y;
        return (*this);
    }

    inline Position operator*(const int &n) const
    {
        Position r = (*this);
        r.x *= n, r.y *= n;
        return r;
    }

    inline bool operator==(const Position &pos) const
    {
        return (this->x == pos.x && this->y == pos.y);
    }

    inline bool operator!=(const Position &pos) const
    {
        return (this->x != pos.x || this->y != pos.y);
    }
    /************************************************************************/
};
