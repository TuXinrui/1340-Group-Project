#include <iostream>
#include <cctype>	//character handling
#include <string>   //对string类
#include <fstream>  //对IO，ofstream写，ifstream读
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <windows.h>
#include "attack.h"
#include "support.h"
#include "inputtransform.h"
#include "enemy_ai.h"
#include "alex.h"
using namespace std;

void player_turn() {
	elixir_increament[0] = 1;
	for (string i :{"S", "s"}) {
		if (playerships[i].status == 1) {
			elixir_increament[0]++;
		}
	}
	elixir[0] += elixir_increament[0];
	damaged_grids.clear();
	torpedo_remain = torpedo_max[0];
}

void enemy_turn(string ** enemy_seen) {
	if (turn <= 31) {
		elixir_increament[1] = 1 + (turn / 8);
	}
	else {
		elixir_increament[1] = 4;
	}
	elixir[0] += elixir_increament[0];
	forbid_grids.clear();
	torpedo_remain = torpedo_max[1];
	enemy_container(enemy_seen);
}

int main() {
	string** player_real=0;
	string** player_seen=0;
	string** enemy_real=0;
	string** enemy_seen=0;
	//第一次用户输入
	while (true) {
		string in_line;
		cout << "game started, input your first command pls" << endl;
		getline(cin, in_line);
		//新游戏
		if (in_line == "new game") {
			//map_size = 0;
			cout << "please input an integer \"n\" which 15<=n<=20, where n is the legth of the size of the map\n";
			cin >> map_size;
			while (true) {
				if (map_size < 15 || map_size>20) {
					cout << "Invalid size, please enter again.\n";
					continue;
				}
				break;
			}
			break;
		}
		//读档
		else if (in_line == "load") {
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
				for (string j : {"H", "h", "Q", "q", "K", "k","S", "s" }) {
					fin >> playerships[j].x1;
					fin >> playerships[j].y1;
					fin >> playerships[j].x2;
					fin >> playerships[j].y2;
					fin >> playerships[j].hp;
					fin >> playerships[j].hp_max;
					fin >> playerships[j].status;
				}
				for (string j : {"H", "h", "Q", "q", "K", "k"}) {
					fin >> enemyships[j].x1;
					fin >> enemyships[j].y1;
					fin >> enemyships[j].x2;
					fin >> enemyships[j].y2;
					fin >> enemyships[j].hp;
					fin >> enemyships[j].hp_max;
					fin >> enemyships[j].status;
				}
				for (int i = 0; i < empty_grids.size(); i++) {
					fin >> empty_grids[i].x;
					fin >> empty_grids[i].y;
				}
				for (int i = 0; i < hit_grids.size(); i++) {
					fin >> hit_grids[i].x;
					fin >> hit_grids[i].y;
				}
				fin.close();
			}
			break;
		}
		else {
			cout << "Invalid input, try again." << endl;
		}
	}
	if (turn == 0) {
		InitMap(player_real, player_seen, enemy_real, enemy_seen);
		turn++;
	}
	//游戏开始
	system("pause");
	while (true) {
		//回合初始化
		player_turn();
		inputtransform(player_real, player_seen, enemy_real, enemy_seen);
		//enemy turn
		enemy_execute(player_real, player_seen, enemy_real, enemy_seen);
		if (turn == -1) {
			cout << "game ends" << endl;
			break;
		}
		turn++;
		//回合初始化
	}
}