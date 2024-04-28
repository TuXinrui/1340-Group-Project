#include <iostream>
#include <cctype>	//character handling
#include <cstring>	//����C-string����ʾ�ַ������� '\0'��Ϊ�ַ����Ľ�����־
#include <string>   //��string��
#include <fstream>  //��IO��ofstreamд��ifstream��
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
//ˢ��empty��hit����������
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

void enemy_execute(string** player_real, string** player_seen, string** enemy_real, string** enemy_seen) {
	//�����ƶ�H
	if ((enemyships["H"].hp <= 5) and (enemyships["H"].status == 1) and (elixir[1] >= 5)) {
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
	//�����ƶ�h
	if ((enemyships["h"].hp <= 5) and (enemyships["h"].status == 1) and (elixir[1] >= 5)) {
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
				break;
			}
		}
	}
	//������:����
	if (elixir[1] >= 2 and elixir[1] <= 3) {
		//���������
		for (string i : {"H", "h", "K", "k", "Q", "q"}) {
			if (((enemyships[i].hp_max - enemyships[i].hp) >= 3) and enemyships[i].status == 1) {
				enemyships[i].hp += 2;
				elixir[1] -= 2;
				break;
			}
		}
	}
	//���ö�:3x3ը��
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
			for (int i = target.x - 1; i <= target.x + 1; i++) {
				for (int j = target.y - 1; j <= target.y + 1; j++) {
					attack_detect("player", player_real, player_seen, i, j, 1);
					forbid_grids.push_back({ i,j });
				}
			}
			elixir[1] -= 3;
		}
	}
	//������ͨ���
	for (torpedo_remain; torpedo_remain > 0; torpedo_remain--) {
		//��"X"����forbid��0
		if ((hit_grids.size() > 0) and (forbid_grids.size() == 0)) {
			srand((unsigned)time(NULL));
			int chosen_grid = rand() % hit_grids.size() + 1;
			int x = empty_grids[chosen_grid].x;
			int y = empty_grids[chosen_grid].y;
			attack_detect("player", player_real, player_seen, x, y, 1);
			forbid_grids.push_back({ x,y });
			continue;
		}
		//��"X"����forbidҲ��
		else if ((hit_grids.size() > 0)) {
			bool hit = 0;
			//����hit�������ҳ�����һ�غϴ�����ĵ�
			for (int i = 0; i < hit_grids.size(); i++) {
				bool valid = 1;
				for (int j = 0; j <= forbid_grids.size(); j++) {
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
			//ȫ��X�������
			if (hit == 0) {
				//��hit���ұ�
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
				//��hit�����
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
				//��hit���ϱ�
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
				//��hit���±�
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
		//���Ŀ��
		else {
			srand((unsigned)time(NULL));
			int chosen_grid = rand() % empty_grids.size() + 1;
			int x = empty_grids[chosen_grid].x;
			int y = empty_grids[chosen_grid].y;
			attack_detect("player", player_real, player_seen, x, y, 1);
		}
	}
}