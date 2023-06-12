/**
 *  File: AnimationManager.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/07 02:32:06
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 17:25:11
 *  Description: Animation Manager
 */

#pragma once

#include "Animation.hpp"

#include <map>

namespace Dungeon
{

    class AnimationManager
    {
    private:
        sf::Sprite &sprite;
        sf::Texture &textureSheet;
        std::map<std::string, Animation *> animations;
        Animation *lastAnimation;

    public:
        AnimationManager(sf::Sprite &sprite, sf::Texture &texture_sheet);
        virtual ~AnimationManager();

    public:
        const bool &isDone(const std::string &key);

        void addAnimation(const std::string &key, float animation_timer,
                          int start_frame_x, int start_frame_y, int frames_x,
                          int frames_y, int width, int height);

        const bool &play(const std::string key, sf::Time &dt);
    };

}