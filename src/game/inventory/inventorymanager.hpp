#pragma once

#include "inventory.hpp"

class InventoryManager
{
public:
    InventoryManager();
    //Inventory playerInventory;
    //Inventory storageInventory;

    std::vector<Inventory> inventoryList;

    Inventory makeInventory(std::string inventoryName);
    void addItem(Inventory inventory, Item item);
    void removeItem(Inventory inventory, Item item);
    void moveItem(Inventory fromInv, Inventory toInv, Item item);

    void printInventory(Inventory inventory);
};
