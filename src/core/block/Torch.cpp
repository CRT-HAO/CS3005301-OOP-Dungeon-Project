/**
 *  File: Torch.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/06 23:28:45
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/07 11:16:09
 *  Description: Torch Block Class
 */

#include "core/block/Torch.hpp"
#include "core/File.hpp"

using namespace Dungeon;

Torch::Torch() {}

Torch::Torch(const sf::Vector2f &pos)
{
    this->setPos(pos);
}

void Torch::init()
{
    int spriteSize = 8;
    this->texture.loadFromFile(fs::path(File::getResPath() / "images/spritesheet_torch.png").string());
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(0, spriteSize, spriteSize, spriteSize));
    sprite.setScale(this->getSize() / spriteSize, this->getSize() / spriteSize);
    this->setSolid(true);

    this->animationManager.addAnimation("Flickering", 0.07, 0, 0, 2, 0, spriteSize, spriteSize);
}

void Torch::logic(KeyInput *keyInput, sf::Time &dt)
{
    this->animationManager.play("Flickering", dt);
}

void Torch::render(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}