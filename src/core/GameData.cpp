/**
 *  File: GameData.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/06/12 15:06:42
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/06/12 15:50:15
 *  Description: Game Data Class
 */

#include "core/GameData.hpp"
#include "core/File.hpp"

#include <fstream>

using namespace Dungeon;

GameData::GameData() {}

bool GameData::loadFile(std::string filename)
{
    std::ifstream ifs;
    std::string path = (File::getDataPath() / filename).string();

    ifs.open(path);
    if ( !ifs.is_open() )
        return false;

    this->j = Json::parse(ifs);
    if ( !this->j.is_array() )
        return false;

    this->valid = true;
    return true;
}

size_t GameData::getLevelNum() const { return this->j.size(); }

Json GameData::getLevelData(size_t level) const { return this->j[level]; }
