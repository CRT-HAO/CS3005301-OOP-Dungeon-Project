/**
 *  File: GUIManager.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 08:37:16
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 09:36:58
 *  Description: GUI Manager Class
 */

#pragma once

#include "gui/GUI.hpp"

#include <unordered_set>

namespace Dungeon
{

    class GUIManager : public GUI
    {
    private:
        std::unordered_set<GUI *> gui;

    public:
        GUIManager();

    public:
        void addGUI(GUI *gui);
        void removeGUI(GUI *gui);
        void clear();

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt,
                           sf::View &view) override;
        virtual void render(sf::RenderWindow &window) override;
    };

}