#pragma once
#include <vector>

#include "item.hpp"

class Inventory {
    public: 
        Inventory();
        Inventory(int maxSize);
        std::vector<item> items_in_inventory; // vector of items
        bool attached = false; // If the inventory is attached to an entity.
        bool isActive = false; // If the inventory is active/currently in use.
        bool isFull = false; // If the inventory is full.
        bool isEmpty = true; // If the inventory is empty.
        // size is the number of slots in the inventory.
        int maxSize = 20; // Maximum size of the inventory.
        int currentSize = 0; // Current size of the inventory.
        int itemCount = 0; // Number of items in the inventory.

        std::vector<item> getItems(); // Get the items in the inventory.
        void addItem(item& newItem); // Add an item to the inventory.
        void removeItem(int itemID); // Remove an item from the inventory by ID.
        void clearInventory(); // Clear the inventory.
        bool isInventoryFull(); // Check if the inventory is full.
        bool isInventoryEmpty(); // Check if the inventory is empty.
        void setInventorySize(int newSize); // Set the size of the inventory.
        int getInventorySize(); // Get the size of the inventory.
        void printInventory(); // Print the inventory to the console.
        void attachInventory(); // Attach the inventory to an entity.
        void detachInventory(); // Detach the inventory from an entity.
        bool isInventoryAttached(); // Check if the inventory is attached to an entity.
        bool isInventoryActive(); // Check if the inventory is active.
        void setInventoryActive(bool active); // Set the inventory active or inactive.
        void setInventoryFull(bool full); // Set the inventory full or not.
        void setInventoryEmpty(bool empty); // Set the inventory empty or not.
        int getItemCount(); // Get the number of items in the inventory.


};