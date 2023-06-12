/**
 *  File: World.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:28:39
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 15:24:31
 *  Description: World Class
 */

#pragma once

#include "CreatureManager.hpp"
#include "Object.hpp"
#include "Room.hpp"
#include "core/CreatureManager.hpp"

#include <vector>

namespace Dungeon
{

    class World : public Object
    {
    private:
        Player *player;
        std::vector<Room *> rooms;
        CreatureManager creatureManager;

    public:
        World(Player *player);

    public:
        inline CreatureManager &getCreatureManager()
        {
            return this->creatureManager;
        }

    public:
        inline void setPlayer(Player *player) { this->player = player; }
        inline const CreatureManager &getCreatureManager() const
        {
            return this->creatureManager;
        }

    public:
        const std::vector<Room *> &getRooms();
        void clear();
        void addRoom(Room *room);
        void addCreature(Creature *creator);
        bool intersects(const sf::FloatRect &frect);

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt) override;
        virtual void render(sf::RenderWindow &window) override;
        virtual Json toJson() const override;
        virtual void fromJson(const Json &json) override;
    };

}