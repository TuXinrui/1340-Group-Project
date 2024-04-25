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
using namespace std;

//�ѱ��ϴ����߽������µ���ͼ�ϣ��˴�ָ�붼��seen
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

//���Ŀ����ҵĴ����߽����Ƿ񱨷ϣ��˴�ָ�붼��seen
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

//���������󣬴������ĵ�ͼ�����λ�ã�ptr_real����ʵ���� ptr_seen�ǿ�����
void attack_detect(string target, string** ptr_real,string ** ptr_seen, int x, int y, int damage) {
	//Ŀ��player
	if (target == "player") {
		//�����
		if (ptr_real[x][y] == "-") {
			ptr_seen[x][y] = "O";
		}

		//���˺�ĸ1
		if (ptr_real[x][y] == "H") {
			ptr_seen[x][y] = "X";
			playerships["H"].hp -= damage;
			broken_detect(target, "H", ptr_seen);
		}
		//���˺�ĸ2
		else if (ptr_real[x][y] == "h") {
			ptr_seen[x][y] = "X";
			playerships["h"].hp -= damage;
			broken_detect(target, "h", ptr_seen);
		}
		//��������1
		else if (ptr_real[x][y] == "Q") {
			ptr_seen[x][y] = "X";
			playerships["Q"].hp -= damage;
			broken_detect(target, "Q", ptr_seen);
		}
		//��������2
		else if (ptr_real[x][y] == "q") {
			ptr_seen[x][y] = "X";
			playerships["q"].hp -= damage;
			broken_detect(target, "X", ptr_seen);
		}
		//���˿Ƽ�1
		else if (ptr_real[x][y] == "K") {
			ptr_seen[x][y] = "X";
			playerships["K"].hp -= damage;
			broken_detect(target, "K", ptr_seen);
		}
		//��������2
		else if (ptr_real[x][y] == "k") {
			ptr_seen[x][y] = "X";
			playerships["k"].hp -= damage;
			broken_detect(target, "k", ptr_seen);
		}
		//����ʯ��1
		else if (ptr_real [x] [y] == "S") {
			ptr_seen[x][y] = "X";
			playerships["S"].hp -= damage;
			broken_detect(target, "S", ptr_seen);
		}
		//����ʯ��2
		else if (ptr_real[x][y] == "s") {
			ptr_seen[x][y] = "X";
			playerships["s"].hp -= damage;
			broken_detect(target, "s", ptr_seen);
		}
		//���˻���1
		else if (ptr_real[x][y] == "D") {
			ptr_seen[x][y] = "X";
			playerships["D"].hp -= damage;
			broken_detect(target, "D", ptr_seen);
		}
		//���˻���2
		else if (ptr_real[x][y] == "d") {
			ptr_seen[x][y] = "X";
			playerships["d"].hp -= damage;
			broken_detect(target, "d", ptr_seen);
		}
	}
	
	//Ŀ��enemy
	else if (target == "enemy") {
		//�����
		if (ptr_real[x][y] == "-") {
			ptr_seen[x][y] = "O";
		}
		//���˺�ĸ1
		if (ptr_real[x][y] == "H") {
			ptr_seen[x][y] = "X";
			enemyships["H"].hp -= damage;
			broken_detect(target, "H", ptr_seen);
		}
		//���˺�ĸ2
		else if (ptr_real[x][y] == "h") {
			ptr_seen[x][y] = "X";
			enemyships["h"].hp -= damage;
			broken_detect(target, "h", ptr_seen);
		}
		//��������1
		else if (ptr_real[x][y] == "Q") {
			ptr_seen[x][y] = "X";
			enemyships["Q"].hp -= damage;
			broken_detect(target, "Q", ptr_seen);
		}
		//��������2
		else  if (ptr_real[x][y] == "q") {
			ptr_seen[x][y] = "X";
			enemyships["q"].hp -= damage;
			broken_detect(target, "q", ptr_seen);
		}
		//���˿Ƽ�1
		else if (ptr_real[x][y] == "K") {
			ptr_seen[x][y] = "X";
			enemyships["K"].hp -= damage;
			broken_detect(target, "K", ptr_seen);
		}
		//��������2
		else if (ptr_real[x][y] == "k") {
			ptr_seen[x][y] = "X";
			enemyships["k"].hp -= damage;
			broken_detect(target, "k", ptr_seen);
		}
		//����ʯ��1
		else if (ptr_real[x][y] == "S") {
			ptr_seen[x][y] = "X";
			enemyships["S"].hp -= damage;
			broken_detect(target, "S", ptr_seen);
		}
		//����ʯ��2
		else if (ptr_real[x][y] == "s") {
			ptr_seen[x][y] = "X";
			enemyships["s"].hp -= damage;
			broken_detect(target, "s", ptr_seen);
		}
		//���˻���1
		else if (ptr_real[x][y] == "D") {
			ptr_seen[x][y] = "X";
			enemyships["D"].hp -= damage;
			broken_detect(target, "D", ptr_seen);
		}
		//���˻���2
		else if (ptr_real[x][y] == "d") {
			ptr_seen[x][y] = "X";
			enemyships["d"].hp -= damage;
			broken_detect(target, "d", ptr_seen);
		}
	}
}

void attack_input_conversion(string target, string** ptr_real,string **ptr_seen, string command, int x, int y, int damage) {
	if (target == "player") {
		//����
		if (command == "torpedo") attack_detect("player", ptr_real,ptr_seen, x, y, 1+attack_buff[0]);
		//��
		if (command == "artillery") {
			for (int i = x - 1; i <= x + 1; i++) {
				for (int j = y - 1; j <= y + 1; j++) {
					attack_detect("player", ptr_real, ptr_seen,i, j, 1 + attack_buff[0]);
				}
			}
		}
		//����
		if (command == "missile") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("player", ptr_real, ptr_seen, i, j, 1 + attack_buff[0]);
				}
			}
		}
		//�˵�
		if (command == "nuclear") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("player", ptr_real, ptr_seen, i, j, 2 + attack_buff[0]);
				}
			}
		}
	}//���˻غ�
	else {
		//����
		if (command == "torpedo")  attack_detect("enemy", ptr_real, ptr_seen, x, y, 1 + attack_buff[1]);
		//����
		if (command == "artillery") {
			for (int i = x - 1; i <= x + 1; i++) {
				for (int j = y - 1; j <= y + 1; j++) {
					attack_detect("enemy", ptr_real, ptr_seen, i, j, 1 + attack_buff[1]);
				}
			}
		}
		//����
		if (command == "missile") {
			for (int i = x - 2; i <= x + 2; i++) {
				for (int j = y - 2; j <= y + 2; j++) {
					attack_detect("enemy", ptr_real, ptr_seen, i, j, 1 + attack_buff[1]);
				}
			}
		}
		//�˵�
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