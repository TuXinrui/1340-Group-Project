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
#include <string>
using namespace std;
//refresh the empty and hit containers
void enemy_container(string** ptr_seen) {
	empty_grids.clear();
	hit_grids.clear();
	for (int i = 1; i <= map_size; i++) {
		for (int j = 1; j <= map_size; j++) {
			if (ptr_seen[i][j] != "X" and ptr_seen[i][j] != "O" and ptr_seen[i][j] != "B") {
				empty_grids.push_back({ i, j });
			}
			if (ptr_seen[i][j] == "X") {
				hit_grids.push_back({ i, j });
			}
		}
	}
}

void enemy_execute(string** player_real, string** player_seen, string** enemy_real, string** enemy_seen) {

	//emergent move for H
	if ((enemyships["H"].hp <= 5) and (enemyships["H"].status == 1) and (elixir[1] >= 5)) {
		bool valid = 0;
		for (int i = enemyships["H"].x1; i <= enemyships["H"].x2; i++) {
			for (int j = enemyships["H"].y1; j <= enemyships["H"].y2; j++) {
				if (enemy_seen[i][j] == "X") {
					valid == 1;
				}
			}
		}
		if (valid == 1) {
			int count = 0;
			while (count < 300) {
				srand((unsigned)time(NULL));
				int x1 = rand() % map_size + 1;
				int y1 = rand() % map_size + 1;
				bool valid = 1;
				for (int i = x1; i < (enemyships["H"].x2 - enemyships["H"].x1); i++) {
					if (valid) {
						for (int j = y1; j < (enemyships["H"].y2 - enemyships["H"].y1); j++) {
							if (enemy_seen[i][j] != "-") {
								count++;
								valid = 0;
								break;
							}
						}
					}
				}
				if (valid) {
					skills("enemy", enemy_real, enemy_seen, "move", enemyships["H"].x1, enemyships["H"].y1, x1, y1);
					cout << "enemy move finished" << endl;
					elixir[1] -= 5;
					break;
				}
			}
		}

	}
	//emergent move for h
	if ((enemyships["h"].hp <= 5) and (enemyships["h"].status == 1) and (elixir[1] >= 5)) {
		bool valid = 0;
		for (int i = enemyships["h"].x1; i <= enemyships["h"].x2; i++) {
			for (int j = enemyships["h"].y1; j <= enemyships["h"].y2; j++) {
				if (enemy_seen[i][j] == "X") {
					valid == 1;
				}
			}
		}
		if (valid == 1) {
			int count = 0;
			while (count < 300) {
				srand((unsigned)time(NULL));
				int x1 = rand() % map_size + 1;
				int y1 = rand() % map_size + 1;
				bool valid = 1;
				for (int i = x1; i < (enemyships["H"].x2 - enemyships["H"].x1); i++) {
					if (valid) {
						for (int j = y1; j < (enemyships["H"].y2 - enemyships["H"].y1); j++) {
							if (enemy_seen[i][j] != "-") {
								count++;
								valid = 0;
								break;
							}
						}
					}
				}
				if (valid) {
					skills("enemy", enemy_real, enemy_seen, "move", enemyships["h"].x1, enemyships["h"].y1, x1, y1);
					cout << "enemy move finished" << endl;
					elixir[1] -= 5;
					cout << "敌人移船H了" << endl;
					break;
				}
			}
		}

	}
	//heal
	if (elixir[1] >= 1 and elixir[1] <= 2) {
		//if wounded
		for (string i : {"H", "h", "K", "k", "Q", "q"}) {
			if (((enemyships[i].hp_max - enemyships[i].hp) >= 3) and enemyships[i].status == 1) {
				enemyships[i].hp += 3;
				elixir[1] -= 1;
				break;
			}
		}
	}
	//3x3 artillery
	if (elixir[1] >= 4) {
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
			cout << "使用33" << endl;
			for (int i = target.x - 1; i <= target.x + 1; i++) {
				for (int j = target.y - 1; j <= target.y + 1; j++) {
					cout << "正在打" << i << " " << j << endl;
					attack_detect("player", player_real, player_seen, i, j, 1);
					forbid_grids.push_back({ i,j });
					for (int i = map_size; i > 0; i--) {
						for (int j = 0; j <= map_size; j++) {
							cout << player_seen[i][j] << " ";
						}
						cout << endl;
					}
					cout << endl;
				}
			}
			enemy_container(player_seen);
			elixir[1] -= 4;
		}

	}
	//normal attack
	for (torpedo_remain; torpedo_remain > 0; torpedo_remain--) {
		//have "X" in hit container and forbid.size() == 0
		enemy_container(player_seen);
		if ((hit_grids.size() > 0) and (forbid_grids.size() == 0)) {
			attack_detect("player", player_real, player_seen, hit_grids[0].x, hit_grids[0].y, 1);
			forbid_grids.push_back({ hit_grids[0].x,hit_grids[0].y });
			continue;
		}
		//have "X" in container and forbid is not empty
		else if ((hit_grids.size() > 0)) {
			bool hit = 0;
			//walk through the hit container，find the grid not in forbid container
			for (int i = 0; i < hit_grids.size(); i++) {
				bool valid = 1;
				for (int j = 0; j < forbid_grids.size(); j++) {
					if ((hit_grids[i].x == forbid_grids[j].x) and (hit_grids[i].y == forbid_grids[j].y)) {
						valid = 0;
						break;
					}
				}
				if (valid) {
					attack_detect("player", player_real, player_seen, hit_grids[i].x, hit_grids[i].y, 1);
					hit = 1;
					break;
				}
			}
			//all X are covered in forbid container
			if (hit == 0) {
				//hit the right side of the X
				for (int i = 0; i < hit_grids.size(); i++) {
					bool valid = 1;
					if (hit_grids[i].x + 1 > map_size)  continue;
					for (int j = 0; j < forbid_grids.size(); j++) {
						if ((hit_grids[i].x + 1 == forbid_grids[j].x and (hit_grids[i].y == forbid_grids[j].y))) {
							valid = 0;
							break;
						}
					}
					if (valid) {
						attack_detect("player", player_real, player_seen, hit_grids[i].x + 1, hit_grids[i].y, 1);
						hit = 1;

						break;
					}
				}
				//hit the left side of the X
				if (hit == 0) {
					for (int i = 0; i < hit_grids.size(); i++) {
						bool valid = 1;
						if (hit_grids[i].x - 1 < 1)  continue;
						for (int j = 0; j < forbid_grids.size(); j++) {
							if ((hit_grids[i].x - 1 == forbid_grids[j].x and (hit_grids[i].y == forbid_grids[j].y))) {
								valid = 0;
								break;
							}
						}
						if (valid) {
							attack_detect("player", player_real, player_seen, hit_grids[i].x - 1, hit_grids[i].y, 1);
							hit = 1;
							break;
						}
					}
				}
				//hit the upper side of the X
				if (hit == 0) {
					for (int i = 0; i < hit_grids.size(); i++) {
						bool valid = 1;
						if (hit_grids[i].y + 1 > map_size)  continue;
						for (int j = 0; j < forbid_grids.size(); j++) {
							if ((hit_grids[i].x == forbid_grids[j].x) and (hit_grids[i].y + 1 == forbid_grids[j].y)) {
								valid = 0;
								break;
							}
						}
						if (valid) {
							attack_detect("player", player_real, player_seen, hit_grids[i].x, hit_grids[i].y + 1, 1);
							hit = 1;
							break;
						}
					}
				}
				//hit the lower side of the X
				if (hit == 0) {
					for (int i = 0; i < hit_grids.size(); i++) {
						bool valid = 1;
						if (hit_grids[i].y - 1 > map_size)  continue;
						for (int j = 0; j < forbid_grids.size(); j++) {
							if ((hit_grids[i].x == forbid_grids[j].x) and (hit_grids[i].y - 1 == forbid_grids[j].y)) {
								valid = 0;
								break;
							}
						}
						if (valid) {
							attack_detect("player", player_real, player_seen, hit_grids[i].x, hit_grids[i].y - 1, 1);
							hit = 1;

							break;
						}
					}
				}
			}
		}
		//random target otherwise
		else {
			srand((unsigned)time(NULL));
			int chosen_grid = rand() % empty_grids.size() + 1;
			int x = empty_grids[chosen_grid].x;
			int y = empty_grids[chosen_grid].y;
			attack_detect("player", player_real, player_seen, x, y, 1);
		}
	}
}