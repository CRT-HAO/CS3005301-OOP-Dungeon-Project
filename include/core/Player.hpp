/**
 *  File: Player.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 00:40:17
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/08 21:03:33
 *  Description: Player Class
 */

#pragma once

#include "AnimationManager.hpp"
#include "Config.hpp"
#include "Entity.hpp"
#include "World.hpp"

#include <vector>

namespace Dungeon
{
    enum class PlayerState
    {
        Idle,
        Moving,
    };

    enum class PlayerDirection
    {
        Left,
        Right,
    };

    class Player : public Entity
    {
    private:
        World *world;
        size_t size{GRID_SIZE};
        AnimationManager animationManager{this->sprite, this->texture};
        PlayerState state{PlayerState::Idle};
        PlayerDirection dir{PlayerDirection::Left};

    public:
        Player(World *world);
        Player(World *world, const sf::Vector2f &pos);

    public:
        bool checkCollision(const sf::Vector2f &newPos);

        void updateHitbox();
        void updateAnimation(sf::Time &dt);

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
    };
}