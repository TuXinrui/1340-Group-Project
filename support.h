#ifndef SUPPORT_H
#define SUPPORT_H

#include <vector>
#include <map>
#include <string>

struct Ship {
    int x1, y1, x2, y2;
    int hp;
    bool status;
};

struct Cor {
    int x, y;
};

extern int map_size;
extern int attack_buff[2];
extern int elixir[2];
extern int elixir_max[2];
extern int elixir_increament[2];
extern int turn;
extern int torpedo_max[2];
extern int torpedo_remain;
extern std::string dialogue;

extern std::map<std::string, Ship> playerships;
extern std::map<std::string, Ship> enemyships;
extern std::vector<Cor> damaged_grids;

#endif
