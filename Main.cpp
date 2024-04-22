#include <iostream>
#include <cctype>	//character handling
#include <string>   //对string类
#include <fstream>  //对IO，ofstream写，ifstream读
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int elixir=0;  //cost
int elixir_max=6;
int turn=1;  //number of turns
struct Ship {
	int x;
	int y;
	bool r;  //direction of the ship, 0 for being horizontal and 1 for vertical
	int hp;
};
map<string, Ship> playerships;  //to store player's ships
map<string, Ship> enemyships;  //opponent's ships

int main() {
	//输入转换函数，获取用户的第一次输入

	//Big turn for player and enemy
	while (true) {
		//player turn
		while (true) {
			//输入转换函数xxxxxxxxxx
		}
		//enemy turn
		while (true) {
			//输入怪物函数
		}
		turn++;
	}
}