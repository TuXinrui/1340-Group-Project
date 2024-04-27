// support.h 
#include <map>
#include <string>
using namespace std;

extern int map_size;
extern int attack_buff[2];
extern int elixir[2];  //cost  elixir[0]Íæ¼Ò·ÑÓÃ
extern int elixir_max[2];
extern int turn;  //number of turns
extern int torpedo_max[2];
extern int torpedo_remain;
extern int elixir_increament[2];
struct Ship {
	int x1, y1, x2, y2;
	int hp;
	int hp_max;
	bool status;
};
struct Cor {
	int x, y;
};
extern vector <Cor> damaged_grids;
extern vector <Cor> empty_grids;  //"-"
extern vector<Cor> hit_grids;  //"X"
extern map<std::string, Ship> playerships;
extern map<std::string, Ship> enemyships;

