#include "ItemManager.h"
#include "../ADTs/Item/Equipable.h"
#include "../ADTs/Item/Consumable.h"

#include "../ADTs/Item/BaseDescription.h"
#include "../ADTs/Item/Curse.h"
#include "../ADTs/Item/Blessing.h"
#include "../ADTs/Item/Compatibility.h"

#include <time.h>
#include <cstdlib>

using namespace std;

ItemManager::ItemManager()
{
    srand(time(NULL));
}

shared_ptr<BaseDescription> ItemManager::generateBaseItem(int level, int type) const
{

    string itemName = type == 0 ? equipNames[rand() % equipNames.size()]
                                : consumeNames[rand() % consumeNames.size()];
    map<string, StatMod> baseStats;
    // Every five levels, max number of base stats increases by 1
    int numBase = rand() % (level / 5 + 1) + 1;
    for (int i = 0; i < numBase; i++)
    {
        string name = stats[rand() % stats.size()];
        double adder = rand() % level + (level / 2 + 1);
        double multi = 1.0;
        StatMod stat{adder, multi};

        ItemDescription::combineMods(baseStats, name, stat);
    }

    return make_shared<BaseDescription>(itemName, baseStats);
}

shared_ptr<ItemDescription> ItemManager::generateDescription(int level, int type, int numMods) const
{
    if (numMods == 0)
    {
        return generateBaseItem(level, type);
    }
    else
    {
        numMods--;
        int modType = rand() % 10;

        // Half the time, modifier is a blessing
        if (modType < 5)
        {
            string name = stats[rand() % stats.size()];

            // These can be adjusted
            double adder = rand() % level + (level / 2 + 1);
            double multi = 1.0 + (rand() % level) / 10.0;
            StatMod stat{adder, multi};
            return make_shared<Blessing>(name, stat, generateDescription(level, type, numMods));
        }
        // 3/10 of the time, it is a compatibility
        else if (modType < 5)
        {
            string className = classes[rand() % classes.size()];

            // These can be adjusted
            double multi = (rand() % 10) / 10.0;
            StatMod stat{0, multi};
            return make_shared<Compatability>(className, stat, generateDescription(level, type, numMods));
        }
        // 2/10 time modifier is a curse
        else
        {
            string name = stats[rand() % stats.size()];

            // These can be adjusted
            double adder = rand() % level + (level / 2 + 1);
            double multi = 1.0 + (rand() % level) / 20.0;
            StatMod stat{adder, multi};
            return make_shared<Curse>(name, stat, generateDescription(level, type, numMods));
        }
    }
}

shared_ptr<Item> ItemManager::createItem(int level) const
{
    // Consumables are three times as likely to appear compared to Equipment
    int type = rand() % 4;
    // Every five levels, max number of modifiers increases by 1
    int numMods = rand() % (level / 5 + 1);
    // Create Equipment
    if (type == 0)
    {
        shared_ptr<ItemDescription> desc = generateDescription(level, 0, numMods);

        // Generate passive
        map<string, StatMod> passiveStats;
        // Every five levels, max number of passive stats increases by 1
        int numBase = rand() % (level / 5 + 1);
        for (int i = 0; i < numBase; i++)
        {
            string name = stats[rand() % stats.size()];
            double adder = rand() % level + (level / 2 + 1);
            double multi = 1.0;
            StatMod stat{adder, multi};

            ItemDescription::combineMods(passiveStats, name, stat);
        }
        int durability = rand() % level + 3;
        return make_shared<Equipable>(desc->getName(), desc, passiveStats, durability);
    }
    // Create Consumable
    else
    {
        shared_ptr<ItemDescription> desc = generateDescription(level, 1, numMods);
        return make_shared<Consumable>(desc->getName(), desc);
    }
}

// Generates a group of items (ideal for battle drops)
vector<shared_ptr<Item>> ItemManager::createItemGroup(int level) const
{
    // Every 2 levels max number of items increases by 1
    int numItems = rand() % (level / 2 + 1);

    vector<shared_ptr<Item>> group;
    for (int i = 0; i < numItems; i++)
    {
        group.emplace_back(createItem(level));
    }

    return group;
}