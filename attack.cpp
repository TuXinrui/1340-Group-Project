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
using namespace std;


//�ѱ��ϴ����߽������µ���ͼ��
void broken_update(string target, string item, string** ptr) {

}
//���Ŀ����ҵĴ����߽����Ƿ񱨷�
void broken_detect(string target, string item, string ** ptr) {
	if (target == "player") {
		//������
		if ((playerships[item].hp <= 0) and ) {
			broken_update(target, item, ptr);
		}
	}
}

//���������󣬴������ĵ�ͼ�����λ��
void attack_detect(string target, string** ptr, int x, int y) {
	//�����
	if (ptr[x][y] == "O") {
		ptr[x][y] = "X";}
	else if (ptr[x][y] == "X") {
		cout << "Invalid attack, already attacked" << endl;
	}
	//Ŀ��player
	else if (target == "player") {
		//���˺�ĸ1
	    if (ptr[x][y] == "H") {
			ptr[x][y] = "X";
			playerships["H"].hp--;
			//���ϼ�⺯��
		}
		//���˺�ĸ2
		else if (ptr[x][y] == "h") {
			ptr[x][y] = "X";
			playerships["h"].hp--;
			//���ϼ�⺯��
		}
		//��������1
		else if (ptr[x][y] == "Q") {
			ptr[x][y] = "X";
			playerships["Q"].hp--;
			//���ϼ�⺯��
		}
		//��������2
		else if (ptr[x][y] == "q") {
			ptr[x][y] = "X";
			playerships["q"].hp--;
			//���ϼ�⺯��
		}
		//���˿Ƽ�1
		else if (ptr[x][y] == "K") {
			ptr[x][y] = "X";
			playerships["K"].hp--;
			//���ϼ�⺯��
		}
		//��������2
		else if (ptr[x][y] == "k") {
			ptr[x][y] = "X";
			playerships["k"].hp--;
			//���ϼ�⺯��
		}
		//����ʯ��1
		else if (ptr[x][y] == "S") {
			ptr[x][y] = "X";
			playerships["S"].hp--;
			//���ϼ�⺯��
		}
		//����ʯ��2
		else if (ptr[x][y] == "s") {
			ptr[x][y] = "X";
			playerships["s"].hp--;
			//���ϼ�⺯��
		}
		//���˻���1
		else if (ptr[x][y] == "D") {
			ptr[x][y] = "X";
			playerships["D"].hp--;
			//���ϼ�⺯��
		}
		//���˻���2
		else if (ptr[x][y] == "d") {
			ptr[x][y] = "X";
			playerships["d"].hp--;
			//���ϼ�⺯��
		}
	}
	
	//Ŀ��enemy
	else if (target == "player") {
		//���˺�ĸ1
		if (ptr[x][y] == "H") {
			ptr[x][y] = "X";
			enemyships["H"].hp--;
			//���ϼ�⺯��
		}
		//���˺�ĸ2
		else if (ptr[x][y] == "h") {
			ptr[x][y] = "X";
			enemyships["h"].hp--;
			//���ϼ�⺯��
		}
		//��������1
		else if (ptr[x][y] == "Q") {
			ptr[x][y] = "X";
			enemyships["Q"].hp--;
			//���ϼ�⺯��
		}
		//��������2
		else  if (ptr[x][y] == "q") {
			ptr[x][y] = "X";
			enemyships["q"].hp--;
			//���ϼ�⺯��
		}
		//���˿Ƽ�1
		else if (ptr[x][y] == "K") {
			ptr[x][y] = "X";
			enemyships["K"].hp--;
			//���ϼ�⺯��
		}
		//��������2
		else if (ptr[x][y] == "k") {
			ptr[x][y] = "X";
			enemyships["k"].hp--;
			//���ϼ�⺯��
		}
		//����ʯ��1
		else if (ptr[x][y] == "S") {
			ptr[x][y] = "X";
			enemyships["S"].hp--;
			//���ϼ�⺯��
		}
		//����ʯ��2
		else if (ptr[x][y] == "s") {
			ptr[x][y] = "X";
			enemyships["s"].hp--;
			//���ϼ�⺯��
		}
		//���˻���1
		else if (ptr[x][y] == "D") {
			ptr[x][y] = "X";
			enemyships["D"].hp--;
			//���ϼ�⺯��
		}
		//���˻���2
		else if (ptr[x][y] == "d") {
			ptr[x][y] = "X";
			enemyships["d"].hp--;
			//���ϼ�⺯��
		}
	}
}