#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Blessing.h"
#include "Compatibility.h" 
#include "Consumable.h"
#include "Curse.h"
#include "Equipable.h"
#include "Item.h"
#include "Modifier.h"
#include "StatMod.h"

int main() {
    Consumable *x = new Consumable{"Potion"};
    cout << x->getName() << endl;
    Blessing{x,7,8};
    Curse{x,12,15};
    cout << x->getName() << endl;
    vector<StatMod *> testing = x->getStatMod();
    // cout << testing.size() << endl;
    // cout << testing[0]->getAdder() << endl;
    // cout << testing[0]->getMultiplier() << endl;
    // for(int i=0;i<testing.size();i++){
    //     cout << testing[i]->getAdder() << testing[i]->getMultiplier() << endl;
    // }
    map<string,StatMod *> toPrint = x->getModifiers();
    map<string, StatMod *>::iterator it;
    for(it = toPrint.begin(); it!=toPrint.end();it++){
        cout << it->first << it->second->getAdder() << it->second->getMultiplier() << endl;
    }

}