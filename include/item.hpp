#pragma once
#include "string"

class Item
{
public:
    Item(int ID, std::string name);
    int item_ID;
    std::string item_name;

    int getItem_ID() const;
    void setItem_ID(int newItem_ID);
    std::string getItem_name() const;
    void setItem_name(const std::string &newItem_name);
};
