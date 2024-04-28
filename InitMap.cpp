#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

struct Ship {
    int x1, y1, x2, y2;
    int hp;
    bool status;
};

std::map<std::string, Ship> playerships;
std::map<std::string, Ship> enemyships;
int map_size = 15;

void InitMap(std::string** playerMap, std::string** playerSeaMap, std::string** fogMap, std::string** enemyMap) {
    // 初始化地图上的水域
    for(int i = 0; i < map_size; i++) {
        for(int j = 0; j < map_size; j++) {
            playerMap[i][j] = "-"; 
            playerSeaMap[i][j] = "-";
            fogMap[i][j] = "~";
            enemyMap[i][j] = "-";
        }
    }

    // 玩家船只放置
    std::vector<std::tuple<std::string, int, int, int>> ships = {
        {"H", 10, 3, 7}, {"h", 10, 3, 7}, {"Q", 3, 1, 5}, {"q", 3, 1, 5}, {"K", 2, 1, 4}, {"k", 2, 1, 4}
    };
    for(auto& ship : ships) {
        std::string shipName = std::get<0>(ship);
        int shipHP = std::get<1>(ship);
        int shipHeight = std::get<2>(ship);
        int shipWidth = std::get<3>(ship);
        
        while(true) {
            int x, y;
            std::string direction;
            std::cout << "请输入船只 " << shipName << " 的左下角放置坐标x y (用空格分隔): ";
            std::cin >> x >> y;
            std::cout << "请输入船只 " << shipName << " 的放置方向 (h为横向,v为纵向): ";
            std::cin >> direction;

            // 检查船只是否超出地图边界
            if(direction == "h" && y + shipWidth > map_size) {
                std::cout << "船只 " << shipName << " 放置失败,超出地图边界!" << std::endl;
                continue;
            }
            if(direction == "v" && x + shipHeight > map_size) {
                std::cout << "船只 " << shipName << " 放置失败,超出地图边界!" << std::endl;
                continue;
            }
            
            // 检查船只是否与其他船只重叠
            bool isOverlap = false;
            if(direction == "h") {
                for(int j = y; j < y + shipWidth; j++) {
                    if(playerMap[x][j] != "-") {
                        isOverlap = true;
                        break;
                    }
                }
            } else {
                for(int i = x; i < x + shipHeight; i++) {
                    if(playerMap[i][y] != "-") {
                        isOverlap = true;
                        break;
                    }
                }
            }
            if(isOverlap) {
                std::cout << "船只 " << shipName << " 放置失败,与其他船只重叠!" << std::endl;
                continue;
            }

            // 放置船只
            if(direction == "h") {
                for(int j = y; j < y + shipWidth; j++) {
                    playerMap[x][j] = shipName;
                    playerSeaMap[x][j] = shipName;
                }
                playerships[shipName] = {x, y, x, y+shipWidth-1, shipHP, true};
            } else {
                for(int i = x; i < x + shipHeight; i++) {
                    playerMap[i][y] = shipName;
                    playerSeaMap[i][y] = shipName;
                }
                playerships[shipName] = {x, y, x+shipHeight-1, y, shipHP, true};
            }
            break;
        }
    }

    // 敌人随机放置船只
    srand(time(0));  // 设置随机数种子
    std::vector<std::tuple<std::string, int, int, int>> enemyShips = {
        {"H", 10, 3, 7}, {"h", 10, 3, 7}, {"Q", 3, 1, 5}, {"q", 3, 1, 5}, {"K", 2, 1, 4}, {"k", 2, 1, 4}
    };
    for(auto& ship : enemyShips) {
        std::string shipName = std::get<0>(ship);
        int shipHP = std::get<1>(ship);
        int shipHeight = std::get<2>(ship);
        int shipWidth = std::get<3>(ship);
        
        while(true) {
            int x = rand() % (map_size - shipHeight + 1);
            int y = rand() % (map_size - shipWidth + 1);
            std::string direction = rand() % 2 == 0 ? "h" : "v";

            // 检查船只是否与其他船只重叠
            bool isOverlap = false;
            if(direction == "h") {
                for(int j = y; j < y + shipWidth; j++) {
                    if(enemyMap[x][j] != "-") {
                        isOverlap = true;
                        break;
                    }
                }
            } else {
                for(int i = x; i < x + shipHeight; i++) {
                    if(enemyMap[i][y] != "-") {
                        isOverlap = true;
                        break;
                    }
                }
            }
            if(isOverlap) {
                continue;
            }

            // 放置船只
            if(direction == "h") {
                for(int j = y; j < y + shipWidth; j++) {
                    enemyMap[x][j] = shipName;
                }
                enemyships[shipName] = {x, y, x, y+shipWidth-1, shipHP, true};
            } else {
                for(int i = x; i < x + shipHeight; i++) {
                    enemyMap[i][y] = shipName;
                }
                enemyships[shipName] = {x, y, x+shipHeight-1, y, shipHP, true};
            }
            break;
        }
    }
}
