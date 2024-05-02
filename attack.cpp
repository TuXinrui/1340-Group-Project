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
#include "enemy_ai.h"
using namespace std;


//把报废船或者建筑更新到地图上，此处指针都是seen
void broken_update(string target, string item, string** ptr_seen) {
	if (target == "player") {
		for (int i = playerships[item].x1; i <= playerships[item].x2; i++) {
			for (int j = playerships[item].y1; j <= playerships[item].y2; j++) {
				ptr_seen[i][j] = "B";
			}
		}
		enemy_container(ptr_seen);
		playerships[item].status = 0;
		
	}
	else {
		for (int i = enemyships[item].x1; i <= enemyships[item].x2; i++) {
			for (int j = enemyships[item].y1; j <= enemyships[item].y2; j++) {
				ptr_seen[i][j] = item;
			}
		}
		enemyships[item].status = 0;
	}
}

//检测目标玩家的船或者建筑是否报废，此处指针都是seen
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
//输入打击对象，打击对象的地图，点的位置，ptr_real是真实海域， ptr_seen是看到的
void attack_detect(string target, string** ptr_real,string ** ptr_seen, int x, int y, int damage) {
	//目标player
	
	Cor temp = { x, y };
	if (target == "player") {
		//打空了
		if (ptr_real[x][y] == "-") {
			ptr_seen[x][y] = "O";
			modify_empty(x, y);
		}
		//打到了航母1
		else if (ptr_real[x][y] == "H" and playerships["H"].status==true) {
			ptr_seen[x][y] = "X";
			playerships["H"].hp -= damage;
			broken_detect(target, "H", ptr_seen);
			modify_empty(x, y);
			hit_grids.push_back({ x,y });
		}
		//打到了航母2
		
		else if (ptr_real[x][y] == "h" and playerships["h"].status == true) {
			ptr_seen[x][y] = "X";
			playerships["h"].hp -= damage;
			broken_detect(target, "h", ptr_seen);
			modify_empty(x, y);
			hit_grids.push_back({ x,y });
		}
		//打到了驱逐1
		else if (ptr_real[x][y] == "Q" and playerships["Q"].status == true) {
			ptr_seen[x][y] = "X";
			playerships["Q"].hp -= damage;
			broken_detect(target, "Q", ptr_seen);
			modify_empty(x, y);
			hit_grids.push_back({ x,y });
		}
		//打到了驱逐2
		else if (ptr_real[x][y] == "q" and playerships["q"].status == true) {
			ptr_seen[x][y] = "X";
			playerships["q"].hp -= damage;
			broken_detect(target, "q", ptr_seen);
			modify_empty(x, y);
			hit_grids.push_back({ x,y });
		}
		//打到了科技1
		else if (ptr_real[x][y] == "K" and playerships["K"].status == true) {
			ptr_seen[x][y] = "X";
			playerships["K"].hp -= damage;
			broken_detect(target, "K", ptr_seen);
			modify_empty(x, y);
			hit_grids.push_back({ x,y });
		}
		//打到了驱逐2
		else if (ptr_real[x][y] == "k" and playerships["k"].status == true) {
			ptr_seen[x][y] = "X";
			playerships["k"].hp -= damage;
			broken_detect(target, "k", ptr_seen);
			modify_empty(x, y);
			hit_grids.push_back({ x,y });
		}
		//打到了石油1
		else if (ptr_real [x] [y] == "S" and playerships["S"].status == true) {
			ptr_seen[x][y] = "X";
			playerships["S"].hp -= damage;
			broken_detect(target, "S", ptr_seen);
			modify_empty(x, y);
			hit_grids.push_back({ x,y });
		}
		//打到了石油2
		else if (ptr_real[x][y] == "s" and playerships["s"].status == true) {
			ptr_seen[x][y] = "X";
			playerships["s"].hp -= damage;
			broken_detect(target, "s", ptr_seen);
			modify_empty(x, y);
			hit_grids.push_back({ x,y });
		}
	}
	//目标enemy
	else if (target == "enemy") {
		//打空了
		if (ptr_real[x][y] == "-") {
			ptr_seen[x][y] = "O";
		}
		//打到了航母1
		else if (ptr_real[x][y] == "H" and enemyships["H"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["H"].hp -= damage;
			broken_detect(target, "H", ptr_seen);
		}
		//打到了航母2
		else if (ptr_real[x][y] == "h" and enemyships["h"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["h"].hp -= damage;
			broken_detect(target, "h", ptr_seen);
		}
		//打到了驱逐1
		else if (ptr_real[x][y] == "Q" and enemyships["Q"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["Q"].hp -= damage;
			broken_detect(target, "Q", ptr_seen);
		}
		//打到了驱逐2
		else  if (ptr_real[x][y] == "q" and enemyships["q"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["q"].hp -= damage;
			broken_detect(target, "q", ptr_seen);
		}
		//打到了科技1
		else if (ptr_real[x][y] == "K" and enemyships["K"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["K"].hp -= damage;
			broken_detect(target, "K", ptr_seen);
		}
		//打到了驱逐2
		else if (ptr_real[x][y] == "k" and enemyships["k"].status == 1) {
			ptr_seen[x][y] = "X";
			enemyships["k"].hp -= damage;
			broken_detect(target, "k", ptr_seen);
		}
	}
}

void attack_input_conversion(string target, string** ptr_real,string **ptr_seen, string command, int x, int y, int damage) {
	if (target == "player") {
		//鱼雷
		if (command == "torpedo") attack_detect("player", ptr_real,ptr_seen, x, y, 1+attack_buff[0]);
		//舰
		if (command == "artillery") {
			for (int i = x - 1; i <= x + 1; i++) {
				for (int j = y - 1; j <= y + 1; j++) {
					attack_detect("player", ptr_real, ptr_seen,i, j, 1 + attack_buff[0]);
				}
			}
		}
		//导弹
		if (command == "missile") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("player", ptr_real, ptr_seen, i, j, 1 + attack_buff[0]);
				}
			}
		}
		//核弹
		if (command == "nuclear") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("player", ptr_real, ptr_seen, i, j, 2 + attack_buff[0]);
				}
			}
		}
	}//敌人回合
	else {
		//鱼雷
		if (command == "torpedo") {
			attack_detect("enemy", ptr_real, ptr_seen, x, y, 1 + attack_buff[1]);
		}
		//舰炮
		else if (command == "artillery") {
			for (int i = x - 1; i <= x + 1; i++) {
				for (int j = y - 1; j <= y + 1; j++) {
					attack_detect("enemy", ptr_real, ptr_seen, i, j, 1 + attack_buff[1]);
				}
			}
		}
		//导弹
		else if (command == "missile") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("enemy", ptr_real, ptr_seen, i, j, 1 + attack_buff[1]);
				}
			}
		}
		//核弹
		else if (command == "nuclear") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("enemy", ptr_real , ptr_seen, i, j, 1 + attack_buff[1]);
				}
			}
		}
	}

}

