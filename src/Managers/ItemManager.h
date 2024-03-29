#ifndef ITEM_MANAGER_H_
#define ITEM_MANAGER_H_
#include <memory>
#include <vector>
#include <string>
class BaseDescription;
class Equipable;
class Consumable;
class Item;
class ItemDescription;

/**
 * Factory class that creates items and item groups
 * randomly which scale based on the level inputted
 */
class ItemManager
{
    const std::vector<std::string> equipNames = {
        "Sword",
        "Shield",
        "Helmet",
        "Bow",
        "Staff",
        "Greaves",
        "Chestplate",
        "Gun",
        "Boots"};
    const std::vector<std::string> consumeNames = {
        "Potion",
        "Scroll",
        "Gadget",
        "Arrow",
        "Bullet",
        "Bomb",
        "Porkchop"};
    const std::vector<std::string> stats = {
        "Health",
        "Attack",
        "Damage",
        "Armor",
        "Energy"};
    const std::vector<std::string> classes = {
        "Ranger",
        "Mage",
        "Warrior",
    };
    std::shared_ptr<ItemDescription> generateDescription(int, int, int) const;
    std::shared_ptr<BaseDescription> generateBaseItem(int, int) const;

public:
    ItemManager();
    std::shared_ptr<Item> createItem(int) const;
    std::vector<std::shared_ptr<Item>> createItemGroup(int) const;
};

#endif