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
#include "enemy_ai.h"
using namespace std;


//update the broken ships onto the pointer maps
void broken_update(string target, string item, string** ptr_seen) {
	if (target == "player") {
		for (int i = playerships[item].x1; i <= playerships[item].x2; i++) {
			for (int j = playerships[item].y1; j <= playerships[item].y2; j++) {
				ptr_seen[i][j] = "B";
			}
		}
		enemy_container(ptr_seen);
		playerships[item].status = false;
		if (item == "Q" || item == "K" || item == "k" || item == "q") {
			elixir[1] += 3;
			if (elixir[1] > elixir_max[1]) {
				elixir[1] = elixir_max[1];
			}
		}
		
		
	}
	else {
		for (int i = enemyships[item].x1; i <= enemyships[item].x2; i++) {
			for (int j = enemyships[item].y1; j <= enemyships[item].y2; j++) {
				ptr_seen[i][j] = item;
			}
		}
		enemyships[item].status = 0;
		if(item == "Q" || item == "K" || item == "k" || item == "q"){
			elixir[0] += 3;
			if (elixir[0] > elixir_max[0]) {
				elixir[0] = elixir_max[0];
			}
		}
		
	}
}

//detect whether the target ship is broken
void broken_detect(string target, string item, string** ptr_seen) {
	if (target == "player") {
		if ((playerships[item].hp <= 0)and(playerships[item].status == 1)) {
			broken_update(target, item, ptr_seen);
			cout << target << " " << item << " "<<"has been crashed" << endl;
		}
	}
	else {
		if ((enemyships[item].hp <= 0) and (enemyships[item].status == 1)) {
			broken_update(target, item, ptr_seen);
			cout << target << " " << item << " " << "has been crashed" << endl;
		}
	}
}
//erase specific grid in empty container, and add it to forbid container
void modify_empty(int x, int y) {
	int b = 0;
	for (int i = 0; i < empty_grids.size(); i++) {
		if (empty_grids[i].x == x and empty_grids[i].y == y) {
			b = i;
			break;
		}
	}
	empty_grids.erase(empty_grids.begin() + b);
	forbid_grids.push_back({ x,y });
}
//check the real map of the attacking grid, for enemy or for player
void attack_detect(string target, string** ptr_real,string ** ptr_seen, int x, int y, int damage) {
	//target == player
	Cor temp = { x, y };
	if (target == "player") {
		//empty
		if (ptr_real[x][y] == "-") {
			ptr_seen[x][y] = "O";
			modify_empty(x, y);
		}
		//hit H
		else if (ptr_real[x][y] == "H" and playerships["H"].status==true) {
			ptr_seen[x][y] = "X";
			hit_grids.push_back({ x,y });
			playerships["H"].hp -= damage;
			broken_detect(target, "H", ptr_seen);
			modify_empty(x, y);
			
		}
		//hit h
		else if (ptr_real[x][y] == "h" and playerships["h"].status == true) {
			ptr_seen[x][y] = "X";
			hit_grids.push_back({ x,y });
			playerships["h"].hp -= damage;
			broken_detect(target, "h", ptr_seen);
			modify_empty(x, y);
			
		}
		////hit Q
		else if (ptr_real[x][y] == "Q" and playerships["Q"].status == true) {
			ptr_seen[x][y] = "X";
			hit_grids.push_back({ x,y });
			playerships["Q"].hp -= damage;
			broken_detect(target, "Q", ptr_seen);
			modify_empty(x, y);
		
		}
		//hit q
		else if (ptr_real[x][y] == "q" and playerships["q"].status == true) {
			ptr_seen[x][y] = "X";
			hit_grids.push_back({ x,y });
			playerships["q"].hp -= damage;
			broken_detect(target, "q", ptr_seen);
			modify_empty(x, y);
			
		}
		//hit K
		else if (ptr_real[x][y] == "K" and playerships["K"].status == true) {
			ptr_seen[x][y] = "X";
			hit_grids.push_back({ x,y });
			playerships["K"].hp -= damage;
			broken_detect(target, "K", ptr_seen);
			modify_empty(x, y);
			
		}
		//hit k
		else if (ptr_real[x][y] == "k" and playerships["k"].status == true) {
			ptr_seen[x][y] = "X";
			hit_grids.push_back({ x,y });
			playerships["k"].hp -= damage;
			broken_detect(target, "k", ptr_seen);
			modify_empty(x, y);
			
		}
		//hit S
		else if (ptr_real [x] [y] == "S" and playerships["S"].status == true) {
			ptr_seen[x][y] = "X";
			hit_grids.push_back({ x,y });
			playerships["S"].hp -= damage;
			broken_detect(target, "S", ptr_seen);
			modify_empty(x, y);
			
		}
		//hit s
		else if (ptr_real[x][y] == "s" and playerships["s"].status == true) {
			ptr_seen[x][y] = "X";
			hit_grids.push_back({ x,y });
			playerships["s"].hp -= damage;
			broken_detect(target, "s", ptr_seen);
			modify_empty(x, y);
			
		}
	}
	//target == enemy
	else if (target == "enemy") {
		//empty
		if (ptr_real[x][y] == "-") {
			ptr_seen[x][y] = "O";
		}
		//hit H
		else if (ptr_real[x][y] == "H" and enemyships["H"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["H"].hp -= damage;
			broken_detect(target, "H", ptr_seen);
		}
		//hit h
		else if (ptr_real[x][y] == "h" and enemyships["h"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["h"].hp -= damage;
			broken_detect(target, "h", ptr_seen);
		}
		//hit Q
		else if (ptr_real[x][y] == "Q" and enemyships["Q"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["Q"].hp -= damage;
			broken_detect(target, "Q", ptr_seen);
		}
		//hit q
		else  if (ptr_real[x][y] == "q" and enemyships["q"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["q"].hp -= damage;
			broken_detect(target, "q", ptr_seen);
		}
		//hit K
		else if (ptr_real[x][y] == "K" and enemyships["K"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["K"].hp -= damage;
			broken_detect(target, "K", ptr_seen);
		}
		//hit k
		else if (ptr_real[x][y] == "k" and enemyships["k"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["k"].hp -= damage;
			broken_detect(target, "k", ptr_seen);
		}
	}
}
//convert the input lines into attack commands
void attack_input_conversion(string target, string** ptr_real,string **ptr_seen, string command, int x, int y, int damage) {
	if (target == "player") {
		//torpedo
		if (command == "torpedo") attack_detect("player", ptr_real,ptr_seen, x, y, 1+attack_buff[0]);
		//artillery
		if (command == "artillery") {
			for (int i = x - 1; i <= x + 1; i++) {
				for (int j = y - 1; j <= y + 1; j++) {
					attack_detect("player", ptr_real, ptr_seen,i, j, 1 + attack_buff[0]);
				}
			}
		}
		//missile
		if (command == "missile") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("player", ptr_real, ptr_seen, i, j, 1 + attack_buff[0]);
				}
			}
		}
		//nuclear
		if (command == "nuclear") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("player", ptr_real, ptr_seen, i, j, 2 + attack_buff[0]);
				}
			}
		}
	}//enemy turn
	else {
		//torpedo
		if (command == "torpedo") {
			attack_detect("enemy", ptr_real, ptr_seen, x, y, 1 + attack_buff[1]);
		}
		//artillery
		else if (command == "artillery") {
			for (int i = x - 1; i <= x + 1; i++) {
				for (int j = y - 1; j <= y + 1; j++) {
					attack_detect("enemy", ptr_real, ptr_seen, i, j, 1 + attack_buff[1]);
				}
			}
		}
		//missile
		else if (command == "missile") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("enemy", ptr_real, ptr_seen, i, j, 1 + attack_buff[1]);
				}
			}
		}
		//nuclear
		else if (command == "nuclear") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("enemy", ptr_real , ptr_seen, i, j, 1 + attack_buff[1]);
				}
			}
		}
	}

}

