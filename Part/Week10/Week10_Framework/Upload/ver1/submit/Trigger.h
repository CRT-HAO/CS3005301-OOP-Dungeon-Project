/**
 *  File: Trigger.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/11 00:53:37
 *  Description: Trigger Class
 */

#pragma once

#include "Hero.h"
#include "Position.h"

#include <iostream>
#include <string>

class Hero;

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
    Trigger() : _exp(10)
    {
        _icon = 'T';
    }
    Trigger(int x, int y) : _exp(10)
    {
        _pos.x = x;
        _pos.y = y;
        _icon = 'T';
    }
    Trigger(const Trigger &ref) { *this = ref; }

    void update(Hero &hero) const;

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
