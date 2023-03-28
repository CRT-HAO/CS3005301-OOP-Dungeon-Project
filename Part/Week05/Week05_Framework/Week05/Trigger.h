/**
 *  File: Trigger.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023-03-28 18:12:41
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/03/28 19:43:45
 *  Description: Trigger Class
 */

#pragma once
#include <iostream>
#include <string>

#include "Hero.h"
#include "Position.h"

//************************************************************
// Trigger Class
//************************************************************
class Trigger
{
    // Implement Trigger Class
    /*Please implement your code here*/

private:
    Position sPos;
    char sIcon = 'T';
    int sExpAmount;

public:
    Trigger(int x, int y, int expAmount, char icon = 'T')
    {
        this->sPos = Position{x, y};
        this->sExpAmount = expAmount;
        this->sIcon = icon;
    }

    Position getPos()
    {
        return this->sPos;
    }

    char getIcon()
    {
        return this->sIcon;
    }

    int getExpAmount()
    {
        return this->sExpAmount;
    }

    void update(Hero &hero)
    {
        Position heroPos = hero.getPos();
        if ( heroPos.x == this->sPos.x && heroPos.y == this->sPos.y )
            hero.gainEXP(this->sExpAmount);
    }

    /************************************************************************/
};
