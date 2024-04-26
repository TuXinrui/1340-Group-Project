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

std::tuple<std::string**, std::string**, std::string**, std::string**> InitMap() {
    // 动态分配map_size*map_size的二维字符串数组
    std::string** playerMap = new std::string*[map_size];
    std::string** playerSeaMap = new std::string*[map_size];
    std::string** fogMap = new std::string*[map_size];
    std::string** enemyMap = new std::string*[map_size];
    for(int i = 0; i < map_size; i++) {
        playerMap[i] = new std::string[map_size];
        playerSeaMap[i] = new std::string[map_size];
        fogMap[i] = new std::string[map_size];
        enemyMap[i] = new std::string[map_size];
    }

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
    int x = 0, y = 0;
    for(auto& ship : ships) {
        std::string shipName = std::get<0>(ship);
        int shipHP = std::get<1>(ship);
        int shipHeight = std::get<2>(ship);
        int shipWidth = std::get<3>(ship);
        
        // 检查船只是否超出地图边界
        if(x + shipHeight > map_size || y + shipWidth > map_size) {
            std::cout << "船只 " << shipName << " 放置失败,超出地图边界!" << std::endl;
            continue;
        }
        
        // 放置船只
        for(int i = x; i < x + shipHeight; i++) {
            for(int j = y; j < y + shipWidth; j++) {
                playerMap[i][j] = shipName;
                playerSeaMap[i][j] = shipName;
            }
        }
        playerships[shipName] = {x, y, x+shipHeight-1, y+shipWidth-1, shipHP, true};
        
        y += shipWidth + 1;
        if(y >= map_size) {
            x += 3;
            y = 0;
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

            // 检查船只是否与其他船只重叠
            bool isOverlap = false;
            for(int i = x; i < x + shipHeight; i++) {
                for(int j = y; j < y + shipWidth; j++) {
                    if(enemyMap[i][j] != "-") {
                        isOverlap = true;
                        break;
                    }
                }
                if(isOverlap) break;
            }
            if(isOverlap) {
                continue;
            }

            // 放置船只
            for(int i = x; i < x + shipHeight; i++) {
                for(int j = y; j < y + shipWidth; j++) {
                    enemyMap[i][j] = shipName;
                }
            }
            enemyships[shipName] = {x, y, x+shipHeight-1, y+shipWidth-1, shipHP, true};
            break;
        }
    }

     return {playerMap, playerSeaMap, fogMap, enemyMap};
}
