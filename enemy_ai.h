// enemy_ai.h 
#include <string>
using namespace std;

//刷新empty和hit这两个容器
void enemy_container(string** ptr_seen);
//执行怪物回合
void enemy_execute(string** player_real, string** player_seen, string** enemy_real, string** enemy_seen);