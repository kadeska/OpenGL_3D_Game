#include "inventorymanager.hpp"
#include "../include/helper.hpp"

InventoryManager::InventoryManager()
    : playerInventory(Inventory("player")),
    storageInventory(Inventory("storage")),
    inventoryList()
{
    helper.log(3, "Inventory manager constructor");
    playerInventory.getItems().emplace_back(Item(std::rand(), "player_sword"));
    storageInventory.getItems().emplace_back(Item(std::rand(), "storage_item"));
    inventoryList.emplace_back(playerInventory);
    inventoryList.emplace_back(storageInventory);

    helper.log(3, std::to_string(inventoryList.size()));

    // Print inventory for testing
    helper.log(3, "Your inventory: ");
    for (Inventory& inv : inventoryList) {
        helper.log(3, "Inventory:");
        for (Item& item : inv.getItems()) {
            helper.log(3, "Item ID: " + std::to_string(item.getItem_ID()));
            helper.log(3, "Item Name: " + item.getItem_name());
        }
    }
}
