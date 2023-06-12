/**
 *  File: Animation.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/07 02:14:09
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 17:09:17
 *  Description: Animation Class
 */

#pragma once

#include <SFML/Graphics.hpp>

namespace Dungeon
{

    class Animation
    {
    public:
        // Variables
        sf::Sprite &sprite;
        sf::Texture &textureSheet;
        float animationTimer;
        float timer;
        bool done;
        int width;
        int height;
        sf::IntRect startRect;
        sf::IntRect currentRect;
        sf::IntRect endRect;

        Animation(sf::Sprite &sprite, sf::Texture &texture_sheet,
                  float animation_timer, int start_frame_x, int start_frame_y,
                  int frames_x, int frames_y, int width, int height)
            : sprite(sprite), textureSheet(texture_sheet),
              animationTimer(animation_timer), timer(0.f), done(false),
              width(width), height(height)
        {
            this->startRect = sf::IntRect(
                start_frame_x * width, start_frame_y * height, width, height);
            this->currentRect = this->startRect;
            this->endRect =
                sf::IntRect(frames_x * width, frames_y * height, width, height);

            this->sprite.setTexture(this->textureSheet, true);
            this->sprite.setTextureRect(this->startRect);
        }

        // Accessor
        const bool &isDone() const { return this->done; }

        // Functions
        const bool &play(sf::Time &dt)
        {
            // Update timer
            this->done = false;
            this->timer += dt.asSeconds();
            if ( this->timer >= this->animationTimer )
            {
                // reset timer
                this->timer = 0.f;

                // Animate
                // if ( this->currentRect != this->endRect )
                if ( this->currentRect.left < this->endRect.left )
                {
                    this->currentRect.left += this->width;
                }
                else // Reset
                {
                    this->currentRect.left = this->startRect.left;
                    this->done = true;
                }

                this->sprite.setTextureRect(this->currentRect);
            }

            return this->done;
        }

        const bool &play(sf::Time &dt, float mod_percent)
        {
            // Update timer
            if ( mod_percent < 0.5f )
                mod_percent = 0.5f;

            this->done = false;
            this->timer += mod_percent * 100.f * dt.asSeconds();
            if ( this->timer >= this->animationTimer )
            {
                // reset timer
                this->timer = 0.f;

                // Animate
                // if ( this->currentRect != this->endRect )
                if ( this->currentRect.left < this->endRect.left )
                {
                    this->currentRect.left += this->width;
                }
                else // Reset
                {
                    this->currentRect.left = this->startRect.left;
                    this->done = true;
                }

                this->sprite.setTextureRect(this->currentRect);
            }

            return this->done;
        }

        void reset()
        {
            this->timer = this->animationTimer;
            this->currentRect = this->startRect;
        }
    };

}