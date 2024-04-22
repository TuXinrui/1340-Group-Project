// attack_detection.h 
#ifndef ATTACK_H 
#define ATTACK_H
//把报废船或者建筑更新到地图上
void broken_update(string target, string item, string** ptr);
//检测目标玩家的船或者建筑是否报废
void broken_detect(string target, string item, string** ptr);
//输入打击对象，打击对象的地图，点的位置
void attack_detect(string target, string** ptr, int x, int y);
#endif 