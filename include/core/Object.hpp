/**
 *  File: Object.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 22:59:50
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 22:13:47
 *  Description: Object Class
 */

#pragma once

#include "KeyInput.hpp"

#include <SFML/Graphics.hpp>

namespace Dungeon
{

    class Object
    {
    public:
        ~Object() = default;

    public:
        virtual void init() = 0;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) = 0;
        virtual void render(sf::RenderWindow &window) = 0;
    };

}