//skills for player or enemy
void skills(string target, string** ptr_real, string** ptr_seen, string command, int x1, int y1, int x2, int y2) {
	//for player
	if (target == "player") {
		//move specific ship to x2y2
		if (command == "move") {
			string name = ptr_real[x1][y1];
			int a = playerships[name].x2 - playerships[name].x1;
			int b = playerships[name].y2 - playerships[name].y1;
			for (int i = playerships[name].x1; i <= playerships[name].x2; i++) {
				for (int j = playerships[name].y1; j <= playerships[name].y2; j++) {
					ptr_real[i][j] = "-";
					if (ptr_seen[i][j] == name)  ptr_seen[i][j] = "-";
				}
			}
			playerships[name].x1 = x2;
			playerships[name].y1 = y2;
			playerships[name].x2 = x2 + a;
			playerships[name].y2 = y2 + b;
			for (int i = playerships[name].x1; i <= playerships[name].x2; i++) {
				for (int j = playerships[name].y1; j <= playerships[name].y2; j++) {
					ptr_seen[i][j] = name;
					ptr_real[i][j] = name;
				}
			}
			cout << "move finished\n";
		}
		//heal specific ship
		if (command == "heal") {
			playerships[ptr_real[x1][y1]].hp += x2;
			if (playerships[ptr_real[x1][y1]].hp > playerships[ptr_real[x1][y1]].hp_max) {
				playerships[ptr_real[x1][y1]].hp = playerships[ptr_real[x1][y1]].hp_max;
			}
			cout << "heal successful" << endl;
		}
		//construct the oil well
		if (command == "S" or command == "s") {
			playerships[command].hp = 1;
			playerships[command].hp_max = 1;
			playerships[command].status = 1;
			playerships[command].x1 = x1;
			playerships[command].y1 = y1;
			playerships[command].x2 = x1;
			playerships[command].y2 = y1;
			ptr_seen[x1][y1] = command;
			ptr_real[x1][y1] = command;
			elixir_increament[0]++;
			elixir_max[0]++;
		}
	}
	else {
		//move specific ship to x2y2
		if (command == "move") {
			string name = ptr_real[x1][y1];
			int a = enemyships[name].x2 - enemyships[name].x1;
			int b = enemyships[name].y2 - enemyships[name].y1;
			for (int i = enemyships[name].x1; i <= enemyships[name].x2; i++) {
				for (int j = enemyships[name].y1; j <= enemyships[name].y2; j++) {
					ptr_real[i][j] = "-";
					
				}
			}
			enemyships[name].x1 = x2;
			enemyships[name].y1 = y2;
			enemyships[name].x2 = x2 + a;
			enemyships[name].y2 = y2 + b;
			for (int i = enemyships[name].x1; i <= enemyships[name].x2; i++) {
				for (int j = enemyships[name].y1; j <= enemyships[name].y2; j++) {
					ptr_real[i][j] = name;
					//ptr_seen[i][j] = name;
				}
			}
		}
		
		//heal specific ship
		if (command == "heal") {
			enemyships[ptr_real[x1][y1]].hp += x2;
			if (enemyships[ptr_real[x1][y1]].hp > enemyships[ptr_real[x1][y1]].hp_max) {
				enemyships[ptr_real[x1][y1]].hp = enemyships[ptr_real[x1][y1]].hp_max;
			}
		}
	}
}