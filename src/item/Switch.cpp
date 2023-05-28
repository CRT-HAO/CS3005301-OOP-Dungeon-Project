/**
 *  File: Switch.cpp
 *  Author: 張皓鈞 (B11030202@mail.ntust.edu.tw)
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 15:02:27
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/26 01:38:00
 *  Description: Switch Class
 */

#include "item/Switch.hpp"

#include "Hero.hpp"

std::string Switch::getInfo() const
{
    std::stringstream ss;
    ss << "icon=" << this->getIcon() << ", "
       << "posX=" << this->getPos().x << ", "
       << "posY=" << this->getPos().y << ", "
       << "on=" << this->_on;
    return ss.str();
}

void Switch::update(Hero &hero)
{
    if ( hero.getPos().x == _pos.x && hero.getPos().y == _pos.y )
        this->_on = !this->_on;

    if ( this->_on )
        this->_icon = Switch::ON_ICON;
    else
        this->_icon = Switch::OFF_ICON;
}