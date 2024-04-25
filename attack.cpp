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
using namespace std;

//把报废船或者建筑更新到地图上，此处指针都是seen
void broken_update(string target, string item, string** ptr_seen) {
	if (target == "player") {
		for (int i = playerships[item].x1; i <= playerships[item].x2; i++) {
			for (int j = playerships[item].y1; j <= playerships[item].y2; j++) {
				ptr_seen[i][j] = "B";
			}
		}
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

//输入打击对象，打击对象的地图，点的位置，ptr_real是真实海域， ptr_seen是看到的
void attack_detect(string target, string** ptr_real,string ** ptr_seen, int x, int y, int damage) {
	//目标player
	if (target == "player") {
		//打空了
		if (ptr_real[x][y] == "-") {
			ptr_seen[x][y] = "O";
		}

		//打到了航母1
		if (ptr_real[x][y] == "H") {
			ptr_seen[x][y] = "X";
			playerships["H"].hp -= damage;
			broken_detect(target, "H", ptr_seen);
		}
		//打到了航母2
		else if (ptr_real[x][y] == "h") {
			ptr_seen[x][y] = "X";
			playerships["h"].hp -= damage;
			broken_detect(target, "h", ptr_seen);
		}
		//打到了驱逐1
		else if (ptr_real[x][y] == "Q") {
			ptr_seen[x][y] = "X";
			playerships["Q"].hp -= damage;
			broken_detect(target, "Q", ptr_seen);
		}
		//打到了驱逐2
		else if (ptr_real[x][y] == "q") {
			ptr_seen[x][y] = "X";
			playerships["q"].hp -= damage;
			broken_detect(target, "X", ptr_seen);
		}
		//打到了科技1
		else if (ptr_real[x][y] == "K") {
			ptr_seen[x][y] = "X";
			playerships["K"].hp -= damage;
			broken_detect(target, "K", ptr_seen);
		}
		//打到了驱逐2
		else if (ptr_real[x][y] == "k") {
			ptr_seen[x][y] = "X";
			playerships["k"].hp -= damage;
			broken_detect(target, "k", ptr_seen);
		}
		//打到了石油1
		else if (ptr_real [x] [y] == "S") {
			ptr_seen[x][y] = "X";
			playerships["S"].hp -= damage;
			broken_detect(target, "S", ptr_seen);
		}
		//打到了石油2
		else if (ptr_real[x][y] == "s") {
			ptr_seen[x][y] = "X";
			playerships["s"].hp -= damage;
			broken_detect(target, "s", ptr_seen);
		}
		//打到了护盾1
		else if (ptr_real[x][y] == "D") {
			ptr_seen[x][y] = "X";
			playerships["D"].hp -= damage;
			broken_detect(target, "D", ptr_seen);
		}
		//打到了护盾2
		else if (ptr_real[x][y] == "d") {
			ptr_seen[x][y] = "X";
			playerships["d"].hp -= damage;
			broken_detect(target, "d", ptr_seen);
		}
	}
	
	//目标enemy
	else if (target == "enemy") {
		//打空了
		if (ptr_real[x][y] == "-") {
			ptr_seen[x][y] = "O";
		}
		//打到了航母1
		if (ptr_real[x][y] == "H") {
			ptr_seen[x][y] = "X";
			enemyships["H"].hp -= damage;
			broken_detect(target, "H", ptr_seen);
		}
		//打到了航母2
		else if (ptr_real[x][y] == "h") {
			ptr_seen[x][y] = "X";
			enemyships["h"].hp -= damage;
			broken_detect(target, "h", ptr_seen);
		}
		//打到了驱逐1
		else if (ptr_real[x][y] == "Q") {
			ptr_seen[x][y] = "X";
			enemyships["Q"].hp -= damage;
			broken_detect(target, "Q", ptr_seen);
		}
		//打到了驱逐2
		else  if (ptr_real[x][y] == "q") {
			ptr_seen[x][y] = "X";
			enemyships["q"].hp -= damage;
			broken_detect(target, "q", ptr_seen);
		}
		//打到了科技1
		else if (ptr_real[x][y] == "K") {
			ptr_seen[x][y] = "X";
			enemyships["K"].hp -= damage;
			broken_detect(target, "K", ptr_seen);
		}
		//打到了驱逐2
		else if (ptr_real[x][y] == "k") {
			ptr_seen[x][y] = "X";
			enemyships["k"].hp -= damage;
			broken_detect(target, "k", ptr_seen);
		}
		//打到了石油1
		else if (ptr_real[x][y] == "S") {
			ptr_seen[x][y] = "X";
			enemyships["S"].hp -= damage;
			broken_detect(target, "S", ptr_seen);
		}
		//打到了石油2
		else if (ptr_real[x][y] == "s") {
			ptr_seen[x][y] = "X";
			enemyships["s"].hp -= damage;
			broken_detect(target, "s", ptr_seen);
		}
		//打到了护盾1
		else if (ptr_real[x][y] == "D") {
			ptr_seen[x][y] = "X";
			enemyships["D"].hp -= damage;
			broken_detect(target, "D", ptr_seen);
		}
		//打到了护盾2
		else if (ptr_real[x][y] == "d") {
			ptr_seen[x][y] = "X";
			enemyships["d"].hp -= damage;
			broken_detect(target, "d", ptr_seen);
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
		if (command == "torpedo")  attack_detect("enemy", ptr_real, ptr_seen, x, y, 1 + attack_buff[1]);
		//舰炮
		if (command == "artillery") {
			for (int i = x - 1; i <= x + 1; i++) {
				for (int j = y - 1; j <= y + 1; j++) {
					attack_detect("enemy", ptr_real, ptr_seen, i, j, 1 + attack_buff[1]);
				}
			}
		}
		//导弹
		if (command == "missile") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("enemy", ptr_real, ptr_seen, i, j, 1 + attack_buff[1]);
				}
			}
		}
		//核弹
		if (command == "nuclear") {
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
		if (command == "move") {
			string name = ptr_real[x1][y1];
			int a = playerships[name].x2 - playerships[name].x1;
			int b = playerships[name].y2 - playerships[name].y1;
			for (int i = playerships[name].x1; i <= playerships[name].x2; i++) {
				for (int j = playerships[name].y1; j <= playerships[name].y2; j++) {
					ptr_real[i][j] = "-";
				}
			}
			playerships[name].x1 = x2;
			playerships[name].y1 = y2;
			playerships[name].x2 = x2 + a;
			playerships[name].x2 = y2 + b;
			for (int i = playerships[name].x1; i <= playerships[name].x2; i++) {
				for (int j = playerships[name].y1; j <= playerships[name].y2; j++) {
					ptr_seen[i][j] = name;
				}
			}
			cout << "move finished\n";
		}
	}
	else {
		
		}if (command == "move") {
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
			enemyships[name].x2 = y2 + b;
			for (int i = enemyships[name].x1; i <= enemyships[name].x2; i++) {
				for (int j = enemyships[name].y1; j <= enemyships[name].y2; j++) {
					ptr_real[i][j] = name;
				}
			}
			cout << "move finished\n";
	}
}