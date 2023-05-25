/**
 *  File: IItem.hpp
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/26 00:24:46
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/26 01:36:55
 *  Description: Item Interface
 */

#pragma once

#include "Position.hpp"
#include "TItem.hpp"

#include <string>

class Hero;

class IItem
{
protected:
    TItem _type;
    Position _pos;
    char _icon;

public:
    IItem(TItem type, char icon) : _type(type), _icon(icon) {}

    IItem(TItem type, char icon, const Position &pos)
        : _type(type), _icon(icon), _pos(pos) {}

    IItem(TItem type, char icon, int posX, int posY)
        : _type(type), _icon(icon)
    {
        this->_pos.x = posX;
        this->_pos.y = posY;
    }

    ~IItem() = default;

    // Get Type
    inline TItem getType() const { return this->_type; }

    // Set Position
    virtual inline void setPos(const Position &pos) { this->_pos = pos; }
    virtual inline void setPos(int x, int y)
    {
        this->_pos.x = x;
        this->_pos.y = y;
    }

    // Get Position
    virtual inline const Position &getPos() const { return this->_pos; }

    // Get Icon
    virtual inline char getIcon() const { return this->_icon; }

    // Get Info
    virtual std::string getInfo() const = 0;

    // Update
    virtual void update(Hero &hero) = 0;
};