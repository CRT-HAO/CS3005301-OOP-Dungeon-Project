/**
 *  File: World.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:28:39
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/11 15:35:26
 *  Description: World Class
 */

#pragma once

#include "CreatureManager.hpp"
#include "Object.hpp"
#include "Room.hpp"

#include <vector>

namespace Dungeon
{

    class World : public Object
    {
    private:
        std::vector<Room *> rooms;
        CreatureManager creatorManager;

    public:
        World();

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
    };

}