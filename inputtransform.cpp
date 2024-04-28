#include <bits/stdc++.h>
#include "attack.h"
#include "support.h"
#include "inputtransform.h"
using namespace std;


void inputtransform(string** player_map_seen, string** player_map_real, string** enemy_map_seen, string** enemy_map_real) {
	string in_line; //read a line from the player
	while (1) {
		getline(cin, in_line);	//receive player input
		if (in_line == "save") {	//the player wants to save the game to a file
			string file_name;	//stores the name the user want to open;
			while (1) {
				cout << "please input the name of the file.\n"
				cin >> file_name;
				if (file_name == "cancel"||file_name=="Cancel") {
					break;	//the player doesn't want to load a game
				}
				ofstream fout;
				fout.open(file_name);
				if (fout.fail()) {
					cout << "Error in file opening!\n";
				}
				else {	//successfully opened the file
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
					for (Ship ships : playerships) {
						fout << playerships[ships].x1 << " " << playerships[ships].y1 << " ";
						fout << playerships[ships].x2 << " " << playerships[ships].y2 << " ";
						fout << playerships[ships].hp << " " << playerships[ships].status << endl;
					}
					for (Ship ships : enemyships) {
						fout << enemyships[ships].x1 << " " << enemyships[ships].y1 << " ";
						fout << enemyships[ships].x2 << " " << enemyships[ships].y2 << " ";
						fout << enemyships[ships].hp << " " << enemyships[ships].status << endl;
					}
					//for (int i = 0; i < damaged_grids.size(); i++) {
					//	cout << damaged_grids[i].x << " " << damaged_grids[i].y << endl;
					//}
					for (int i = 0; i < empty_grids.size(); i++) {
						cout << empty_grids[i].x << " " << empty_grids[i].y << endl;
					}
					for (int i = 0; i < hit_grids.size(); i++) {
						cout << hit_grids[i].x << " " << hit_grids[i].y << endl;
					}
					//need to add other output lines here;
					fout.close();
					break;
				}
			}
		}

		else if (in_line == "move") {//the player want's to move a ship
			if (elixir > 4) {//need 4 elixirs to move
				string move_ship, move_dir, move_dis;
				//ship to move, direction of the move, distance of the move
				bool move_valid;
				//indicates whether the move instruction is valid, 1 for valid, 0 for invalid
				cout << "please enter the target ship, the direction and the distance. i.e. H east 5\n";
				while (1) {
					move_valid = 1;
					cin >> move_ship;
					if (move_ship == "cancel") {
						//the user want to cancel the move
						break;
					}
					cin >> move_dir >> move_dis;
					if (move_ship != "H" && move_ship != "h" && move_ship != "K" && move_ship != "k" && move_ship != "Q" && move_ship != "q") {
						//invalid ship
						cout << "Invalid ship.\n";
						move_valid = 0;
					}
					if (move_dir != "west" && move_dir != "east" && move_dir != "north" && move_dir != "south") {
						//invalid direction
						cout << "invalid direction\.n";
						move_valid = 0;
					}
					if (move_valid == 1) {
						//movement input is correct in terms of format
						if (move_dir == "west") {
							//move to the west
							if (playerships[move_ship].x1 - move_dis <= 0) {
								//movement out of boundary
								cout << "You can't move a ship out of the map!\n";
								move_valid = 0;
							}
							bool ship_overlap = 0;
							for (int i = x1 - move_dis; i <= x2 - move_dis; i++) {
								for (int j = y1; j <= y2; j++) {
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
						}
						if (move_dir == "west") {
							//move to the west
							if (playerships[move_ship].x1 - move_dis <= 0) {
								//movement out of boundary
								cout << "You can't move a ship out of the map!\n";
								move_valid = 0;
							}
							bool ship_overlap = 0;
							for (int i = playerships[move_ship].x1 - move_dis; i <= playerships[move_ship].x2 - move_dis; i++) {
								for (int j = playerships[move_ship].y1; j <= playerships[move_ship].y2; j--) {
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
							}
						}
						else if (move_dir == "east") {
							//move to the east
							if (playerships[move_ship].x2 + move_dis > map_size) {
								//movement out of boundary
								cout << "You can't move a ship out of the map!\n";
								move_valid = 0;
							}
							bool ship_overlap = 0;
							for (int i = playerships[move_ship].x1 + move_dis; i <= playerships[move_ship].x2 + move_dis; i++) {
								for (int j = playerships[move_ship].y1; j <= playerships[move_ship].y2; j--) {
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
							}
						}
						else if (move_dir == "north") {
							//move to the north
							if (playerships[move_ship].y1 + move_dis > map_size) {
								//movement out of boundary
								cout << "You can't move a ship out of the map!\n";
								move_valid = 0;
							}
							bool ship_overlap = 0;
							for (int i = playerships[move_ship].x1; i <= playerships[move_ship].x2; i++) {
								for (int j = playerships[move_ship].y1 + move_dis; j <= playerships[move_ship].y2 + move_dis; j--) {
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
							}
						}
						else if (move_dir == "south") {
							//move to the south
							if (playerships[move_ship].y2 - move_dis <= 0) {
								//movement out of boundary
								cout << "You can't move a ship out of the map!\n";
								move_valid = 0;
							}
							bool ship_overlap = 0;
							for (int i = playerships[move_ship].x1; i <= playerships[move_ship].x2; i++) {
								for (int j = playerships[move_ship].y1 - move_dis; j <= playerships[move_ship].y2 - move_dis; j--) {
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
		else if (in_line == "shop") {	//the player wants to open the shop page

		}
		else if (in_line == "quit") {
			turn = -1;	//player quit
			break;
		}
		else if (in_line == "surrender") {
			turn = -2;	//player lose
			break;
		}
		else if (in_line == "oil drill") {
			string tmp_x, tmp_y;

		}
		else if (in_line == "attack") {
			string atk_type;	//stores attack type
			string tmp_x, tmp_y;	//attack coordinates input
			int lenx, leny;	//the length of attack coordinates input
			int atk_x, atk_y;	//stores attack coordinates
			bool atk_valid;		//indicates whether the attack instruction is valid, 1 for valid, 0 for invalid.
			while (1) {
				cout << "Please enter attack type and attack coordinates. (i.e. artillery 5 5)\n";
				atk_valid = 1;
				cin >> atk_type;
				if (atk_type == "cancel") {
					break;	//the player wants to cancel the attack
				}
				cin >> tmp_x >> tmp_y;
				lenx = tmp_x.length();
				leny = tmp_y.length();
				if (atk_type != "torpedo" && atk_type != "artillery" && atk_type != "missile" && atk_type != "nuclear") {
					//check if attack type input is valid.
					cout << "Invalid attack type.\n";
					atk_valid = 0;
				}
				for (int i = 0; i < lenx; i++) {	//check if input x-coordinate is a number
					if (tmp_x[i] < 48 || tmp_x[i]>57) {
						cout << "Invalid x-coordinate.\n";
						atk_valid = 0;
					}
				}
				for (int i = 0; i < leny; i++) {	//check if input y-coordinate is a number
					if (tmp_y[i] < 48 || tmp_y[i]>57) {
						cout << "Invalid y-coordinate.\n";
						atk_valid = 0;
					}
				}

				if (atk_valid == 1) {	//input attack type is correct and input coordinates are numbers
					atk_x = 0;
					atk_y = 0;
					for (int i = 0; i < lenx; i++) {	//transform the coordinate string to an integer	
						atk_x *= 10;
						atk_x += (tmp_x[i] - 48);
					}
					for (int i = 0; i < leny; i++) {	//transform the coordinate string to an integer
						atk_y *= 10;
						atk_y += (tmp_y[i] - 48);
					}
					for (int i = 0; i < damaged_grids.size(); i++) {	//cannot attack the same grids in 1 turn
						if (damaged_grids[i].x == atk_x && damaged_grids[i].y == atk_y) {
							cout << "You can't attack the same grid more than once in one turn!\n";
							atk_valid = 0;
							break;
						}
					}
					if (atk_type == "torpedo" && atk_valid == 1 ) {
						if (atk_x > 0 && atk_x < map_size && atk_y>0 && atk_y < map_size ) {
							if (topedo_remain > 0) {	//topedo is free but the player can only use it for limited times in a turn
								//cout<<"attack is valid\n";
								cor tmp;
								tmp = { atk_x,atk_y };
								damaged_grids.push_back(tmp);	//new damaged grids
								attack_input_conversion("enemy", ptr, ptr_seen, atk_type, atk_x, atk_y, 1);
								break;
							}
							else {
								cout << "you can only use topedo " << topedo_max << " times in a turn.\n"
							}
						}
						else {
							cout << "attack out of boundary\n";
							atk_valid = 0;
						}
					}
					else if (atk_type == "artillery" && elixer >= 2 && atk_valid == 1 ) {
						if (atk_x - 1 > 0 && atk_x + 1 < map_size && atk_y - 1 > 0 && atk_y + 1 < map_size) {
							//cout<<"attack is valid\n";
							cor tmp;
							tmp = { atk_x,atk_y };
							damaged_grids.push_back(tmp);	//new damaged grids
							attack_input_conversion("enemy", ptr, ptr_seen, atk_type, atk_x, atk_y, 1);
							break;
						}
						else {
							cout << "attack out of boundary\n";
							atk_valid = 0;
						}
					}

					else if ((atk_type == "missile" && elixir >= 5 && atk_valid == 1) || (atk_type == "nuclear"elixir >= 8 && atk_valid == 1)) {
						if (atk_x - 2 > 0 && atk_x + 2 < map_size && atk_y - 2 > 0 && atk_y + 2 < map_size) {
							//cout<<"attack is valid\n";
							cor tmp;	
							tmp = { atk_x,atk_y };
							damaged_grids.push_back(tmp);	//new damaged grids
							if (atk_type == "missile") {
								attack_input_conversion("enemy", ptr, ptr_seen, atk_type, atk_x, atk_y, 1);
								break;
							}
							else {
								attack_input_conversion("enemy", ptr, ptr_seen, atk_type, atk_x, atk_y, 2);
								break;
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
		else if (in_line == "end turn") {
			break;
		}
		else {
			cout << "Invalid input, please enter again.\n"
		}
	}
	
}
