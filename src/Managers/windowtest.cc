// #include "XWindowManager.h"
// #include "../ADTs/Map/Map.h"
// #include "../ADTs/Entity/Ranger.h"
// #include "../ADTs/Entity/Warrior.h"
// #include "../ADTs/Entity/Mage.h"

// #include <iostream>
// #include <unistd.h>
// using namespace std;

// int main()
// {

//     shared_ptr<Player> p = make_shared<Mage>(100, 100, 100, 10, pair<int, int>{1, 1});
//     vector<vector<char>> v = {
//         {'W', 'W', 'W', 'W', 'W', 'W'},
//         {'W', 'S', 'S', 'S', 'S', 'W'},
//         {'W', 'S', 'S', 'W', 'S'},
//         {'W', 'E', 'S', 'W', 'S', 'W'},
//         {'W', 'W', 'W', 'W', 'W', 'W'},
//         {'W', 'E', 'S', 'W', 'S', 'W'},
//         {'W', 'E', 'S', 'W', 'S', 'W'},
//         {'W', 'E', 'S', 'W', 'S', 'W'},
//         {'W', 'E', 'S', 'W', 'S', 'W'},
//         {'W', 'E', 'S', 'W', 'S', 'W'},
//         {'W', 'E', 'S', 'W', 'S', 'W'},
//         {'W', 'E', 'S', 'W', 'S', 'W'},
//         {'W', 'E', 'S', 'W', 'E', 'W'},
//         {'W', 'E', 'S', 'W', 'S', 'W'},
//         {'W', 'E', 'S', 'W', 'S', 'W'},
//         {'W', 'E', 'S', 'W', 'S', 'W'}};
//     shared_ptr<Map> m = make_shared<Map>(p, v);
//     p->setMap(m);
//     XWindowManager win(m);
//     while (true)
//     {
//         win.redrawMap();

//         sleep(2);
//         bool move = p->makeMove('N');
//         win.redrawMap();
//         cout << move << endl;
//     }
// }