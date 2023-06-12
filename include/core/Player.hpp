/**
 *  File: Player.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 00:40:17
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 09:07:15
 *  Description: Player Class
 */

#pragma once

#include "AnimationManager.hpp"
#include "Config.hpp"
#include "Entity.hpp"
#include "Weapon.hpp"
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
        Down,
        Up,
    };

    class Player : public Entity
    {
    private:
        World *world;
        size_t size{GRID_SIZE};
        AnimationManager animationManager{this->sprite, this->texture};
        PlayerState state{PlayerState::Idle};
        PlayerDirection dirX{PlayerDirection::Left};
        PlayerDirection dir{PlayerDirection::Left};
        Weapon *weapon;
        float maxHP{100};
        float hp{maxHP};

    public:
        Player(World *world);
        Player(World *world, const sf::Vector2f &pos);
        ~Player();

    public:
        void setWorld(World *world);

        inline float getHP() const { return this->hp; }

        inline void setHP(float hp) { this->hp = hp; }

        inline float getMaxHP() const { return this->maxHP; }

        inline void damage(float damage)
        {
            this->hp -= std::min(damage, this->hp);
        }

        inline void heal(float heal)
        {
            this->hp += heal;
            if ( this->hp > this->maxHP )
                this->hp = this->maxHP;
        }

        inline bool isDead() const { return this->hp <= 0; }

        inline PlayerDirection getDir() const { return this->dir; }

    public:
        bool checkCollision(const sf::Vector2f &newPos);

        void updateHitbox();
        void updateAnimation(sf::Time &dt);

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
        virtual Json toJson() const override;
        virtual void fromJson(const Json &json) override;
    };
}