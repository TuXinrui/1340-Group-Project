// enemy_ai.h 
#include <string>
using namespace std;

//ˢ��empty��hit����������
void enemy_container(string** ptr_seen);
//ִ�й���غ�
void enemy_execute(string** player_real, string** player_seen, string** enemy_real, string** enemy_seen);