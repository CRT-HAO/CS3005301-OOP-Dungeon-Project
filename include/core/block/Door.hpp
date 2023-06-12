/**
 *  File: Door.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:29:15
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 06:38:00
 *  Description: Door Block Class
 */

#pragma once

#include "../Player.hpp"
#include "../World.hpp"
#include "Block.hpp"

#include <SFML/Graphics.hpp>

namespace Dungeon
{

    class Door : public Block
    {
    private:
        Player *player;
        bool closed;
        sf::IntRect textureClosed;
        sf::IntRect textureOpened;
        sf::IntRect textureTest;
        bool playerApproach;

    public:
        Door(Player *player);
        Door(Player *player, const sf::Vector2f &pos);

    public:
        inline bool isClosed() const { return this->closed; }
        inline void setClosed(bool value) { this->closed = value; }

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
        virtual Json toJson() const override;
        virtual void fromJson(const Json &json) override;
    };

}