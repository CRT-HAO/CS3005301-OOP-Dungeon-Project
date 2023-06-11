#include "core/CreatureManager.hpp"
#include "core/EntityManager.hpp"

using namespace Dungeon;

CreatureManager::CreatureManager() : EntityManager() {}

void CreatureManager::addCreature(Creature *creature)
{
    this->addEntity(creature);
}