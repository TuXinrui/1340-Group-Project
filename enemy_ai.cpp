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

void enemy_execute(string** player_real, string** player_seen, string** enemy_real,string** enemy_seen) {
	//������ͨ���
	for (torpedo_remain; torpedo_remain>0; torpedo_remain--) {
		srand((unsigned)time(NULL));
		int chosen_grid = rand() % empty_grids.size() + 1;
		int x = empty_grids[chosen_grid].x;
		int y = empty_grids[chosen_grid].y;
		attack_detect("player", player_real, player_seen, x, y, 1);
	}
	//����
	if ((enemyships["H"].hp <= 5) and (enemyships["H"].status == 1) and (elixir[1] >= 5)) {
		while (true) {
			srand((unsigned)time(NULL));
			int x1 = rand() % map_size + 1;
			int y1 = rand() % map_size + 1;
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 3; j++) {
					if (enemy_seen[i][j] != "-")  continue;
				}
			}
			move();
		}
	}
	//�����������
	else if (elixir[1] >= 1 and elixir[1] <= 2) {
		//���������
		for (string i : {"H", "h", "K", "k", "Q", "q"}) {
			if (((enemyships[i].hp_max - enemyships[i].hp) >= 3)and enemyships[i].status == 1) {
				enemyships[i].hp += 2;
				elixir[1] -= 2;
				break;
			}
		}
	}
	else if (elixir[1] >= 3 and elixir[1] <= 5) {

	}
}