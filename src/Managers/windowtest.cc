#include "XWindowManager.h"
#include "../ADTs/Map/Map.h"
#include "../ADTs/Entity/Ranger.h"

#include <unistd.h>
using namespace std;

int main()
{

    shared_ptr<Player> p = make_shared<Ranger>(100, 100, 10, pair<int, int>{0, 0});
    vector<vector<char>> v = {
        {'W', 'W', 'W', 'W', 'W', 'W'},
        {'W', 'S', 'S', 'S', 'S', 'W'},
        {'W', 'S', 'S', 'W', 'S', 'W'},
        {'W', 'E', 'S', 'W', 'S', 'W'},
        {'W', 'W', 'W', 'W', 'W', 'W'}};
    shared_ptr<Map> m = make_shared<Map>(p, v);
        XWindowManager win(m);
        win.redrawMap();

        sleep(1000);
}