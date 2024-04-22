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
using namespace std;


//把报废船或者建筑更新到地图上
void broken_update(string target, string item, string** ptr) {

}
//检测目标玩家的船或者建筑是否报废
void broken_detect(string target, string item, string ** ptr) {
	if (target == "player") {
		//报废了
		if ((playerships[item].hp <= 0) and ) {
			broken_update(target, item, ptr);
		}
	}
}

//输入打击对象，打击对象的地图，点的位置
void attack_detect(string target, string** ptr, int x, int y) {
	//打空了
	if (ptr[x][y] == "O") {
		ptr[x][y] = "X";}
	else if (ptr[x][y] == "X") {
		cout << "Invalid attack, already attacked" << endl;
	}
	//目标player
	else if (target == "player") {
		//打到了航母1
	    if (ptr[x][y] == "H") {
			ptr[x][y] = "X";
			playerships["H"].hp--;
			//报废检测函数
		}
		//打到了航母2
		else if (ptr[x][y] == "h") {
			ptr[x][y] = "X";
			playerships["h"].hp--;
			//报废检测函数
		}
		//打到了驱逐1
		else if (ptr[x][y] == "Q") {
			ptr[x][y] = "X";
			playerships["Q"].hp--;
			//报废检测函数
		}
		//打到了驱逐2
		else if (ptr[x][y] == "q") {
			ptr[x][y] = "X";
			playerships["q"].hp--;
			//报废检测函数
		}
		//打到了科技1
		else if (ptr[x][y] == "K") {
			ptr[x][y] = "X";
			playerships["K"].hp--;
			//报废检测函数
		}
		//打到了驱逐2
		else if (ptr[x][y] == "k") {
			ptr[x][y] = "X";
			playerships["k"].hp--;
			//报废检测函数
		}
		//打到了石油1
		else if (ptr[x][y] == "S") {
			ptr[x][y] = "X";
			playerships["S"].hp--;
			//报废检测函数
		}
		//打到了石油2
		else if (ptr[x][y] == "s") {
			ptr[x][y] = "X";
			playerships["s"].hp--;
			//报废检测函数
		}
		//打到了护盾1
		else if (ptr[x][y] == "D") {
			ptr[x][y] = "X";
			playerships["D"].hp--;
			//报废检测函数
		}
		//打到了护盾2
		else if (ptr[x][y] == "d") {
			ptr[x][y] = "X";
			playerships["d"].hp--;
			//报废检测函数
		}
	}
	
	//目标enemy
	else if (target == "player") {
		//打到了航母1
		if (ptr[x][y] == "H") {
			ptr[x][y] = "X";
			enemyships["H"].hp--;
			//报废检测函数
		}
		//打到了航母2
		else if (ptr[x][y] == "h") {
			ptr[x][y] = "X";
			enemyships["h"].hp--;
			//报废检测函数
		}
		//打到了驱逐1
		else if (ptr[x][y] == "Q") {
			ptr[x][y] = "X";
			enemyships["Q"].hp--;
			//报废检测函数
		}
		//打到了驱逐2
		else  if (ptr[x][y] == "q") {
			ptr[x][y] = "X";
			enemyships["q"].hp--;
			//报废检测函数
		}
		//打到了科技1
		else if (ptr[x][y] == "K") {
			ptr[x][y] = "X";
			enemyships["K"].hp--;
			//报废检测函数
		}
		//打到了驱逐2
		else if (ptr[x][y] == "k") {
			ptr[x][y] = "X";
			enemyships["k"].hp--;
			//报废检测函数
		}
		//打到了石油1
		else if (ptr[x][y] == "S") {
			ptr[x][y] = "X";
			enemyships["S"].hp--;
			//报废检测函数
		}
		//打到了石油2
		else if (ptr[x][y] == "s") {
			ptr[x][y] = "X";
			enemyships["s"].hp--;
			//报废检测函数
		}
		//打到了护盾1
		else if (ptr[x][y] == "D") {
			ptr[x][y] = "X";
			enemyships["D"].hp--;
			//报废检测函数
		}
		//打到了护盾2
		else if (ptr[x][y] == "d") {
			ptr[x][y] = "X";
			enemyships["d"].hp--;
			//报废检测函数
		}
	}
}