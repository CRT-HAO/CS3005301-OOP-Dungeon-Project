/**
 *  File: Heal.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:29:15
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 10:34:19
 *  Description: Heal Block Class
 */

#pragma once

#include "Block.hpp"

#include "../AnimationManager.hpp"

#include <SFML/Graphics.hpp>

namespace Dungeon
{
    // Forward declarations
    class Player;

    class Heal : public Block
    {
    private:
        Player *player;
        AnimationManager animationManager{this->sprite, this->texture};
        float healHP;

    public:
        Heal(Player *player, float healHP = 20);
        Heal(Player *player, const sf::Vector2f &pos, float healHP = 20);

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
        virtual Json toJson() const override;
        virtual void fromJson(const Json &json) override;
    };
}