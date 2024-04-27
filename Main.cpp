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
#include "inputtransform.h"
using namespace std;



int main() {
	string** player_real;
	string** player_seen;
	string** enemy_real;
	string** enemy_seen;
	//it is a new game
	while (true) {
		string in_line;
		getline(cin, in_line);
		if (in_line == "new game") {//the player wants to start a new game from a file
			map_size = 0;
			cout << "please input an integer \"n\" which 10<=n<=15, where n is the legth of the size of the map\n";
			while (cin >> map_size) {
				if (map_size < 15 || map_size>20) {
					cout << "Invalid size, please enter again.\n";
					continue;
				}
				break;
			}
			break;
		}
		if (in_line == "load") {
			//读档啊
			cout << "Enter your loading file's name" << endl;
			string loading_name;
			cin >> loading_name;
			ifstream fin;
			fin.open(loading_name.c_str());
			if (fin.fail()) {
				cout << "Error in loading! Try again."<< endl;
				continue;
			}
			else {
				cout << "Load successful";
				fin >> map_size;
				player_real = new string * [map_size];
				player_seen = new string * [map_size];
				enemy_real = new string * [map_size];
				enemy_seen = new string * [map_size];
				for (int i = 1; i <= map_size; i++) {
					for (int j = 1; j <= map_size; j++) {
						fin >> player_real[i][j];
					}
				}
				for (int i = 1; i <= map_size; i++) {
					for (int j = 1; j <= map_size; j++) {
						fin >> player_seen[i][j];
					}
				}
				for (int i = 1; i <= map_size; i++) {
					for (int j = 1; j <= map_size; j++) {
						fin >> enemy_real[i][j];
					}
				}
				for (int i = 1; i <= map_size; i++) {
					for (int j = 1; j <= map_size; j++) {
						fin >>enemy_seen[i][j];
					}
				}
				fin >> attack_buff[0];
				fin >> attack_buff[1];
				fin >> elixir[0];
				fin >> elixir[1];
				fin >> elixir_max[0];
				fin >> elixir_max[1];
				fin >> turn;
				fin >> torpedo_max[0];
				fin >> torpedo_max[1];
				fin >> torpedo_remain;
				fin >> torpedo_remain;
				for (int i = 0; i < 6; i++) {
					for (string j : {"H", "h", "Q", "q", "K", "k","S", "s" }) {
						fin >> playerships[j].x1;
						fin >> playerships[j].y1;
						fin >> playerships[j].x2;
						fin >> playerships[j].y2;
						fin >> playerships[j].hp;
						fin >> playerships[j].hp_max;
						fin >> playerships[j].status;
					}
				}
				for (int i = 0; i < 6; i++) {
					for (string j : {"H", "h", "Q", "q", "K", "k", "S", "s"}) {
						fin >> enemyships[j].x1;
						fin >> enemyships[j].y1;
						fin >> enemyships[j].x2;
						fin >> enemyships[j].y2;
						fin >> enemyships[j].hp;
						fin >> enemyships[j].hp_max;
						fin >> enemyships[j].status;
					}
				}
				fin.close();
			}
			break;
		}
		cout << "Invalid input, try again." << endl;
	}
	if (turn == 0) {
		//地图初始化Alex
		turn++;
	}
	else {
		//读档的情况
	}
	//Big turn for player and enemy
	while (true) {
		inputtransform(player_real, player_seen, enemy_real, enemy_seen);
		//enemy turn
		turn++;
		if (turn == -1) {
			cout << "game ends" << endl;
			break;
		}
	}
}