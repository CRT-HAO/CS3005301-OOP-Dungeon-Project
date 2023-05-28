/**
 *  File: Trigger.cpp
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/26 01:37:48
 *  Description: Trigger Class
 */

#include "item/Trigger.hpp"

#include "Hero.hpp"

std::string Trigger::getInfo() const
{
    std::stringstream ss;
    ss << "icon=" << this->getIcon() << ", "
       << "posX=" << this->getPos().x << ", "
       << "posY=" << this->getPos().y << ", "
       << "exp=" << this->_exp;
    return ss.str();
}

void Trigger::update(Hero &hero)
{
    if ( hero.getPos().x == _pos.x && hero.getPos().y == _pos.y )
    {
        hero.gainEXP(_exp);
    }
}