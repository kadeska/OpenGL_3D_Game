#pragma once

#include "inventory.hpp"

class InventoryManager
{
public:
    InventoryManager();
    Inventory playerInventory;
    Inventory storageInventory;

    std::vector<Inventory> inventoryList;
};
