/**
 *  File: Ground.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:29:15
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 07:59:46
 *  Description: Ground Block Class
 */

#pragma once

#include "Block.hpp"

#include <SFML/Graphics.hpp>

namespace Dungeon
{

    class Ground : public Block
    {
    private:
        int textureType;

    public:
        Ground();
        Ground(const sf::Vector2f &pos);

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
        virtual Json toJson() const override;
    };

}