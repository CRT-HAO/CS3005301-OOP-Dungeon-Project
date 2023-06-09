/**
 *  File: Camera.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:06:30
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/09 22:36:44
 *  Description: Camera Class
 */

#pragma once

#include "Object.hpp"
#include "Player.hpp"

#include <SFML/Graphics.hpp>

namespace Dungeon
{

    class Camera : public Object
    {
    private:
        sf::Vector2f pos;
        sf::Vector2f targetPos;
        bool smoothMove{true};
        float smoothMoveSpeed{2.5};

    public:
        Camera() {}
        Camera(const sf::Vector2f &pos) : pos(pos) {}

    public:
        void setPos(const sf::Vector2f &pos);
        void focus(Player *player);

    public:
        void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
        void updateView(sf::View &view);
    };

}