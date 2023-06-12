/**
 *  File: GameData.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 15:03:01
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 16:33:29
 *  Description: Game Data Class
 */

#pragma once

#include "../lib/json.hpp"

using Json = nlohmann::json;

namespace Dungeon
{

    class GameData
    {
    private:
        Json j;
        bool valid{false};

    public:
        GameData();

    public:
        inline const Json &getJson() const { return this->j; };
        bool loadFile(std::string filename = "game.json");
        bool loadJson(const Json &json);

    public:
        size_t getLevelNum() const;
        Json getLevelData(size_t level) const;
    };

}