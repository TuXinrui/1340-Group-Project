// attack_detection.h 
#include <string>
using namespace std;

//check the real map of the attacking grid, for enemy or for player
void attack_detect(string target, string** ptr_real, string** ptr_seen, int x, int y, int damage);
//update the broken ships onto the map
void broken_update(string target, string item, string** ptr_seen);
//check whether the ship is broken
void broken_detect(string target, string item, string** ptr_seen);
//convert user input lines into commands
void attack_input_conversion(string target, string** ptr_real, string** ptr_seen, string command, int x, int y, int damage);
//for special skills
void skills(string target, string** ptr_real, string** ptr_seen, string command, int x1, int y1, int x2, int y2);

