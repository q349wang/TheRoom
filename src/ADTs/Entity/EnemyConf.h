#ifndef ENEMY_CONF_H_
#define ENEMY_CONF_H_

#include <utility>

// Struct to hold configuration values of enemy type
// Stats are stored as pair of base and scale
struct EnemyConf
{
    int weight;
    std::pair<double, double> health;
    std::pair<double, double> energy;
    std::pair<double, double> armour;
    std::pair<double, double> attack;
    EnemyConf();
    EnemyConf(int,
              std::pair<double, double>,
              std::pair<double, double>,
              std::pair<double, double>,
              std::pair<double, double>);
};

#endif
