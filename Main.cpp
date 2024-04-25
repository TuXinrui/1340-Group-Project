#include <iostream>
#include <cctype>	//character handling
#include <string>   //对string类
#include <fstream>  //对IO，ofstream写，ifstream读
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "attack.h"
#include "support.h"
using namespace std;



int main() {
	input_conversion(0);
	//it is a new game
	if (turn == 0) {
		//defines 4 pointers towards 4 maps
		string** player_real = new string * [map_size];
		string** player_seen = new string * [map_size];
		string** enemy_real = new string * [map_size];
		string** enemy_seen = new string * [map_size];
		turn++;
	}
	else {
		//读档的情况
	}
	//Big turn for player and enemy
	while (true) {
		input_conversion(player_real, player_seen, enemy_real, enemy_seen);
		//enemy turn
		turn++;
		if (turn == -1) {
			cout << "game ends" << endl;
			break;
		}
	}
}