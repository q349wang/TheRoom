#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

#include "Blessing.h"
#include "Compatibility.h" 
#include "Consumable.h"
#include "Curse.h"
#include "Equipable.h"
#include "Item.h"
#include "Modifier.h"
#include "BaseDescription.h"
#include "StatMod.h"

int main() {
    
    shared_ptr<ItemDescription> potiondDesc = make_shared<Blessing>("Health", StatMod{2, 2}, make_shared<BaseDescription>("Potion"));

    Consumable *x = new Consumable{"Potion", potiondDesc};
    cout << x->getName() << endl;
    cout << x->getName() << endl;
    // cout << testing.size() << endl;
    // cout << testing[0]->getAdder() << endl;
    // cout << testing[0]->getMultiplier() << endl;
    // for(int i=0;i<testing.size();i++){
    //     cout << testing[i]->getAdder() << testing[i]->getMultiplier() << endl;
    // }
    map<string,StatMod> toPrint = x->getModifiers();
    map<string, StatMod>::iterator it;
    for(it = toPrint.begin(); it!=toPrint.end();it++){
        cout << it->first << it->second.getAdder() << it->second.getMultiplier() << endl;
    }

}