/**
 *  File: CreatureS.hpp
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/20 17:43:43
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 18:48:01
 *  Description: Creature S
 */

#pragma once

#include "ICreature.hpp"

class CreatureS : public ICreature
{
public:
    // Default constructor
    CreatureS()
    {
        this->sType = TCreature::kS;
        this->sPos.x = 1;
        this->sPos.y = 1;
        this->sIcon = 'S';
        this->power = 5;
    };

public:
    virtual void update(Hero &hero) override
    {
        Position hPos = hero.getPos();

        Position dir;
        if ( canSee(this->sPos, hPos, dir) )
        {
            std::cout << "Creature has find the Hero in the ( "
                      << dir.x << ", " << dir.y << " ) direction\n";
            heroCanSee = true;
        }
        else
        {
            std::cout << "Creature didn't find the Hero\n";
            heroCanSee = false;
        }

        if ( !(hPos != sPos) )
        {
            hero.damage(power);
        }
    }
};