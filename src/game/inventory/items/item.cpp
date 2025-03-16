#include "item.hpp"
#include "../include/helper.hpp"

Item::Item(int ID, std::string name) : item_ID(ID), item_name(name)

{
    helper.log(3, "Item constructor");
    item_ID = ID;
    item_name = name;
}

std::string Item::getItem_name() const
{
    return item_name;
}

void Item::setItem_name(const std::string &newItem_name)
{
    item_name = newItem_name;
}

int Item::getItem_ID() const
{
    return item_ID;
}

void Item::setItem_ID(int newItem_ID)
{
    item_ID = newItem_ID;
}
