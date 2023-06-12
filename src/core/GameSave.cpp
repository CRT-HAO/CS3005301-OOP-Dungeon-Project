/**
 *  File: GameSave.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 15:06:42
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 16:50:40
 *  Description: Game Data Class
 */

#include "core/GameSave.hpp"
#include "core/File.hpp"
#include "core/Game.hpp"

#include <fstream>

using namespace Dungeon;

GameSave::GameSave() {}

bool GameSave::loadFile(std::string filename)
{
    std::ifstream ifs;
    std::string path = (File::getDataPath() / filename).string();

    ifs.open(path);
    if ( !ifs.is_open() )
        return false;

    this->j = Json::parse(ifs);

    this->valid = true;
    return true;
}

bool GameSave::saveFile(std::string filename)
{
    std::ofstream ofs;
    std::string path = (File::getDataPath() / filename).string();

    ofs.open(path);
    if ( !ofs.is_open() )
        return false;

    if ( !(ofs << this->j) )
        return false;

    return true;
}

void GameSave::fromInstance(Game *game, const GameData &data, size_t level)
{
    this->j.clear();
    j["game"] = game->toJson();
    j["game_data"] = data.getJson();
    j["level"] = level;
}

Json GameSave::getGameJson() const { return this->j["game"]; }
Json GameSave::getGameDataJson() const { return this->j["game_data"]; }
size_t GameSave::getLevel() const { return this->j["level"]; }
