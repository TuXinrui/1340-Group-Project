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
#include <string>
using namespace std;
//刷新empty和hit这两个容器
void enemy_container(string** ptr_seen) {
	empty_grids.clear();
	hit_grids.clear();
	for (int i = 1; i <= map_size; i++) {
		for (int j = 1; j <= map_size; j++) {
			if (ptr_seen[i][j] == "-") {
				empty_grids.push_back({ i, j });
			}
			if (ptr_seen[i][j] == "X") {
				hit_grids.push_back({ i, j });
			}
		}
	}
}

void enemy_execute(string** player_real, string** player_seen, string** enemy_real,string** enemy_seen) {
	//紧急移动
	if ((enemyships["H"].hp <= 5) and (enemyships["H"].status == 1) and (elixir[1] >= 5)) {
		int count = 0;
		while (count < 300) {
			srand((unsigned)time(NULL));
			int x1 = rand() % map_size + 1;
			int y1 = rand() % map_size + 1;
			for (int i = x1; i < (enemyships["H"].x2 - enemyships["H"].x1); i++) {
				for (int j = y1; j < (enemyships["H"].y2 - enemyships["H"].y1); j++) {
					if (enemy_seen[i][j] != "-") {
						count++;
						continue;
					}
				}
			}
			skills("enemy", enemy_real, enemy_seen, "move", enemyships["H"].x1, enemyships["H"].y1, x1, y1);
			cout << "enemy move finished" << endl;
			elixir[1] -= 5;
		}
	}
	//费用少:治疗
	if (elixir[1] >= 2 and elixir[1] <= 3) {
		//如果有受伤
		for (string i : {"H", "h", "K", "k", "Q", "q"}) {
			if (((enemyships[i].hp_max - enemyships[i].hp) >= 3)and enemyships[i].status == 1) {
				enemyships[i].hp += 2;
				elixir[1] -= 2;
				break;
			}
		}
	}
	//费用多:炸弹
	if (elixir[1] >= 4) {
		srand((unsigned)time(NULL));
		int direction = rand() % 2;
		//使用3x3炸弹
		if (direction == 0) {
			if (hit_grids.size() > 0) {
				Cor target = hit_grids[0];
				if (target.x + 1 > map_size) {
					target.x--;
				}
				if (target.x - 1 < 1) {
					target.x++;
				}
				if (target.y + 1 > map_size) {
					target.y--;
				}
				if (target.y - 1 < 1) {
					target.y++;
				}
				for (int i = target.x - 1; i <= target.x + 1; i++) {
					for (int j = target.y - 1; j <= target.y + 1; j++) {
						attack_detect("player", player_real, player_seen, i, j, 1);
						forbid_grids.push_back({ i,j });
					}
				}
				elixir[1] -= 3;
			}
			
		}
	}
	//进行普通打击
	for (torpedo_remain; torpedo_remain > 0; torpedo_remain--) {
		//有"X"并且forbid是0
		if ((hit_grids.size() > 0) and (forbid_grids.size() == 0)) {
			srand((unsigned)time(NULL));
			int chosen_grid = rand() % hit_grids.size() + 1;
			int x = empty_grids[chosen_grid].x;
			int y = empty_grids[chosen_grid].y;
			attack_detect("player", player_real, player_seen, x, y, 1);
			forbid_grids.push_back({ x,y });
			continue;
		}
		//有"X"并且forbid也有
		else if ((hit_grids.size() > 0)) {
			vector<Cor>::iterator itr1;
			vector<Cor>::iterator itr2;
			bool hit = 0;
			//遍历hit容器，找出不在一回合打击过的点
			for (itr1 = hit_grids.begin(); itr1 != hit_grids.end(); itr1++) {
				bool valid = 1;
				for (itr2 = forbid_grids.begin(); itr2 != forbid_grids.end(); itr2++) {
					if (((*itr1).x == (*itr2).x) or ((*itr1).y = (*itr2).y)) {
						valid = 0;
						break;
					}
				}
				if (valid) {
					attack_detect("player", player_real, player_seen, (*itr1).x, (*itr1).y, 1);
					hit = 1;
					break;
				}
			}
			//全部X都打过了
			if (hit == 0) {
				//打hit的右边
				for (itr1 = hit_grids.begin(); itr1 != hit_grids.end(); itr1++) {
					bool valid = 1;
					if ((*itr1).x + 1 > map_size)  continue;
					for (itr2 = forbid_grids.begin(); (itr2 != forbid_grids.end()); itr2++) {
						if (((*itr1).x + 1 == (*itr2).x) or ((*itr1).y == (*itr2).y)) {
							valid = 0;
							break;
						}
					}
					if (valid) {
						attack_detect("player", player_real, player_seen, (*itr1).x + 1, (*itr1).y, 1);
						hit = 1;
						break;
					}
				}
				//打hit的左边
				if (hit == 0) {
					for (itr1 = hit_grids.begin(); itr1 != hit_grids.end(); itr1++) {
						bool valid = 1;
						if ((*itr1).x - 1 < 1)  continue;
						for (itr2 = forbid_grids.begin(); (itr2 != forbid_grids.end()); itr2++) {
							if (((*itr1).x - 1 == (*itr2).x) or ((*itr1).y == (*itr2).y)) {
								valid = 0;
								break;
							}
						}
						if (valid) {
							attack_detect("player", player_real, player_seen, (*itr1).x - 1, (*itr1).y, 1);
							hit = 1;
							break;
						}
					}
				}
				//打hit的上边
				if (hit == 0) {
					for (itr1 = hit_grids.begin(); itr1 != hit_grids.end(); itr1++) {
						bool valid = 1;
						if ((*itr1).y + 1 > map_size)  continue;
						for (itr2 = forbid_grids.begin(); (itr2 != forbid_grids.end()); itr2++) {
							if (((*itr1).x == (*itr2).x) or ((*itr1).y + 1 == (*itr2).y)) {
								valid = 0;
								break;
							}
						}
						if (valid) {
							attack_detect("player", player_real, player_seen, (*itr1).x, (*itr1).y + 1, 1);
							hit = 1;
							break;
						}
					}
				}
				//打hit的下边
				if (hit == 0) {
					for (itr1 = hit_grids.begin(); itr1 != hit_grids.end(); itr1++) {
						bool valid = 1;
						if ((*itr1).y - 1 < 1)  continue;
						for (itr2 = forbid_grids.begin(); (itr2 != forbid_grids.end()); itr2++) {
							if (((*itr1).x == (*itr2).x) or ((*itr1).y - 1 == (*itr2).y)) {
								valid = 0;
								break;
							}
						}
						if (valid) {
							attack_detect("player", player_real, player_seen, (*itr1).x, (*itr1).y - 1, 1);
							hit = 1;
							break;
						}
					}
				}
			}
		}
		//随机目标
		else {
			srand((unsigned)time(NULL));
			int chosen_grid = rand() % empty_grids.size() + 1;
			int x = empty_grids[chosen_grid].x;
			int y = empty_grids[chosen_grid].y;
			attack_detect("player", player_real, player_seen, x, y, 1);
		}
	}
}