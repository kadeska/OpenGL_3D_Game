#include "inventory.hpp"
#include <iostream>

Inventory::Inventory()
{
}

Inventory::Inventory(int maxSize) : maxSize(maxSize)
{
    std::cout << "testing inventory" << std::endl;
    items_in_inventory.reserve(maxSize); // Reserve space for the maximum size
}