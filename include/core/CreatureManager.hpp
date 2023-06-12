/**
 *  File: CreatureManager.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/11 15:28:23
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 08:12:46
 *  Description: Creature Manager Class
 */

#pragma once

#include "EntityManager.hpp"
#include "creature/Creature.hpp"

#include <unordered_set>

namespace Dungeon
{

    class CreatureManager : public EntityManager
    {
    public:
        CreatureManager();

    public:
        void addCreature(Creature *creature);
        std::unordered_set<Creature *> getCreatures() const;

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
        virtual Json toJson() const override;
        virtual void fromJson(const Json &json) override;
    };

}