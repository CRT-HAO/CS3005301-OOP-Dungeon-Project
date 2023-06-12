/**
 *  File: Ground.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 23:28:45
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 07:59:43
 *  Description: Ground Block Class
 */

#include "core/block/Ground.hpp"
#include "core/File.hpp"
#include "core/block/Block.hpp"

using namespace Dungeon;

Ground::Ground() { this->textureType = rand() % 4; }

Ground::Ground(const sf::Vector2f &pos)
{
    this->textureType = rand() % 4;
    this->setPos(pos);
}

void Ground::init()
{
    int spriteSize = 8;
    this->texture.loadFromFile(
        fs::path(File::getResPath() / "images/tilemap.png").string());
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(
        sf::IntRect(this->textureType * spriteSize, 0, spriteSize, spriteSize));
    sprite.setScale(GRID_SIZE / spriteSize, GRID_SIZE / spriteSize);
}

void Ground::logic(KeyInput *keyInput, sf::Time &dt) {}

void Ground::render(sf::RenderWindow &window) { window.draw(this->sprite); }

Json Ground::toJson() const
{
    Json j;
    j["type"] = "Ground";
    j.update(Block::toJson());
    return j;
}
