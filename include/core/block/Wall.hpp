/**
 *  File: Wall.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:29:15
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/06 23:55:31
 *  Description: Wall Block Class
 */

#pragma once

#include "Block.hpp"

#include <SFML/Graphics.hpp>

namespace Dungeon
{

    class Wall : public Block
    {
    public:
        Wall();
        Wall(const sf::Vector2f &pos);

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
    };

}