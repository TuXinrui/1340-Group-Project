#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include "support.h"
//#include <windows.h>
using namespace std;
//define the constant of colors
const string RED = "\033[1;31m";
const string GREEN = "\033[1;32m";
const string YELLOW = "\033[1;33m";
const string BLUE = "\033[1;34m";
const string MAGENTA = "\033[1;35m";
const string CYAN = "\033[1;36m";
const string RESET = "\033[0m";

void show_map(string ** real) {
    //output the player map with coordinates
    cout <<YELLOW<< " Y" <<RESET<< endl;
    
    for (int i = map_size; i > 0; i--) {
        if (i < 10) {
            cout << " " << YELLOW << i << RESET << " ";
        }
        else {
            cout << YELLOW << i << RESET << " ";
        }
        for (int j = 1; j <= map_size; j++) {
            if (real[i][j] == "-") {
                cout << BLUE << real[i][j] << RESET << " ";
            }
            else {
                cout << real[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << " ";
    for (int i = 0; i <= map_size; i++) {
        if (i < 10) {
            cout << YELLOW << i << RESET << " ";
        }
        else {
            cout << YELLOW << i/10 << RESET << " ";
        }
    }
    cout << YELLOW << "X" << RESET << endl;
    cout << string(21, ' ');
    for (int i = 10; i <= map_size; i++) {
        cout << YELLOW << i % 10 << RESET << " ";
    }
    cout << endl;
}

void InitMap(string** & player_real, string** & player_seen, string** & enemy_real, string** & enemy_seen) {
    // initialize the pointers
    player_real = new std::string * [map_size + 1];
    player_seen = new std::string * [map_size + 1];
    enemy_real = new std::string * [map_size + 1];
    enemy_seen = new std::string * [map_size + 1];
    for (int i = 0; i <= map_size; i++) {
        player_real[i] = new std::string[map_size + 1];
        player_seen[i] = new std::string[map_size + 1];
        enemy_real[i] = new std::string[map_size + 1];
        enemy_seen[i] = new std::string[map_size + 1];
    }

    // "-" represents water
    for (int i = 1; i <= map_size; i++) {
        for (int j = 1; j <= map_size; j++) {
            player_real[i][j] = "-";
            player_seen[i][j] = "-";
            enemy_real[i][j] = "-";
            enemy_seen[i][j] = "-";
        }
    }
    
    vector<tuple<string, int, int, int>> ships = {
        {"H", 20, 3, 7}, {"h", 20, 3, 7}, {"Q", 5, 1, 5}, {"q", 5, 1, 5}, {"K", 4, 1, 4}, {"k", 4, 1, 4}
    };
    string tmp_cor;    //stores the temporary input of coordinates and storation of direction;
    int tmp_cor_len, space_num;     //stores the length of coordinates input
    bool input_valid;   //indicates whether the input is valid, 1 for valid and 0 for invalid.
    int x, y, r=-1;   //stores the coordinates
    system("clear");
    show_map(player_real);
    for (auto& ship : ships) {
        //store the ship information
        string shipName = get<0>(ship);
        int shipHP = get<1>(ship);
        int shipHeight = get<2>(ship);
        int shipWidth = get<3>(ship);
        while (1) {
            tmp_cor = { "" };
            input_valid = 1;
            x = 0;
            y = 0;
            space_num = 0;
            cout << "please input the coordinates and value of " << GREEN << shipName << RESET << " ship.\n";
            cout << "e.g. " << YELLOW << "\"4 6 0\"" << RESET << " means to put the ship at coordinates " << YELLOW << "y = 4, x = 6" << RESET << " in the " << YELLOW << "horizontal " << RESET << "direction\n";
            cout << "     " << YELLOW << "\"4 6 1\"" << RESET << " means to put the ship at coordinates " << YELLOW << "y = 4, x = 6" << RESET << " in the " << YELLOW << "vertical " << RESET << "direction\n";
            getline(cin,tmp_cor);
            tmp_cor_len = tmp_cor.length();
            for (int i = 0; i < tmp_cor_len; i++) { //input valid check
                if (i == 0 && tmp_cor[i] == ' ') {
                    while (1) {
                        if (tmp_cor[i + 1] == ' ') {
                            i++;
                            continue;
                        }
                        else {
                            break;
                        }
                    }
                }
                else if (tmp_cor[i] == ' ') {
                    space_num += 1;
                    while (1) {
                        if (tmp_cor[i + 1] == ' ') {
                            i++;
                            continue;
                        }
                        else {
                            break;
                        }
                    }
                }
                else if (tmp_cor[i] < 48 || tmp_cor[i] > 57) { //coordinates have to be numbers
                    cout << "Invalid input, please enter again.\n";
                    input_valid = 0;
                    break;
                }
                else {
                    if (space_num == 0) {
                        x *= 10;
                        x += (tmp_cor[i] - 48);
                    }
                    else if (space_num == 1) {
                        y *= 10;
                        y += (tmp_cor[i] - 48);
                    }
                    else if (space_num == 2) {
                        r = (tmp_cor[i] - 48);
                    }
                    else {
                        cout << "Invalid input, please enter again.\n"; //too many input items
                        input_valid = 0;
                        break;
                    }
                }
            }
            if (input_valid == 0) {
                continue;
            }
            if (space_num < 2) {
                cout << "Invalid input, please enter again.\n"; //insufficient input items
                continue;
            }
            //boundary check
                //the coordinates and direction are numbers
            if (r != 1 && r != 0) {   //invalid direction;
                cout << "Invalid direction.\n";
                input_valid = 0;
            }
            if (r == 0 && (x + shipHeight-1 > map_size || y + shipWidth-1 > map_size)) {
                cout << "Ship " << shipName << " is out of boundary.\n" << std::endl;
                input_valid = 0;  
            }
            else if (r == 1 && (x + shipWidth-1 > map_size || y + shipHeight-1 > map_size)) {
                cout << "Ship " << shipName << " is out of boundary.\n" << std::endl;
                input_valid = 0;
            }
            //detect if the new ship overlaps with other ships
            if (r == 0 && input_valid==1) { //horizontally placed
                for (int i = x; i < x + shipHeight; i++) {
                    for (int j = y; j < y + shipWidth; j++) {
                        if (player_real[i][j] != "-") {
                            cout << "Ship " << shipName << " overlaps with other ships.\n";
                            input_valid = 0;
                            j = y + shipWidth;
                            i = x + shipHeight;
                        }
                    }
                }
            }
            else if ( r==1 && input_valid==1){ //vertically placed
                for (int i = x; i < x + shipWidth; i++) {
                    for (int j = y; j < y + shipHeight; j++) {
                        if (player_real[i][j] != "-") {
                            cout << "Ship " << shipName << " overlaps with other ships.\n";
                            input_valid = 0;
                            j = y + shipHeight;
                            i = x + shipWidth;
                        }
                    }
                }
            }
            if (input_valid == 1) {
                break;
            }
        }
        //valid, place the ships onto the map and store the information into the global container
        if (r == 0) {
            for (int i = x; i < x + shipHeight; i++) {
                for (int j = y; j < y + shipWidth; j++) {
                    player_real[i][j] = shipName;
                    player_seen[i][j] = shipName;
                }
            }
            playerships[shipName] = { x, y, x + shipHeight - 1, y + shipWidth - 1, shipHP, shipHP,true };
        }
        else {
            for (int i = x; i < x + shipWidth; i++) {
                for (int j = y; j < y + shipHeight; j++) {
                    player_real[i][j] = shipName;
                    player_seen[i][j] = shipName;
                }
            }
            playerships[shipName] = { x, y, x + shipWidth - 1, y + shipHeight - 1, shipHP, shipHP,true };
        }
        system("clear");
        show_map(player_real);
    }

    //randomly generate enemy ships
    srand(time(0));  // seed of random number based on system time
    vector<tuple<string, int, int, int>> enemyShips = {
        {"H", 20, 3, 7}, {"h", 20, 3, 7}, {"Q", 5, 1, 5}, {"q", 5, 1, 5}, {"K", 4, 1, 4}, {"k", 4, 1, 4}
    };
    for (auto& ship : enemyShips) {
        string shipName = get<0>(ship);
        int shipHP = get<1>(ship);
        int shipHeight = get<2>(ship);
        int shipWidth = get<3>(ship);
        int r = rand() % (2);
        while (true) {
            if (r == 0) {//place the ship horizontally
                int x = rand() % (map_size - shipHeight + 1);
                int y = rand() % (map_size - shipWidth + 1);
                bool isOverlap = false;
                for (int i = x; i < x + shipHeight; i++) {
                    for (int j = y; j < y + shipWidth; j++) {
                        if (enemy_real[i][j] != "-") {
                            isOverlap = true;
                            break;
                        }
                    }
                    if (isOverlap) break;
                }
                if (isOverlap) {
                    continue;
                }

                //valid, place the ships onto the map and store the information into the global container
                for (int i = x; i < x + shipHeight; i++) {
                    for (int j = y; j < y + shipWidth; j++) {
                        enemy_real[i][j] = shipName;
                    }
                }
                enemyships[shipName] = { x, y, x + shipHeight - 1, y + shipWidth - 1, shipHP, shipHP,true };
                break;
            }
            else {//placed vertically
                int x = rand() % (map_size - shipWidth + 1);
                int y = rand() % (map_size - shipHeight + 1);
                bool isOverlap = false;
                for (int i = x; i < x + shipWidth; i++) {
                    for (int j = y; j < y + shipHeight; j++) {
                        if (enemy_real[i][j] != "-") {
                            isOverlap = true;
                            break;
                        }
                    }
                    if (isOverlap) break;
                }
                if (isOverlap) {
                    continue;
                }

                //valid, place the ships onto the map and store the information into the global container
                for (int i = x; i < x + shipWidth; i++) {
                    for (int j = y; j < y + shipHeight; j++) {
                        enemy_real[i][j] = shipName;
                    }
                }
                enemyships[shipName] = { x, y, x + shipWidth - 1, y + shipHeight - 1, shipHP, shipHP,true };
                break;
            }
        }
    }
}