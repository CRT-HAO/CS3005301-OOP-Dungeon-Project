/**
 *  File: GameGUI.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 08:46:10
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 15:21:17
 *  Description: Player GUI Class
 */

#include "../Player.hpp"
#include "GUI.hpp"

namespace Dungeon
{

    class GameGUI : public GUI
    {
    private:
        sf::Font font;
        sf::Text creatureNum;
        size_t currentCreatureNum{0};

    public:
        GameGUI();

    public:
        inline void setCurrentCreatureNum(size_t num)
        {
            this->currentCreatureNum = num;
        }

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt,
                           sf::View &view) override;
        virtual void render(sf::RenderWindow &window) override;
    };

};