/**
 *  File: Trigger.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/04/15 00:41:55
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/04/15 02:00:18
 *  Description: Trigger Class
 */

#pragma once

#include "Hero.h"
#include "Position.h"

#include <iostream>
#include <string>

//************************************************************
// Trigger Class
//************************************************************
class Trigger
{
private:
    Position _pos;
    char _icon;
    int _exp;

public:
    Trigger(int x, int y, int exp) : _exp(exp)
    {
        _pos.x = x;
        _pos.y = y;
        _icon = 'T';
    }

    void update(Hero &hero) const
    {
        if ( hero.getPos().x == _pos.x && hero.getPos().y == _pos.y )
        {
            hero.gainEXP(_exp);
        }
    }

    // Set position
    void setPos(const Position &pos) { this->_pos = pos; }
    void setPos(int x, int y)
    {
        this->_pos.x = x;
        this->_pos.y = y;
    }

    // Get position
    Position getPos() const { return this->_pos; }

    // Get Icon
    char getIcon() const { return this->_icon; }

    int getExpAmount() const { return this->_exp; }
};
