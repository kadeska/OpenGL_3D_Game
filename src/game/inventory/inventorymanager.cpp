#include "inventorymanager.hpp"
#include "../include/helper.hpp"

InventoryManager::InventoryManager()
{
    helper.log(3, "Inventory manager constructor");
    // playerInventory.getItems().emplace_back(Item(std::rand(), "player_sword"));
    // storageInventory.getItems().emplace_back(Item(std::rand(), "storage_item"));
    // inventoryList.emplace_back(playerInventory);
    // inventoryList.emplace_back(storageInventory);

    // helper.log(3, std::to_string(inventoryList.size()));


}

Inventory InventoryManager::makeInventory(std::string inventoryName)
{
    return Inventory(inventoryName);
}

void InventoryManager::addItem(Inventory inventory, Item item)
{
    inventory.addItem(item);
}

void InventoryManager::removeItem(Inventory inventory, Item item)
{

}

void InventoryManager::moveItem(Inventory fromInv, Inventory toInv, Item item)
{

}

void InventoryManager::printInventory(Inventory inventory)
{
    // Print inventory for testing
    helper.log(3, "Your inventory: ");
    for (Item& item : inventory.getItems()) {
        helper.log(3, "Item ID: " + std::to_string(item.getItem_ID()));
        helper.log(3, "Item Name: " + item.getItem_name());
    }
}
