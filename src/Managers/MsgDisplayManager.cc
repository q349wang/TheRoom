#include "MsgDisplayManager.h"
#include "../HelperClasses/Subject.h"

using namespace std;

MsgDisplayManager::MsgDisplayManager(Subject* sub, ostream& out)
    : _sub{sub}, _out{out} {
    _sub->attach(this);
}
MsgDisplayManager::~MsgDisplayManager() { _sub->detach(this); }

void MsgDisplayManager::notify() {
    _out << _sub->getMsg() << endl;
    return;
}