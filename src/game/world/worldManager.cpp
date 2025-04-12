#include "../include/worldManager.hpp"
#include "worldManager.hpp"

WorldManager::WorldManager() {
    // Constructor implementation (if needed)
}

void WorldManager::addWorld(const World& world) {
    worlds.push_back(world);
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