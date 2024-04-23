// support.h 
#include <map>
#include <string>
using namespace std;

extern int map_size;
extern int attack_buff;
extern int elixir;  //cost
extern int elixir_max;
extern int turn;  //number of turns
extern int torpedo_max;
extern int torpedo_remain;

extern struct Ship {
	int x1, y1, x2, y2;
	int hp;
	bool status;
};
extern struct Cor {
	int x, y;
};

extern std::map<std::string, Ship> playerships;
extern std::map<std::string, Ship> enemyships;

