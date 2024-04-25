// attack_detection.h 
#include <string>
using namespace std;

//输入打击对象，打击对象的地图，点的位置
void attack_detect(string target, string** ptr_real, string** ptr_seen, int x, int y, int damage);
//把报废船或者建筑更新到地图上
void broken_update(string target, string item, string** ptr_seen);
//检测目标玩家的船或者建筑是否报废
void broken_detect(string target, string item, string** ptr_seen);
//使用攻击类型
void attack_input_conversion(string target, string** ptr_real, string** ptr_seen, string command, int x, int y, int damage);
//特殊技能
void skills(string target, string** ptr_real, string** ptr_seen, string command, int x1, int y1, int x2, int y2);

