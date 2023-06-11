/**
 *  File: Entity.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 23:00:06
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/11 15:24:10
 *  Description: Entity Class
 */

#pragma once

#include "Object.hpp"

#include <SFML/Graphics.hpp>

namespace Dungeon
{

    class Entity : public Object
    {
    protected:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::FloatRect hitbox;
        int zIndex{0};

    public:
        inline void setPos(const sf::Vector2f &pos)
        {
            this->sprite.setPosition(pos);
        };

        inline const sf::Vector2f &getPos() const
        {
            return this->sprite.getPosition();
        };

        inline sf::Vector2f getCenter() const
        {
            return (this->sprite.getPosition() +
                    sf::Vector2f(this->sprite.getGlobalBounds().width / 2.f,
                                 this->sprite.getGlobalBounds().height / 2.f));
        };

        inline void move(const sf::Vector2f &offset)
        {
            this->sprite.move(offset);
        }

        inline int getZIndex() const { return this->zIndex; }

        inline void setZIndex(int ziIndex) { this->zIndex = ziIndex; }

        inline sf::FloatRect getGlobalBounds() const
        {
            return this->sprite.getGlobalBounds();
        }

        inline const sf::FloatRect &getHitBox() const { return this->hitbox; }

        inline void setHitBox(const sf::FloatRect &hitbox)
        {
            this->hitbox = hitbox;
        }

        bool intersects(const sf::FloatRect &frect);
    };
}