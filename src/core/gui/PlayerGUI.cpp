/**
 *  File: PlayerGUI.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 08:49:39
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 09:55:13
 *  Description: Player GUI Class
 */

#include "core/gui/PlayerGUI.hpp"
#include "core/File.hpp"

#include <SFML/System/Vector2.hpp>
#include <string>

using namespace Dungeon;

PlayerGUI::PlayerGUI(Player *player) : player(player) {}

void PlayerGUI::init()
{
    this->font.loadFromFile(
        fs::path(File::getResPath() / "fonts/rpg-font.ttf").string());

    this->hp.setFont(this->font);
    this->hp.setCharacterSize(24);
    this->hp.setFillColor(sf::Color::Red);
    this->hp.setStyle(sf::Text::Bold);

    this->dead.setFont(this->font);
    this->dead.setCharacterSize(80);
    this->dead.setFillColor(sf::Color::Red);
    this->dead.setStyle(sf::Text::Bold);
}

void PlayerGUI::logic(KeyInput *keyInput, sf::Time &dt, sf::View &view)
{
    sf::Vector2f origin(view.getCenter().x - view.getSize().x / 2,
                        view.getCenter().y - view.getSize().y / 2);

    std::string hpText =
        "HP " + std::to_string(int(round(this->player->getHP()))) + "/" +
        std::to_string(int(round(this->player->getMaxHP())));
    this->hp.setString(hpText);
    this->hp.setPosition(origin + sf::Vector2f(10, 10));

    if ( this->player->isDead() )
        this->dead.setString("You dead!");
    else
        this->dead.setString("");

    this->dead.setPosition(view.getCenter().x, view.getCenter().y);
}

void PlayerGUI::render(sf::RenderWindow &window)
{
    window.draw(this->hp);
    window.draw(this->dead);
}