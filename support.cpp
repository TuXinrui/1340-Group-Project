#include <iostream>
#include <cctype>	//character handling
#include <cstring>	//对于C-string，表示字符串，以 '\0'作为字符串的结束标志
#include <string>   //对string类
#include <fstream>  //对IO，ofstream写，ifstream读
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

int map_size=0;
int attack_buff = 0;
int elixir = 0;  //cost
int elixir_max = 6;
int turn = 0;  //number of turns
int torpedo_max = 2;
int torpedo_remain = torpedo_max;

vector <Cor> damaged_grids;  //to store the attacked points in one turn
 
map<string, Ship> playerships;  //to store player's ships
map<string, Ship> enemyships;  //opponent's ships

