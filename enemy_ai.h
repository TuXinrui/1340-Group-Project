// enemy_ai.h 
#include <string>
using namespace std;

//refresh empty and hit containers
void enemy_container(string** ptr_seen);
//execute the enemy turn
void enemy_execute(string** player_real, string** player_seen, string** enemy_real, string** enemy_seen);