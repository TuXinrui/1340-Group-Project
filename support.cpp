#include <iostream>
#include <cctype>	//character handling
#include <cstring>	//����C-string����ʾ�ַ������� '\0'��Ϊ�ַ����Ľ�����־
#include <string>   //��string��
#include <fstream>  //��IO��ofstreamд��ifstream��
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

