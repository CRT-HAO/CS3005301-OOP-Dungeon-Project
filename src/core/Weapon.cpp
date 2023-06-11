/**
 *  File: Weapon.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 00:41:38
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 03:26:48
 *  Description: Weapon Class
 */

#include "core/Weapon.hpp"
#include "Config.hpp"
#include "SFML/System/Vector2.hpp"
#include "core/File.hpp"
#include "core/Player.hpp"
#include "core/World.hpp"

using namespace Dungeon;

Weapon::Weapon(World *world, Player *player, float damage, float attackInterval)
    : world(world), player(player), damage(damage),
      attackInterval(attackInterval)
{
}

void Weapon::attack()
{
    for ( auto &c : this->world->getCreatureManager().getCreatures() )
    {
        if ( c->getHitBox().intersects(this->player->getHitBox()) )
        {
            c->damage(this->damage);
            std::cout << "attack" << std::endl;
        }
    }
}

void Weapon::init()
{
    int spriteSize = 8;
    this->texture.loadFromFile(
        fs::path(File::getResPath() / "images/spritesheet_player_attack.png")
            .string());
    this->sprite.setTexture(this->texture);
    sprite.setScale(GRID_SIZE / spriteSize, GRID_SIZE / spriteSize);

    this->animationManager.addAnimation("Idle", 0, 0, 0, 0, 0, 0, 0);
    this->animationManager.addAnimation("Attacking_Up", 0.01, 0, 0, 6, 0,
                                        spriteSize, spriteSize);
    this->animationManager.addAnimation("Attacking_Right", 0.01, 7, 0, 13, 0,
                                        spriteSize, spriteSize);
    this->animationManager.addAnimation("Attacking_Down", 0.01, 14, 0, 20, 0,
                                        spriteSize, spriteSize);
    this->animationManager.addAnimation("Attacking_Left", 0.01, 21, 0, 27, 0,
                                        spriteSize, spriteSize);
}

void Weapon::logic(KeyInput *keyInput, sf::Time &dt)
{
    sf::FloatRect playerRect = this->player->getGlobalBounds();
    sf::Vector2f newPos(playerRect.left + playerRect.width, playerRect.top);

    PlayerDirection dir = this->player->getDir();
    static PlayerDirection lastDir = dir;

    std::string animationName;

    switch ( dir )
    {
    case PlayerDirection::Left:
        newPos.x = playerRect.left - playerRect.width;
        newPos.y = playerRect.top;
        animationName = "Attacking_Left";
        break;

    case PlayerDirection::Right:
        newPos.x = playerRect.left + playerRect.width;
        newPos.y = playerRect.top;
        animationName = "Attacking_Right";
        break;

    case PlayerDirection::Up:
        newPos.x = playerRect.left;
        newPos.y = playerRect.top - playerRect.height;
        animationName = "Attacking_Up";
        break;

    case PlayerDirection::Down:
        newPos.x = playerRect.left;
        newPos.y = playerRect.top + playerRect.height;
        animationName = "Attacking_Down";
        break;
    }

    this->sprite.setPosition(newPos);

    if ( keyInput->isAttack() && !attacking )
    {
        this->attack();
        this->animationManager.play(animationName, dt);
        this->attackTime = sf::Time::Zero;
        attacking = true;
    }
    else
    {
        if ( attacking &&
             (!this->animationManager.isDone(animationName) || lastDir != dir) )
        {
            this->animationManager.play(animationName, dt);
        }
        else
        {
            this->animationManager.play("Idle", dt);
        }

        this->attackTime += dt;
    }

    if ( attacking )
    {
        if ( this->attackTime.asSeconds() > this->attackInterval )
            attacking = false;
    }

    lastDir = dir;
}

void Weapon::render(sf::RenderWindow &window) { window.draw(this->sprite); }