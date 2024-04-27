#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "support.h"
using namespace std;

void battle_page_output(string** player_map, string** enemy_map){
    system("clear"); //清屏指令
    
    // 输出回合数
    cout << "当前回合: " << turn << endl;
    cout << endl;

    // 输出玩家信息
    cout << "玩家信息:" << endl;
    cout << "能量: " << elixir[0] << "/" << elixir_max[0] << "  能量增长: " << elixir_increament[0] << endl;
    cout << "攻击力加成: " << attack_buff[0] << endl;
    cout << "剩余鱼雷数: " << torpedo_remain << "/" << torpedo_max[0] << endl;
    cout << endl;

    // 输出敌人信息
    cout << "敌人信息:" << endl;
    cout << "能量: " << elixir[1] << "/" << elixir_max[1] << "  能量增长: " << elixir_increament[1] << endl;
    cout << "攻击力加成: " << attack_buff[1] << endl;
    cout << "剩余鱼雷数: " << torpedo_max[1] - torpedo_remain << "/" << torpedo_max[1] << endl;
    cout << endl;

    // 输出玩家地图和敌人地图
    cout << "玩家地图:";
    cout << string(map_size * 2, ' ');
    cout << "敌人地图:" << endl;
    for(int i=0; i<map_size; i++){
        for(int j=0; j<map_size; j++){
            cout << player_map[i][j] << " ";
        }
        cout << "  ";
        for(int j=0; j<map_size; j++){
            cout << enemy_map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 输出被攻击的格子
    cout << "被攻击的格子:" << endl;
    for(auto it=damaged_grids.begin(); it!=damaged_grids.end(); it++){
        cout << "(" << it->x << "," << it->y << ") ";
    }
    cout << endl << endl;

    // 输出玩家船只信息
    cout << "玩家船只信息:" << endl;
    for(auto it=playerships.begin(); it!=playerships.end(); it++){
        cout << it->first << ": ";
        cout << "位置(" << it->second.x1 << "," << it->second.y1 << ")到(";
        cout << it->second.x2 << "," << it->second.y2 << ") ";
        cout << "HP=" << it->second.hp << " ";
        cout << "状态:" << (it->second.status ? "存活" : "死亡") << endl;
    }
    cout << endl;

    // 输出敌人船只信息
    cout << "敌人船只信息:" << endl;
    for(auto it=enemyships.begin(); it!=enemyships.end(); it++){
        cout << it->first << ": ";
        cout << "位置(" << it->second.x1 << "," << it->second.y1 << ")到(";
        cout << it->second.x2 << "," << it->second.y2 << ") ";
        cout << "HP=" << it->second.hp << " ";
        cout << "状态:" << (it->second.status ? "存活" : "死亡") << endl;
    }
    cout << endl;

    // 输出对话框
    cout << "对话框:" << endl;
    cout << "-------------------------------" << endl;
    cout << dialogue << endl;
    cout << "-------------------------------" << endl;

    return;
}
