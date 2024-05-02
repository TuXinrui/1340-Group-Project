#include <iostream>
#include <cctype>	
#include <string>   
#include <fstream>  
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
//#include <windows.h>
#include "attack.h"
#include "support.h"
#include "inputtransform.h"
#include "enemy_ai.h"
#include "initMap.h"
#include "output.h"
using namespace std;

const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string YELLOW = "\033[1;33m";
const string BLUE = "\033[1;34m";
const string MAGENTA = "\033[1;35m";
const string CYAN = "\033[1;36m";
const string RESET = "\033[0m";

void player_turn() {
	elixir_increament[0] = 1;
	for (string i :{"S", "s"}) {
		if (playerships[i].status == 1) {
			elixir_increament[0]++;
		}
	}
	elixir[0] += elixir_increament[0];
	if (elixir[0] > elixir_max[0])  elixir[0] = elixir_max[0];
	damaged_grids.clear();
	torpedo_remain = torpedo_max[0];
}

void enemy_turn(string ** player_seen) {
	if (turn <= 31) {
		elixir_increament[1] = 1 + (turn / 8);
	}
	else {
		elixir_increament[1] = 4;
	}
	if (turn <= 10) {
		elixir_max[1] = 6 + (turn / 5);
	}
	else {
		elixir_max[1] = 8;
	}
	if (elixir[1] > elixir_max[1])  elixir[1] = elixir_max[1];
	elixir[1] += elixir_increament[1];
	forbid_grids.clear();
	torpedo_remain = torpedo_max[1];
	enemy_container(player_seen);
}

int main() {
	system("clear");
	string** player_real=0;
	string** player_seen=0;
	string** enemy_real=0;
	string** enemy_seen=0;
	//first input by the user
	cout << "Welcome to the" << BLUE << " NAVAL BATTLE" << RESET << "!" << endl;
	while (true) {
		string in_line;
		
		cout << "Enter " << YELLOW << "\"new game\"" << RESET << " or " << YELLOW << "\"load\"" << RESET << " to start!" << endl;
		getline(cin, in_line);
		in_line = string_execute(in_line);
		//new game
		if (in_line == "newgame") {
			turn = 0;
			while (1) {
				map_size = 0;
				bool size_valid = 1;
				string tmp_size;
				int size_len;
				cout << "please input an integer \"n\" that 15<=n<=20, where n is the length of the side of the map\n";
				//cin >> map_size;
				getline(cin, tmp_size);
				tmp_size = string_execute(tmp_size);
				size_len = tmp_size.length();
				for (int i = 0; i < size_len; i++) {
					if (tmp_size[i] > 57 || tmp_size[i] < 48) {
						cout << "Invalid n.\n";
						size_valid = 0;
						break;
					}
					else {
						map_size *= 10;
						map_size += (tmp_size[i] - 48);
					}
				}
				if (size_valid == 0) {
					continue;
				}
				if (map_size > 20 || map_size < 15) {
					cout << "Input too large or too small.\n";
					continue;
				}
				break;
			}
			break;
		}
		//read file
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
				//cout << "Load successful";
				fin >> map_size;
				player_real = new string * [map_size+1];
				player_seen = new string * [map_size+1];
				enemy_real = new string * [map_size+1];
				enemy_seen = new string * [map_size+1];
				//1
				for (int i = 0; i <= map_size; i++) {
					player_real[i] = new string[map_size + 1];
					player_seen[i] = new string[map_size + 1];
					enemy_real[i] = new string[map_size + 1];
					enemy_seen[i] = new string[map_size + 1];
				}

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
				//fin >> attack_buff[0];
				//fin >> attack_buff[1];
				fin >> elixir[0];
				fin >> elixir[1];
				fin >> elixir_max[0];
				fin >> elixir_max[1];
				fin >> turn;
				fin >> torpedo_max[0];
				fin >> torpedo_max[1];
				fin >> torpedo_remain;
				for (string j : {"H", "h", "K", "k", "Q", "q","S", "s" }) {
					fin >> playerships[j].x1;
					fin >> playerships[j].y1;
					fin >> playerships[j].x2;
					fin >> playerships[j].y2;
					fin >> playerships[j].hp;
					fin >> playerships[j].hp_max;
					fin >> playerships[j].status;
				}
				for (string j : {"H", "h", "K", "k", "Q", "q"}) {
					fin >> enemyships[j].x1;
					fin >> enemyships[j].y1;
					fin >> enemyships[j].x2;
					fin >> enemyships[j].y2;
					fin >> enemyships[j].hp;
					fin >> enemyships[j].hp_max;
					fin >> enemyships[j].status;
				}
				int a, b;
				fin >> a;
				for (int i = 0; i < a; i++) {
					Cor tmp;
					fin >> tmp.x;
					fin >> tmp.y;
					empty_grids.push_back(tmp);
				}
				fin >> b;
				for (int i = 0; i < b; i++) {
					Cor tmp;
					fin >> tmp.x;
					fin >> tmp.y;
					hit_grids.push_back(tmp);
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
	//game start
	while (true) {
		//player turn initialize
		player_turn();
		inputtransform(player_real, player_seen, enemy_real, enemy_seen);
		if (enemyships["H"].status == 0 and enemyships["h"].status == 0) {
			cout <<GREEN<< "Player wins by destroying the H and h battleships." <<RESET<< endl;
			cout << "In " <<turn << " turns." << endl;
			return 1;
		}
		if (turn == -1) {
			cout << "Game ends" << endl;
			break;
		}
		if (turn == -2) {
			cout << RED << "Player surrenders, enemy wins." << RESET << endl;
			return 1;
		}
		//enemy turn initialize
		cout << "enemy turn started" << endl;
		enemy_turn(player_seen);
		enemy_execute(player_real, player_seen, enemy_real, enemy_seen);
		cout << "enemy turn ended" << endl;
		if (playerships["H"].status == 0 and playerships["h"].status == 0) {
			cout <<RED<< "Enemy wins by destroying the H and h battleships." <<RESET<< endl;
			cout << "In " << turn << " turns." << endl;
			return 1;
		}
		turn++;
		if (turn == -1) {
			cout << "Game ends" << endl;
			break;
		}
		
	}
}