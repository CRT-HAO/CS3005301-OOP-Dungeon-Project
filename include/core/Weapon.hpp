/**
 *  File: Weapon.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/11 18:03:25
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 08:23:46
 *  Description: Weapon Class
 */

#pragma once

#include "AnimationManager.hpp"
#include "Entity.hpp"

namespace Dungeon
{
    // Forward declarations
    class World;
    class Player;

    class Weapon : public Object
    {
    private:
        World *world;
        Player *player;
        float damage;
        float attackInterval;
        sf::Time attackTime;
        bool attacking{false};
        sf::Texture texture;
        sf::Sprite sprite;
        AnimationManager animationManager{sprite, texture};

    public:
        Weapon(World *world, Player *player, float damage = 50,
               float attackInterval = 0.2);

    public:
        inline void setWorld(World *world) { this->world = world; }

    public:
        void attack();

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
        virtual Json toJson() const override;
        virtual void fromJson(const Json &json) override;
    };

}