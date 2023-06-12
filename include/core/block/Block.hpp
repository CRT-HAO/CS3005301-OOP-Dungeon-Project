/**
 *  File: Block.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/29 23:15:11
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 07:03:45
 *  Description: Block Class
 */

#pragma once

#include "../../Config.hpp"
#include "../Entity.hpp"

#include <SFML/Graphics.hpp>

namespace Dungeon
{

    class Block : public Entity
    {
    private:
        bool solid{false};
        size_t size{GRID_SIZE};

    public:
        inline const sf::Vector2f &getPos() const
        {
            return this->sprite.getPosition();
        }
        inline void setPos(const sf::Vector2f &pos)
        {
            this->sprite.setPosition(pos);
        }
        inline bool isSolid() const { return this->solid; }

        inline void setSolid(bool solid)
        {
            this->solid = solid;
            if ( solid )
            {
                this->setHitBox(this->sprite.getGlobalBounds());
            }
            else
            {
                this->setHitBox(sf::FloatRect(0, 0, 0, 0));
            }
        }

        inline size_t getSize() const { return this->size; }
        inline void setSize(size_t size) { this->size = size; };

    public:
        virtual Json toJson() const override;
        virtual void fromJson(const Json &json) override;
    };
}