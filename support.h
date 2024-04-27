// support.h 
#include <map>
#include <string>
using namespace std;

extern int map_size;
extern int attack_buff[2];
extern int elixir[2];  //cost
extern int elixir_max[2];
extern int elixir_increament[2];
extern int turn;  //number of turns
extern int torpedo_max[2];
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

