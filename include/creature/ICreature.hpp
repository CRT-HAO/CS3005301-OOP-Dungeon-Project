/**
 *  File: ICreature.hpp
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/20 17:43:43
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 18:48:45
 *  Description: Creature Interface
 */

#pragma once

#include "Hero.hpp"
#include "Position.hpp"
#include "TCreature.hpp"

class ICreature
{ // Creature Interface
protected:
    TCreature sType;
    Position sPos; // Creature position
    char sIcon;    // Creature icon
    int power;
    bool heroCanSee{false};

public:
    ~ICreature() = default;

    // Get type
    inline TCreature getType() const { return this->sType; }

    // Set position
    inline void setPos(Position pos) { this->sPos = pos; }

    inline void setPos(int x, int y)
    {
        this->sPos.x = x;
        this->sPos.y = y;
    }

    // Set icon
    void setIcon(char &icon) { this->sIcon = icon; }

    // Get position
    const Position &getPos() const { return this->sPos; }

    // Get icon
    char getIcon() const { return heroCanSee ? '!' : this->sIcon; }

public:
    virtual void update(Hero &hero) = 0;
};