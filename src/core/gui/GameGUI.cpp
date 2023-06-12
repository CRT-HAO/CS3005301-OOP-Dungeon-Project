/**
 *  File: GameGUI.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 08:49:39
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 15:37:34
 *  Description: Player GUI Class
 */

#include "core/gui/GameGUI.hpp"
#include "core/File.hpp"

#include <SFML/System/Vector2.hpp>
#include <string>

using namespace Dungeon;

GameGUI::GameGUI() {}

void GameGUI::init()
{
    this->font.loadFromFile(
        fs::path(File::getResPath() / "fonts/rpg-font.ttf").string());

    this->creatureNum.setFont(this->font);
    this->creatureNum.setCharacterSize(24);
    this->creatureNum.setFillColor(sf::Color::White);
    this->creatureNum.setStyle(sf::Text::Bold);
}

void GameGUI::logic(KeyInput *keyInput, sf::Time &dt, sf::View &view)
{
    sf::Vector2f origin(view.getCenter().x + view.getSize().x / 2,
                        view.getCenter().y - view.getSize().y / 2);

    std::string text = "Creature " + std::to_string(this->currentCreatureNum);
    this->creatureNum.setString(text);
    sf::FloatRect box = this->creatureNum.getGlobalBounds();
    this->creatureNum.setPosition(origin.x - box.width - 10, origin.y + 10);
}

void GameGUI::render(sf::RenderWindow &window)
{
    window.draw(this->creatureNum);
}