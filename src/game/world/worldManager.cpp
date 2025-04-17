#include "../include/worldManager.hpp"
#include "worldManager.hpp"

WorldManager::WorldManager() {
    // Constructor implementation (if needed)
    helper.log(3, "WorldManager constructor");
}

void WorldManager::addWorld(const World& world) {
    worlds.push_back(world);
}

void WorldManager::addWorld(std::string name, int size, int seed)
{
    helper.log(3, "WorldMananger: Adding world: " + name);
}

World& WorldManager::getWorld(int index) {
    if (index < 0 || index >= worlds.size()) {
        throw std::out_of_range("Index out of range");
    }
    return worlds[index];
}

void WorldManager::removeWorld(int index) {
    if (index < 0 || index >= worlds.size()) {
        throw std::out_of_range("Index out of range");
    }
    worlds.erase(worlds.begin() + index);
}

int WorldManager::getWorldCount() const {
    return worlds.size();
}

void WorldManager::updateWorld(World world)
{
    world.update();
}