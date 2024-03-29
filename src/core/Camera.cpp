/**
 *  File: Camera.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/05 23:09:20
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 06:49:09
 *  Description: Camera Class
 */

#include "core/Camera.hpp"

#include "Config.hpp"

using namespace Dungeon;

void Camera::setPos(const sf::Vector2f &pos) { this->targetPos = pos; }

void Camera::focus(Player *player) { this->targetPos = player->getCenter(); }

void Camera::init() {}

void Camera::logic(KeyInput *keyInput, sf::Time &dt)
{
    if ( !this->smoothMove )
    {
        this->pos = this->targetPos;
    }
    else
    {
        sf::Vector2f diff = this->targetPos - this->pos;
        double x = diff.x * this->smoothMoveSpeed * dt.asSeconds();
        double y = diff.y * this->smoothMoveSpeed * dt.asSeconds();
        this->pos.x += x;
        this->pos.y += y;
    }
}

void Camera::render(sf::RenderWindow &window) {}

void Camera::updateView(sf::View &view) { view.setCenter(this->pos); }

Json Camera::toJson() const
{
    Json j;
    j["pos"] = {
        {"x", this->pos.x},
        {"y", this->pos.y},
    };
    j["target_pos"] = {
        {"x", this->targetPos.x},
        {"y", this->targetPos.y},
    };
    j["smooth_move"] = this->smoothMove;
    j["smooth_move_speed"] = this->smoothMoveSpeed;
    return j;
}

void Camera::fromJson(const Json &json)
{
    this->pos.x = json["pos"]["x"].get<float>();
    this->pos.y = json["pos"]["y"].get<float>();
    this->targetPos.x = json["target_pos"]["x"].get<float>();
    this->targetPos.y = json["target_pos"]["y"].get<float>();
    this->smoothMove = json["smooth_move"].get<bool>();
    this->smoothMoveSpeed = json["smooth_move_speed"].get<float>();
}