#include <iostream>
#include <cctype>	
#include <cstring>	
#include <string>   
#include <fstream>  
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include "attack.h"
#include "support.h"
#include <string>
using namespace std;

//in int array, 0 place for player and 1 for enemy
int map_size=0;
int attack_buff[2] = {0,0};  
int elixir[2] = {0,0};  //cost
int elixir_increament[2] = { 1,1 };
int elixir_max[2] = {6,6};
int turn = 0;  //number of turns
int torpedo_max[2] = {2,2};
int torpedo_remain=0;

vector <Cor> damaged_grids;  //to store the attacked points in one turn
vector<Cor> empty_grids;  //available grids for enemy ai to attack
vector<Cor> hit_grids;  //container to store the X grids
vector<Cor> forbid_grids;  //container to store the attacked grids in one turn to avoid double firing
map<string, Ship> playerships;  //to store player's ships
map<string, Ship> enemyships;  //opponent's ships


