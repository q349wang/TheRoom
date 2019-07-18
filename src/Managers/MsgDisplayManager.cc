#include "MsgDisplayManager.h"

using namespace std;

MsgDisplayManager::MsgDisplayManager(ostream& out)
    :_out{out} {}
MsgDisplayManager::~MsgDisplayManager() {}

void MsgDisplayManager::notify(string msg) {
    _out << msg << endl;
    return;
}