void skills(string target, string** ptr_real, string** ptr_seen, string command, int x1, int y1, int x2, int y2) {
	if (target == "player") {
		//把x1y1的船移动到x2y2
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
		//治疗点目标x1点
		if (command == "heal") {
			playerships[ptr_real[x1][y1]].hp += x2;
			if (playerships[ptr_real[x1][y1]].hp > playerships[ptr_real[x1][y1]].hp_max) {
				playerships[ptr_real[x1][y1]].hp = playerships[ptr_real[x1][y1]].hp_max;
			}
			cout << "heal successful" << endl;
		}
		//建造石油井1和2
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
		//增加各种上限
	}
	else {
		//把x1y1的船移动到x2y2
		
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
					ptr_seen[i][j] = name;
				}
			}
		}
		
		//治疗点目标x1点
		if (command == "heal") {
			enemyships[ptr_real[x1][y1]].hp += x2;
			if (enemyships[ptr_real[x1][y1]].hp > enemyships[ptr_real[x1][y1]].hp_max) {
				enemyships[ptr_real[x1][y1]].hp = enemyships[ptr_real[x1][y1]].hp_max;
			}
		}
		//建造石油井1和2
		if (command == "S" or command == "s") {
			enemyships[command].hp = 1;
			enemyships[command].hp_max = 1;
			enemyships[command].status = 1;
			enemyships[command].x1 = x1;
			enemyships[command].y1 = y1;
			enemyships[command].x2 = x1;
			enemyships[command].y2 = y1;
			ptr_seen[x1][y1] = command;
			ptr_real[x1][y1] = command;
			elixir_increament[1]++;
			elixir_max[1]++;
		}
		//增加各种上限
	}
}