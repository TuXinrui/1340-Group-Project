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
#include <string>
using namespace std;

int map_size=0;
int attack_buff = 0;
int elixir = 0;  //cost
int elixir_max = 6;
int turn = 0;  //number of turns
int torpedo_max = 2;
int torpedo_remain = torpedo_max;

vector <Cor> damaged_grids;  //to store the attacked points in one turn
 
map<string, Ship> playerships;  //to store player's ships
map<string, Ship> enemyships;  //opponent's ships

#include "support.h"
#include <iostream>
#include <cstdlib>

std::string** InitMap() {
    // 动态分配map_size*map_size的二维字符串数组
    std::string** seamap = new std::string*[map_size];
    std::string** fogmap = new std::string*[map_size];
    for(int i = 0; i < map_size; i++) {
        seamap[i] = new std::string[map_size];
        fogmap[i] = new std::string[map_size];
    }

    // 初始化地图上的水域
    for(int i = 0; i < map_size; i++) {
        for(int j = 0; j < map_size; j++) {
            seamap[i][j] = "-"; 
            fogmap[i][j] = "~";
        }
    }

    // 玩家放置船只
    for(auto& ship : playerships) {
        while(true) {
            int x, y, r;
            std::cout << "请为 " << ship.first << " 输入位置 (x, y) 和方向 (0为横向, 1为纵向): ";
            std::cin >> x >> y >> r;

            // 检查位置是否合法
            if(x < 0 || x >= map_size || y < 0 || y >= map_size) {
                std::cout << "位置不合法!请重试。" << std::endl;
                continue;
            }

            // 检查方向是否合法
            if(r != 0 && r != 1) {
                std::cout << "方向不合法!请输入0表示横向或1表示纵向。" << std::endl;
                continue;
            }

            // 检查船只是否超出地图边界或与其他船只重叠
            bool isValid = true;
            int shipSize = ship.second.x2 - ship.second.x1 + 1;
            switch(r) {
                case 0: // 横向
                    if(y + shipSize > map_size) {
                        isValid = false;
                        break;
                    }
                    for(int i = 0; i < shipSize; i++) {
                        if(seamap[x][y+i] != "-") {
                            isValid = false;
                            break;
                        }
                    }
                    break;
                case 1: // 纵向
                    if(x + shipSize > map_size) {
                        isValid = false;
                        break;  
                    }
                    for(int i = 0; i < shipSize; i++) {
                        if(seamap[x+i][y] != "-") {
                            isValid = false;
                            break;
                        }
                    }
                    break;
            }

            if(!isValid) {
                std::cout << "船只放置不合法!请重试。" << std::endl;
                continue;
            }

            // 放置船只
            ship.second.x1 = x;
            ship.second.y1 = y;
            char shipChar = ship.first[0];
            switch(r) {
                case 0: // 横向
                    ship.second.x2 = x;
                    ship.second.y2 = y + shipSize - 1;
                    for(int i = 0; i < shipSize; i++) {
                        seamap[x][y+i] = shipChar;
                    }
                    break;
                case 1: // 纵向
                    ship.second.x2 = x + shipSize - 1;
                    ship.second.y2 = y;
                    for(int i = 0; i < shipSize; i++) {
                        seamap[x+i][y] = shipChar;  
                    }
                    break;
            }
            break;
        }
    }

    // 敌人随机放置船只
    for(auto& ship : enemyships) {
        while(true) {
            int x = rand() % map_size;
            int y = rand() % map_size;
            int r = rand() % 2;
            int shipSize = ship.second.x2 - ship.second.x1 + 1;

            // 检查船只是否超出地图边界或与其他船只重叠
            bool isValid = true;
            switch(r) {
                case 0: // 横向
                    if(y + shipSize > map_size) {
                        isValid = false;
                        break;
                    }
                    for(int i = 0; i < shipSize; i++) {
                        if(seamap[x][y+i] != "-") {
                            isValid = false;
                            break;
                        }
                    }
                    break;
                case 1: // 纵向 
                    if(x + shipSize > map_size) {
                        isValid = false;
                        break;
                    }
                    for(int i = 0; i < shipSize; i++) {
                        if(seamap[x+i][y] != "-") {
                            isValid = false;
                            break;
                        }
                    }
                    break;
            }

            if(!isValid) {
                continue;
            }

            // 放置船只
            ship.second.x1 = x;
            ship.second.y1 = y;
            switch(r) {
                case 0: // 横向
                    ship.second.x2 = x;
                    ship.second.y2 = y + shipSize - 1;
                    break;
                case 1: // 纵向
                    ship.second.x2 = x + shipSize - 1;
                    ship.second.y2 = y;
                    break;
            }
            break;
        }
    }

    return seamap;
}
