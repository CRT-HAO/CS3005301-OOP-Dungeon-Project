/**
 *  File: GUI.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 08:36:07
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 09:37:20
 *  Description: GUI Class
 */

#pragma once

#include "core/Object.hpp"
namespace Dungeon
{

    class GUI
    {
    public:
        ~GUI() = default;

    public:
        virtual void init() = 0;
        virtual void logic(KeyInput *keyInput, sf::Time &dt,
                           sf::View &view) = 0;
        virtual void render(sf::RenderWindow &window) = 0;
    };

}