#include <iostream>
#include <cctype>	//character handling
#include <cstring>	//对于C-string，表示字符串，以 '\0'作为字符串的结束标志
#include <string>   //对string类
#include <fstream>  //对IO，ofstream写，ifstream读
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <Windows.h>
#include "attack.h"
#include "support.h"
#include "inputtransform.h"
#include "output.h"
using namespace std;

string string_execute(string s) {//uppercase to lowercase, meanwhile remove the spaces
	int s_len = s.length();
	string e_s = { "" };//executed string;
	for (int i = 0; i < s_len; i++) {
		if (s[i] == ' ') {
			continue;
		}
		else if (s[i] >= 65 && s[i] <= 90) {
			s[i] += 32;
			e_s.append(s, i, 1);
		}
		else {
			e_s.append(s, i, 1);
		}
	}
	return e_s;
}

string space_del(string s) {	//remove the spaces;
	int s_len = s.length();
	string e_s = { "" };//executed string;
	for (int i = 0; i < s_len; i++) {
		if (s[i] == ' ') {
			continue;
		}
		else {
			e_s.append(s, i, 1);
		}
	}
	return e_s;
	
}

void inputtransform(string** player_map_real, string** player_map_seen, string** enemy_map_real, string** enemy_map_seen) {
	string in_line; //read a line from the player
	int count = 0;
	battle_page_output(player_map_seen, enemy_map_seen);
	while (1) {
		cout << "Please input your order.\n";
		getline(cin, in_line);	//receive player input
		if (in_line == "") {
			cout << "Invalid order.\n";
			continue;
		}
		in_line = string_execute(in_line);
		if (in_line == "") {
			cout << "Invalid order.\n";
			continue;
		}
		if (in_line == "save") {	//the player wants to save the game to a file
			if (count > 0) {
				continue;	//player can only save at the begining of the turn;
			}
			string file_name;	//stores the name the user want to open;
			while (1) {
				cout << "please input the name of the file.\n";
					cin >> file_name;
				if (file_name == "cancel" || file_name == "Cancel") {
					break;	//the player doesn't want to load a game
				}
				ofstream fout;
				fout.open(file_name);
				if (fout.fail()) {
					cout << "Error in file opening!\n";
				}
				else {	//successfully opened the file
					count++;
					fout << map_size << endl;	//save the mapsize
					//the following four for-loops are for saving the maps
					for (int i = 1; i <= map_size; i++) {
						for (int j = 1; j <= map_size; j++) {
							fout << player_map_real[i][j] << " ";
						}
						cout << endl;
					}
					for (int i = 1; i <= map_size; i++) {
						for (int j = 1; j <= map_size; j++) {
							fout << player_map_seen[i][j] << " ";
						}
						cout << endl;
					}
					for (int i = 1; i <= map_size; i++) {
						for (int j = 1; j <= map_size; j++) {
							fout << enemy_map_real[i][j] << " ";
						}
						cout << endl;
					}
					for (int i = 1; i <= map_size; i++) {
						for (int j = 1; j <= map_size; j++) {
							fout << enemy_map_seen[i][j] << " ";
						}
						cout << endl;
					}
					fout << attack_buff[0] << " " << attack_buff[1] << endl;	//save player buff and enemy buff
					fout << elixir[0] << " " << elixir[1] << endl;	//save player elixir left and enemy elixir left
					fout << elixir_max[0] << " " << elixir_max[1] << endl;	//save player & enemy maximum elixir
					fout << turn << endl;	//save the number of turns;
					fout << torpedo_max[0] << " " << torpedo_max[1] << endl;	//save player & enemy maximum torpedo
					fout << torpedo_remain << endl;	//save player torpedo remain
					for (string i : {"H", "h", "K", "k", "Q", "q", "S", "s"}) {
						fout << playerships[i].x1 << " " << playerships[i].y1 << " ";
						fout << playerships[i].x2 << " " << playerships[i].y2 << " ";
						fout << playerships[i].hp << " " << playerships[i].status << endl;
					}
					for (string i : {"H", "h", "K", "k", "Q", "q"}) {
						fout << enemyships[i].x1 << " " << enemyships[i].y1 << " ";
						fout << enemyships[i].x2 << " " << enemyships[i].y2 << " ";
						fout << enemyships[i].hp << " " << enemyships[i].status << endl;
					}
					for (int i = 0; i < empty_grids.size(); i++) {
						cout << empty_grids[i].x << " " << empty_grids[i].y << endl;
					}
					for (int i = 0; i < hit_grids.size(); i++) {
						cout << hit_grids[i].x << " " << hit_grids[i].y << endl;
					}
					fout.close();
					break;
				}
			}
		}
		else if (in_line == "move") {//the player want's to move a ship

			if (elixir[0] >= 3) {//needs 3 elixirs to move
				string tmp_mov,move_ship,move_dir; //temporary stores move order, ship to move, direction of the move
				int move_dis, tmp_mov_len,space_count;//distance of the move, length of move order
				bool move_valid;//indicates whether the moveis valid, 1 for valid, 0 for invalid
				
				while (1) {
					cout << "please enter the target ship, the direction and the distance. i.e. H east 5\n";
					move_valid = 1;
					move_dis = 0;
					space_count = 0;
					move_ship = { "" };
					move_dir = { "" };
					getline(cin, tmp_mov);
					//special cases
					if (string_execute (tmp_mov) == "cancel") {
						//the user want to cancel the move
						break;
					}
					if (string_execute(tmp_mov) == "endturn") {
						return;
					}
					if (string_execute(tmp_mov) == "quit") {
						turn = -1;
						return;
					}
					if (string_execute(tmp_mov) == "surrender") {
						turn = -2;
						return;
					}
					tmp_mov_len = tmp_mov.length();
					for (int i = 0; i < tmp_mov_len; i++) { //input format valid check
						if (i == 0 && tmp_mov[i] == ' ') {
							while (1) {
								if (tmp_mov[i + 1] == ' ') {
									i++;
									continue;
								}
								else {
									break;
								}
							}
						}
						else if (tmp_mov[i] == ' ') {
							space_count += 1;
							while (1) {
								if (tmp_mov[i + 1] == ' ') {
									i++;
									continue;
								}
								else {
									break;
								}
							}
						}
						else if (space_count==2&&(tmp_mov[i] < 48 || tmp_mov[i] > 57)) {
							cout << "Invalid input, please enter again.\n";
							move_valid = 0;
							break;
						}
						else {
							if (space_count == 0) {
								move_ship.append(tmp_mov, i, 1);
							}
							else if (space_count == 1) {
								move_dir.append(tmp_mov, i, 1);
							}
							else if (space_count == 2) {
								move_dis*=10;
								move_dis += (tmp_mov[i]-48);
							}
							else {
								cout << "Invalid input, please enter again\n";
								move_valid = 0;
								break;
							}
						}
					}
					//format correct, then check the content
					if (space_count < 2) {
						cout << "Invalid input, please enter again\n";
						move_valid = 0;
						break;
					}
					
					if (move_valid == 1) {
						if (move_ship != "H" && move_ship != "h" && move_ship != "K" && move_ship != "k" && move_ship != "Q" && move_ship != "q") {
							//invalid ship
							cout << "Invalid ship.\n";
							move_valid = 0;
						}
						else if (playerships[move_ship].status != 1) {
							//ship that is broken;
							cout << "You can't move a damaged ship.\n";
							move_valid = 0;
						}
						if (move_dir != "west" && move_dir != "east" && move_dir != "north" && move_dir != "south") {
							//invalid direction
							cout << "invalid direction\.n";
							move_valid = 0;
						}
						if (move_valid == 0) {
							break;
						}
						//format correct, then boundary check
						
						move_dir = string_execute(move_dir);
						if (move_dir == "south") {
							//move to the west
							if (playerships[move_ship].x1 - move_dis <= 0) {
								//movement out of boundary
								cout << "You can't move a ship out of the map!\n";
								move_valid = 0;
								continue;
							}
							bool ship_overlap = 0;
							for (int i = playerships[move_ship].x1 - move_dis; i <= playerships[move_ship].x2 - move_dis; i++) {
								for (int j = playerships[move_ship].y1; j <= playerships[move_ship].y2; j++) {
									if (player_map_seen[i][j] != "-" && player_map_seen[i][j] != move_ship) {
										move_valid = 0;
										ship_overlap = 1;
										//can't move to grids that have been attacked or grids of other installations or ships
									}
								}
							}
							if (ship_overlap == 1) {
								cout << "You can't move a ship to a grid of other installations or a grid that has been attacked!\n";
							}
							else {
								skills("player", player_map_real, player_map_seen, "move", playerships[move_ship].x1, playerships[move_ship].y1, playerships[move_ship].x1 - move_dis, playerships[move_ship].y1);
								count++;
								elixir[0] -= 3;
								battle_page_output(player_map_seen, enemy_map_seen);
							}
						}
						else if (move_dir == "north") {
							//move to the east
							if (playerships[move_ship].x2 + move_dis > map_size) {
								//movement out of boundary
								cout << "You can't move a ship out of the map!\n";
								move_valid = 0;
								continue;
							}
							bool ship_overlap = 0;
							for (int i = playerships[move_ship].x1 + move_dis; i <= playerships[move_ship].x2 + move_dis; i++) {
								for (int j = playerships[move_ship].y1; j <= playerships[move_ship].y2; j++) {
									if (player_map_seen[i][j] != "-" && player_map_seen[i][j] != move_ship) {
										move_valid = 0;
										ship_overlap = 1;
										//can't move to grids that have been attacked or grids of other installations or ships
									}
								}
							}
							if (ship_overlap == 1) {
								cout << "You can't move a ship to a grid of other installations or a grid that has been attacked!\n";
							}
							else {
								skills("player", player_map_real, player_map_seen, "move", playerships[move_ship].x1, playerships[move_ship].y1, playerships[move_ship].x1 + move_dis, playerships[move_ship].y1);
								count++;
								elixir[0] -= 3;
								battle_page_output(player_map_seen, enemy_map_seen);
							}
						}
						else if (move_dir == "east") {
							//move to the north
							if (playerships[move_ship].y1 + move_dis > map_size) {
								//movement out of boundary
								cout << "You can't move a ship out of the map!\n";
								move_valid = 0;
								continue;
							}
							bool ship_overlap = 0;
							for (int i = playerships[move_ship].x1; i <= playerships[move_ship].x2; i++) {
								for (int j = playerships[move_ship].y1 + move_dis; j <= playerships[move_ship].y2 + move_dis; j++) {
									if (player_map_seen[i][j] != "-" && player_map_seen[i][j] != move_ship) {
										move_valid = 0;
										ship_overlap = 1;
										//can't move to grids that have been attacked or grids of other installations or ships
									}
								}
							}
							if (ship_overlap == 1) {
								cout << "You can't move a ship to a grid of other installations or a grid that has been attacked!\n";
							}
							else {
								//use skill function to renew the maps
								skills("player", player_map_real, player_map_seen, "move", playerships[move_ship].x1, playerships[move_ship].y1, playerships[move_ship].x1, playerships[move_ship].y1 + move_dis);
								count++;
								elixir[0] -= 3;
								battle_page_output(player_map_seen, enemy_map_seen);
							}
						}
						else if (move_dir == "west") {
							//move to the south
							if (playerships[move_ship].y2 - move_dis <= 0) {
								//movement out of boundary
								cout << "You can't move a ship out of the map!\n";
								move_valid = 0;
								continue;
							}
							bool ship_overlap = 0;
							for (int i = playerships[move_ship].x1; i <= playerships[move_ship].x2; i++) {
								for (int j = playerships[move_ship].y1 - move_dis; j <= playerships[move_ship].y2 - move_dis; j++) {
									if (player_map_seen[i][j] != "-" && player_map_seen[i][j] != move_ship) {
										move_valid = 0;
										ship_overlap = 1;
										//can't move to grids that have been attacked or grids of other installations or ships
									}
								}
							}
							if (ship_overlap == 1) {
								cout << "You can't move a ship to a grid of other installations or a grid that has been attacked!\n";
							}
							else {
								//use skill function to renew the maps
								skills("player", player_map_real, player_map_seen, "move", playerships[move_ship].x1, playerships[move_ship].y1, playerships[move_ship].x1, playerships[move_ship].y1 - move_dis);
								count++;
								elixir[0] -= 3;
								battle_page_output(player_map_seen, enemy_map_seen);
							}
						}
					}
					if (move_valid == 1) {
						//successfully moved, the loop should be broke
						break;
					}
				}
			}
			else {
				cout << "Insufficient elixir to move the ships, each move costs 3 elixirs.\n";
			}
		}
		else if (in_line == "quit") {
			turn = -1;	//player quit
			break;
		}
		else if (in_line == "surrender") {
			turn = -2;	//player lose
			break;
		}
		else if (in_line == "elixirdrill") {
			if (elixir[0] < 5) {
				cout << "insufficient elixir, you need 5 elixir to build an elixir drill.\n";
				continue;
			}
			else if (playerships["S"].status == 1 && playerships["s"].status == 1) {
				cout << "You can't have more than 2 elixir drills at the same time!\n";
				continue;
			}
			string tmp_cor;
			
			int d_x, d_y, tmp_len, space_count;
			bool drill_valid;
			cout << "Please enter the coordinates of drill (y,x).\n";
			while (1) {
				getline(cin, tmp_cor);
				drill_valid = 1;
				space_count = 0;
				d_x = 0;
				d_y = 0;
				tmp_len = tmp_cor.length();
				//special cases
				if (string_execute(tmp_cor) == "cancel") {
					break;
				}
				else if (string_execute(tmp_cor) == "endturn") {
					return;
				}
				else if (string_execute(tmp_cor) == "quit") {
					turn = -1;
					return;
				}
				else if (string_execute(tmp_cor) == "surrender") {
					turn = -2;
					return;
				}
				//input format check
				for (int i = 0; i < tmp_len;i++) {
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
						space_count += 1;
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
					else if (tmp_cor[i] < 48 || tmp_cor[i] > 57) {
						cout << "Invalid input, please enter again.\n";
						drill_valid = 0;
						break;
					}
					else {
						if (space_count == 0) {
							d_x *= 10;
							d_x += (tmp_cor[i] - 48);
						}
						else if (space_count == 1) {
							d_y *= 10;
							d_y += (tmp_cor[i] - 48);
						}
						else {
							cout << "Invalid input, please enter again.\n";
							drill_valid = 0;
							break;
						}
					}
				}
				if (drill_valid == 0) {
					continue;
				}
				if (space_count < 1) {
					cout << "Invalid input, please enter again.\n";
					continue;
				}
				//format correct, then boundary check
				if (d_y > map_size || d_y < 1 || d_x > map_size || d_x < 1) {
					cout << "Coordinates out of boundary, please input again.\n";
					continue;
				}
				else if (player_map_seen[d_x][d_y] != "-") {
					cout << "You can only build the elixir drill at an empty grid that has not been damaged.\n";
					continue;
				}
				else {
					if (playerships["S"].status == 0) {
						playerships["S"] = {d_x,d_y,d_x,d_y,1,1,1};
						player_map_real[d_x][d_y] = "S";
						player_map_seen[d_x][d_y] = "S";
						elixir_max[0] += 1;
						elixir_increament[0] += 1;
						elixir[0] -= 3;
						count++;
						battle_page_output(player_map_seen,enemy_map_seen);
					}
					else {
						playerships["s"] = { d_x,d_y,d_x,d_y,1,1,1 };
						player_map_real[d_x][d_y] = "s";
						player_map_seen[d_x][d_y] = "s";
						elixir_max[0] += 1;
						elixir_increament[0] += 1;
						elixir[0] -= 5;
						count++;
						battle_page_output(player_map_seen, enemy_map_seen);
					}
					break;
				}
			}	
		}
		else if (in_line == "attack") {
			string tmp_order;	//temporary stores the input
			string atk_type;	//stores attack type
			int order_len,space_count;	//the length of attack coordinates input and space execution
			int atk_x, atk_y;	//stores attack coordinates
			bool atk_valid;		//indicates whether the attack instruction is valid, 1 for valid, 0 for invalid.
			
			while (1) {
				cout << "Please enter attack type and attack coordinates. (i.e. artillery 5 5)\n";
				atk_valid = 1;
				space_count = 0;
				atk_type = { "" };
				atk_x = 0;
				atk_y = 0;
				getline(cin, tmp_order);
				if (string_execute(tmp_order)=="cancel") {
					break;	//the player wants to cancel the attack				
				}
				else if (string_execute(tmp_order) == "endturn") {
					return;
				}
				else if (string_execute(tmp_order) == "quit") {
					turn = -1;
					return;
				}
				else if (string_execute(tmp_order) == "surrender") {
					turn = -2;
					return;
				}
				order_len = tmp_order.length();

				for (int i = 0; i < order_len; i++) { //input valid check
					if (i == 0 && tmp_order[i] == ' ') { //ignore spaces at the beginning
						while (1) {
							if (tmp_order[i + 1] == ' ') {
								i++;
								continue;
							}
							else {
								break;
							}
						}
					}
					else if (tmp_order[i] == ' ') {//count spaces, ignore continuous spaces
						space_count += 1;
						while (1) {
							if (tmp_order[i + 1] == ' ') {
								i++;
								continue;
							}
							else {
								break;
							}
						}
					}
					else if (space_count >= 1 && (tmp_order[i] < 48 || tmp_order[i] > 57)) {
						cout << "Invalid input, please enter again\n";
						atk_valid = 0;
						break;
					}
					else {
						if (space_count == 0) {
							atk_type.append(tmp_order, i, 1);
						}
						else if (space_count == 1) {
							atk_x *= 10;
							atk_x += (tmp_order[i] - 48);
						}
						else if (space_count == 2) {
							atk_y *= 10;
							atk_y += (tmp_order[i] - 48);
						}
						else {
							cout << "Invalid input, please enter again\n";
							atk_valid = 0;
							break;
						}
					}
				}
				if (space_count < 2) {
					cout << "Invalid input, please enter again\n";
					atk_valid = 0;
					break;
				}
				if (atk_valid == 1) {	
					atk_type = string_execute(atk_type);
					//input correct in terms of format
					if (atk_type != "torpedo" && atk_type != "artillery" && atk_type != "missile" && atk_type != "nuclear") {
						//check if attack type input is valid.
						cout << "Invalid attack type.\n";
						atk_valid = 0;
					}
					for (int i = 0; i < damaged_grids.size(); i++) {	//cannot attack the same grids in 1 turn
						if (atk_type == "torpedo") {
							if (damaged_grids[i].x == atk_x && damaged_grids[i].y == atk_y) {
								cout << "You can't attack the same grid more than once in one turn!\n";
								atk_valid = 0;
								break;
							}
						}
						else if (atk_type == "artillery") {
							if (damaged_grids[i].x <= atk_x+1 && damaged_grids[i].x >= atk_x -1 && damaged_grids[i].y <= atk_y+1&& damaged_grids[i].y >= atk_y - 1) {
								cout << "You can't attack the same grid more than once in one turn!\n";
								atk_valid = 0;
								break;
							}
						}
						else {
							if (damaged_grids[i].x <= atk_x + 2 && damaged_grids[i].x >= atk_x - 2 && damaged_grids[i].y <= atk_y + 2 && damaged_grids[i].y >= atk_y - 2) {
								cout << "You can't attack the same grid more than once in one turn!\n";
								atk_valid = 0;
								break;
							}
						}
					}
					if (atk_type == "torpedo" && atk_valid == 1) {
						if (atk_x > 0 && atk_x <= map_size && atk_y>0 && atk_y <= map_size) {
							if (torpedo_remain > 0) {	//topedo is free but the player can only use it for limited times in a turn
								Cor tmp;
								tmp = { atk_x,atk_y };
								damaged_grids.push_back(tmp);	//new damaged grids
								attack_input_conversion("enemy", enemy_map_real, enemy_map_seen, atk_type, atk_x, atk_y, 1);
								count++;
								torpedo_remain--;
								battle_page_output(player_map_seen, enemy_map_seen);
								continue;
							}
							else {
								cout << "you can only use topedo " << torpedo_max[0] << " times in a turn.\n";
							}
						}
						else {
							cout << "attack out of boundary\n";
							atk_valid = 0;
						}
					}
					else if (atk_type == "artillery" && atk_valid == 1) {
						if (elixir[0] < 3) {
							cout << "You need 3 elixir to use the artillery!\n";
							continue;
						}
						if (atk_x - 1 > 0 && atk_x + 1 <= map_size && atk_y - 1 > 0 && atk_y + 1 <= map_size) {
							//cout<<"attack is valid\n";
							Cor tmp;
							for (int dmg_x = atk_x - 1; dmg_x <= atk_x + 1; dmg_x++) {
								for (int dmg_y = atk_y - 1; dmg_y <= atk_y + 1; dmg_y++) {
									tmp = { dmg_x,dmg_y }; //load the damaged grids into the container
									damaged_grids.push_back(tmp);
								}
							}
							attack_input_conversion("enemy", enemy_map_real, enemy_map_seen, atk_type, atk_x, atk_y, 1);
							count++;
							elixir[0] -= 3;
							battle_page_output(player_map_seen, enemy_map_seen);
							continue;
						}
						else {
							cout << "attack out of boundary\n";
							atk_valid = 0;
						}
					}

					else if ((atk_type == "missile"  && atk_valid == 1) || (atk_type == "nuclear"  && atk_valid == 1)) {
						if(atk_type=="missile"&& elixir[0] < 5) {
							cout << "You need 5 elixir to use the missile!\n";
							continue;
						}
						if (atk_type == "nuclear" && elixir[0] < 8) {
							cout << "You need 8 elixir to use the missile!\n";
							continue;
						}
						if (atk_x - 2 > 0 && atk_x + 2 <= map_size && atk_y - 2 > 0 && atk_y + 2 <= map_size) {
							Cor tmp;
							for (int dmg_x = atk_x - 2; dmg_x <= atk_x + 2; dmg_x++) {
								for (int dmg_y = atk_y - 2; dmg_y <= atk_y + 2; dmg_y++) {
									tmp = { dmg_x,dmg_y }; //load the damaged grids into the container
									damaged_grids.push_back(tmp);
								}
							}
							if (atk_type == "missile") {
								attack_input_conversion("enemy", enemy_map_real, enemy_map_seen, atk_type, atk_x, atk_y, 1);
								count++;
								elixir[0] -= 5;
								battle_page_output(player_map_seen, enemy_map_seen);
								continue;
							}
							else {
								attack_input_conversion("enemy", enemy_map_real, enemy_map_seen, atk_type, atk_x, atk_y, 2);
								count++;
								elixir[0] -= 8;
								battle_page_output(player_map_seen, enemy_map_seen);
								continue;
							}
						}
						else {
							cout << "attack out of boundary\n";
							atk_valid = 0;
						}
					}
				}
			}
		}
		else if (in_line == "endturn") {
			return;
		}
		else if (in_line == "show") {
			battle_page_output(player_map_real, enemy_map_seen);
			system("pause");
			battle_page_output(player_map_seen, enemy_map_seen);
		}
		else if (in_line == "heal") {
			if (elixir[0] < 2) {
				cout << "Insufficient elixir, it takes 2 elixir to heal";
				continue;
			}
			string h_ship;	//ship top be healed;
			while (1) {
				cout << "please input the ship you want to heal (e.g. H).\n";
				getline(cin, h_ship);
				h_ship = space_del(h_ship);
				//special cases
				if (string_execute(h_ship) == "cancel") {
					break;
				}
				if (string_execute(h_ship) == "endturn") {
					return;
				}
				if (string_execute(h_ship) == "quit") {
					turn = -1;
					return;
				}
				if (string_execute(h_ship) == "surrender") {
					turn = -2;
					return;
				}
				//check if the ship is valid
				if (h_ship != "H" && h_ship != "h" && h_ship != "Q" && h_ship != "q" && h_ship != "K" && h_ship != "k") {
					cout << "Invalid ship.\n";
					continue;
				}
				if (playerships[h_ship].status != 1) {
					cout << "You can't heal a ship that is already destroyed.\n";
					continue;
				}
				if (playerships[h_ship].hp == playerships[h_ship].hp_max) {
					cout << "You can't heal a ship that has 100% hp.\n";
					continue;
				}
				
				elixir[0] -= 2;
				playerships[h_ship].hp += 3;
				if (playerships[h_ship].hp > playerships[h_ship].hp_max) {//hp exceeds limit
					playerships[h_ship].hp = playerships[h_ship].hp_max;
				}
				count++;
				battle_page_output(player_map_seen, enemy_map_seen);
				break;
				
			}	
		}
		else {
			cout << "Invalid input, please enter again.\n";
		}
	}

}