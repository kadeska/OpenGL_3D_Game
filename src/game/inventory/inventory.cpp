#include "inventory.hpp"
#include "../include/helper.hpp"
// #include "items/item.hpp"


Inventory::Inventory() : baseItem(0, ""), inventory() {
    helper.log(3, "Inventory constructor");
}
Inventory::Inventory(std::string inventoryName) : baseItem(0, "BASE"){}

Item Inventory::getBaseItem() const
{
    return baseItem;
}

void Inventory::setBaseItem(const Item &newBaseItem)
{
    baseItem = newBaseItem;
}

void Inventory::addItem(Item item)
{
    inventory.push_back(item);
}

void Inventory::addNewItem(std::string itemName, int itemID)
{
    inventory.push_back(Item(itemID, itemName));
}

Item Inventory::getItemByID(int id)
{
    helper.log(3, "test1");
    helper.log(3, std::to_string(inventory.at(id).getItem_ID()));
    helper.log(3, "test2");
    helper.log(3, inventory.at(id).getItem_name());
    return inventory.at(id);
}

std::vector<Item>& Inventory::getItems() {
    return inventory;
}

void Inventory::setInventory(const std::vector<Item> &newInventory)
{
    inventory = newInventory;
}
