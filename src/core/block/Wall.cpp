/**
 *  File: Wall.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 23:28:45
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 08:00:10
 *  Description: Wall Block Class
 */

#include "core/block/Wall.hpp"
#include "core/File.hpp"

using namespace Dungeon;

Wall::Wall() {}

Wall::Wall(const sf::Vector2f &pos) { this->setPos(pos); }

void Wall::init()
{
    int spriteSize = 8;
    this->texture.loadFromFile(
        fs::path(File::getResPath() / "images/tilemap.png").string());
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(
        sf::IntRect(0, spriteSize, spriteSize, spriteSize));
    sprite.setScale(GRID_SIZE / spriteSize, GRID_SIZE / spriteSize);
    this->setSolid(true);
}

void Wall::logic(KeyInput *keyInput, sf::Time &dt) {}

void Wall::render(sf::RenderWindow &window) { window.draw(this->sprite); }

Json Wall::toJson() const
{
    Json j;
    j["type"] = "Wall";
    j.update(Block::toJson());
    return j;
}
