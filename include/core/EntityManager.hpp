/**
 *  File: EntityManager.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/30 10:21:55
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 06:40:43
 *  Description: Entity Manager
 */

#pragma once

#include "Entity.hpp"

#include <unordered_set>

namespace Dungeon
{

    class EntityManager : public Entity
    {
    private:
        std::unordered_set<Entity *> entities;

    public:
        EntityManager();

    public:
        void addEntity(Entity *e);
        void removeEntity(Entity *e);
        void clear();

        const std::unordered_set<Entity *> &getEntities() const;
        bool intersects(const sf::FloatRect &frect);

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
        virtual Json toJson() const override;
    };

}