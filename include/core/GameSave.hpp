/**
 *  File: GameSave.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 15:03:01
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 16:49:44
 *  Description: Game Save Class
 */

#pragma once

#include "../lib/json.hpp"
#include "Camera.hpp"
#include "GameData.hpp"
#include "World.hpp"

using Json = nlohmann::json;

namespace Dungeon
{
    // Forward declarations
    class Game;

    class GameSave
    {
    private:
        Json j;
        bool valid{false};

    public:
        GameSave();

    public:
        inline const Json &getJson() const { return this->j; };
        bool loadFile(std::string filename = "save.json");
        bool saveFile(std::string filename = "save.json");
        void fromInstance(Game *game, const GameData &data, size_t level);

    public:
        Json getGameJson() const;
        Json getGameDataJson() const;
        size_t getLevel() const;
    };

}