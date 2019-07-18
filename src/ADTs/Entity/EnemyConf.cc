#include "EnemyConf.h"
using namespace std;

EnemyConf::EnemyConf(int weight,
                     pair<double, double>  health,
                     pair<double, double>  energy,
                     pair<double, double> armour,
                     pair<double, double> attack)
    : weight{weight},
      health{health},
      energy{energy},
      armour{armour},
      attack{attack} {}