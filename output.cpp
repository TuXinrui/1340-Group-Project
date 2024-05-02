#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "support.h"
#include "output.h"
using namespace std;

// define constant code of colors
const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string YELLOW = "\033[1;33m";
const string BLUE = "\033[1;34m";
const string MAGENTA = "\033[1;35m";
const string CYAN = "\033[1;36m";
const string RESET = "\033[0m";

void battle_page_output(string** player_map, string** enemy_map) {
    system("clear"); //clear the screen for better gaming experience

    // output number of turns
    cout << YELLOW << "Turn: " << turn << RESET << endl;

    // output player's information
    cout << GREEN << "Player Info:" << RESET << "   ";
    cout << "Elixir: " << elixir[0] << "/" << elixir_max[0] << "   Elixir Gain per Turn: " << elixir_increament[0] << "   ";
    cout << "Torpedo: " << torpedo_remain << "/" << torpedo_max[0] << endl;

    cout << MAGENTA << "Command costs (Elixir):" << RESET << endl;
    cout << "Heal: 2   Elixir drill: 5   Attack: (Torpedo: 0   Artillery: 3   Missile: 5   Nuclear: 8)" << endl;

    // output player map and enemy 
    cout << GREEN << "Player Map:" << RESET;
    cout << string(map_size * 2 - 6, ' ');
    cout << RED << "Enemy Map:" << RESET << endl;
    //output the map with coordinates and varies colors:
    cout << YELLOW << " Y" << string(map_size * 2 + 3, ' ') << " Y" << RESET<<endl;
    for (int i = map_size; i > 0; i--) {
        if (i < 10) {
            cout << " " << YELLOW << i << RESET << " ";
        }
        else {
            cout << YELLOW << i << RESET << " ";
        }
        for (int j = 1; j <= map_size; j++) {
            if (player_map[i][j] == "-") {
                cout << BLUE << player_map[i][j] << RESET << " ";
            }
            else if (player_map[i][j] == "X") {
                cout << MAGENTA << player_map[i][j] << RESET << " ";
            }
            else if (player_map[i][j] == "O") {
                cout << GREEN << player_map[i][j] << RESET << " ";
            }
            else {
                if (playerships[player_map[i][j]].status == 1) {
                    cout << player_map[i][j] << " ";
                }
                else {
                    cout << RED << player_map[i][j] << RESET << " ";
                }
            }
        }
        cout << "  ";
        if (i < 10) {
            cout << " " << YELLOW << i << RESET << " ";
        }
        else {
            cout << YELLOW << i << RESET << " ";
        }
        for (int j = 1; j <= map_size; j++) {
            if (enemy_map[i][j] == "-") {
                cout << BLUE << enemy_map[i][j] << RESET << " ";
            }
            else if (enemy_map[i][j] == "X") {
                cout << MAGENTA << enemy_map[i][j] << RESET << " ";
            }
            else if (enemy_map[i][j] == "O") {
                cout << GREEN << enemy_map[i][j] << RESET << " ";
            }
            else {
                if (enemyships[enemy_map[i][j]].status == 1) {
                    cout << enemy_map[i][j] << " ";
                }
                else {
                    cout << RED << enemy_map[i][j] << RESET << " ";
                }
            }
        }
        cout << endl;
    }
    //output x-axis:
    cout << " ";
    for (int i = 0; i <= map_size; i++) {
        if (i < 10) {
            cout << YELLOW << i << RESET << " ";
        }
        else {
            cout << YELLOW << i / 10 << RESET << " ";
        }
    }
    cout << YELLOW << "X" << RESET;
    cout << "  ";
    for (int i = 0; i <= map_size; i++) {
        if (i < 10) {
            cout << YELLOW << i << RESET << " ";
        }
        else {
            cout << YELLOW << i / 10 << RESET << " ";
        }
    }
    cout << YELLOW << "X" << RESET << endl;
    cout << string(21, ' ');
    for (int i = 10; i <= map_size; i++) {
        cout << YELLOW << i % 10 << RESET << " ";
    }
    cout << string(23, ' ');
    for (int i = 10; i <= map_size; i++) {
        cout << YELLOW << i % 10 << RESET << " ";
    }
    cout << endl;

    // output the attacked grids this turn, (to inform the player not to attack these grids
    cout << MAGENTA << "Enemy Grids Attacked This Turn:" << RESET << endl;
    for (auto it = damaged_grids.begin(); it != damaged_grids.end(); it++) {
        cout << "(" << it->x << "," << it->y << ") ";
    }
    cout << endl << endl;

    // output player ship information
    cout << GREEN << "Player Ship Info:" << RESET << endl;
    for (auto it = playerships.begin(); it != playerships.end(); it++) {
        
        
        if (it->first != "S" && it->first != "s" && it->first != "B") {
            cout << it->first << ": ";
            if (it->second.status) {
                cout << "HP=" << it->second.hp << "  ";
            }
            else {
                cout << "Status: " << RED << "Damaged" << RESET << "  ";
            
            }
        }
        
    }
    cout << endl;

    // output the enemy 
    cout << RED << "Enemy Ship Info" << RESET << endl;
    for (auto it = enemyships.begin(); it != enemyships.end(); it++) {
        if (it->second.status) {
            cout << it->first << ": "  << "Not Damaged" <<" ";
        }
        else {
            cout << it->first << ": " << RED << "Damaged" << RESET << "  ";
        }
    }
    cout << endl;

    // output the "chatbox"
    cout << BLUE << "Enter here: " << RESET << endl;
    cout << "-------------------------------" << endl;

    return;
}