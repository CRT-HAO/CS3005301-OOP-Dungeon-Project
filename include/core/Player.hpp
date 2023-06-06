/**
 *  File: Player.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 00:40:17
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 01:47:27
 *  Description: Player Class
 */

#pragma once

#include "Config.hpp"
#include "Entity.hpp"
#include "World.hpp"

#include <vector>

namespace Dungeon
{

    class Player : public Entity
    {
    private:
        World *world;
        size_t size{GRID_SIZE};

    public:
        Player(World *world);
        Player(World *world, const sf::Vector2f &pos);

    public:
        bool checkCollision(const sf::Vector2f &newPos);

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
    };
}