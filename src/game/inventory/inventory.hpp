#pragma once
#include "items/item.hpp"

#include <string>
#include <map>
#include <vector>

class Inventory
{
public:
    Inventory();
    Inventory(std::string inventoryName);
    std::vector<Item> inventory;
    std::vector<Item> &getItems();

    Item baseItem;

    void setInventory(const std::vector<Item> &newInventory);
    Item getBaseItem() const;
    void setBaseItem(const Item &newBaseItem);

    void addItem(Item item);
    void addNewItem(std::string itemName, int itemID);

    Item getItemByID(int id);

};
