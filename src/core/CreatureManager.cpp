#include "core/CreatureManager.hpp"
#include "core/EntityManager.hpp"
#include <unordered_set>

using namespace Dungeon;

CreatureManager::CreatureManager() : EntityManager() {}

void CreatureManager::addCreature(Creature *creature)
{
    this->addEntity(creature);
}

std::unordered_set<Creature *> CreatureManager::getCreatures() const
{
    std::unordered_set<Creature *> r;
    for ( const auto &e : this->getEntities() )
        r.insert(dynamic_cast<Creature *>(e));
    return r;
}

void CreatureManager::init() { return EntityManager::init(); }

void CreatureManager::logic(KeyInput *keyInput, sf::Time &dt)
{
    std::unordered_set<Creature *> remove;
    for ( auto &e : this->getEntities() )
    {
        Creature *c = static_cast<Creature *>(e);
        if ( c->isDead() )
        {
            remove.insert(c);
            // this->removeEntity((Entity *)e);
        }
    }

    for ( auto &c : remove )
        this->removeEntity(c);

    return EntityManager::logic(keyInput, dt);
}

void CreatureManager::render(sf::RenderWindow &window)
{
    return EntityManager::render(window);
}