/**
 *  File: PlayerGUI.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 08:46:10
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 16:16:53
 *  Description: Player GUI Class
 */

#include "../Player.hpp"
#include "GUI.hpp"

namespace Dungeon
{

    class PlayerGUI : public GUI
    {
    private:
        Player *player;
        sf::Font font;
        sf::Text hp;
        sf::Text dead;

    public:
        PlayerGUI(Player *player);

    public:
        inline void setPlayer(Player *player) { this->player = player; }

    public:
        virtual void init() override;
        virtual void logic(KeyInput *keyInput, sf::Time &dt,
                           sf::View &view) override;
        virtual void render(sf::RenderWindow &window) override;
    };

};