/**
 *  File: Hero.h
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/04/23 09:17:14
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/04/23 09:21:45
 *  Description: Hero Class
 */

#pragma once

#include "Position.h"
#include "main.h"

#include <string>

//************************************************************
// Hero Class, only has requirement part for example
//************************************************************

class Hero
{

private:
    Position sPos;    // Hero location
    char sIcon = 'H'; // Hero icon
    int hp;
    int sLevel = 1;  // Level
    int sMaxExp;     // Level update experience
    int sCurrentExp; // current exp hero has

public:
    // Default constructor
    Hero()
    {
        this->sPos.x = 0;
        this->sPos.y = 0;
        this->sLevel = 1;
        this->sCurrentExp = 0;
        this->sMaxExp = 15;
        this->sIcon = 'H';
        this->hp = 100;
    };
    // Setting constructor
    Hero(int x, int y, int level = 1, int maxExp = 15, int currentExp = 0,
         char icon = 'H', int hp = 100)
    {
        this->sPos.x = x;
        this->sPos.y = y;
        this->sLevel = level;
        this->sCurrentExp = currentExp;
        this->sMaxExp = maxExp;
        this->sIcon = icon;
        this->hp = hp;
    };

    // Setting constructor
    Hero(Position &pos, int level = 1, int maxExp = 15, int currentExp = 0,
         char icon = 'H', int hp = 100)
    {
        this->sPos = pos;
        this->sLevel = level;
        this->sCurrentExp = currentExp;
        this->sMaxExp = maxExp;
        this->sIcon = icon;
        this->hp = hp;
    };

    // Set position
    void setPos(Position pos) { this->sPos = pos; }
    void setPos(int x, int y)
    {
        this->sPos.x = x;
        this->sPos.y = y;
    }

    // Set icon
    void setIcon(char &icon) { this->sIcon = icon; }

    // Set level
    void setLevel(int level) { this->sLevel = level; }

    // Set exp
    void setExp(int exp) { this->sCurrentExp = exp; }

    // Set MaxExp
    void SetMaxExp(int maxexp) { this->sMaxExp = maxexp; }

    // Get position
    Position getPos(void) { return this->sPos; }

    // Get Icon
    char getIcon(void) { return this->sIcon; }

    // Get level
    int getLevel(void) { return this->sLevel; }

    // Get Exp
    int getExp(void) { return this->sCurrentExp; }

    // Get Max
    int getMaxExp(void) { return this->sMaxExp; }

    int getHP() const { return this->hp; }

    // Incrementally move the elements
    void move(int x, int y)
    {
        // Compute the next position
        Position next;
        next.x = this->sPos.x + x;
        next.y = this->sPos.y + y;

        if ( isPositionValid(next) )
            this->sPos = next;
        else
        {
            std::cout << "Invalid location\n";
        }
    }

    // Calculate Gain of EXP
    void gainEXP(int points)
    {
        int number = points;
        while ( number > 0 )
        {
            if ( sCurrentExp + number >= sMaxExp )
            { // level up
                number -= (sMaxExp - sCurrentExp);
                sCurrentExp = 0;
                sMaxExp = (int)((float)sMaxExp * 1.2f);
                sLevel++;
            }
            else
            {
                sCurrentExp += number;
                number = 0;
            }
        }
    }
    void damage(int points)
    {
        hp = hp - points;
        if ( hp < 0 )
            hp = 0;
    }
};
