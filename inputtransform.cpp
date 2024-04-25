#include <bits/stdc++.h>

using namespace std;
int main(string **ptr){
	string in_line; //read a line from the player
	while(1){
		
		getline(cin,in_line);
		
		if(turn==0){//game has not started
			if(in_line=="load"){ //the player wants to load another saving
				
			}
			else if(in_line=="new game"){//the player wants to start a new game from a file
				cout<<"please input an integer \"n\" which 10<=n<=15, where n is the legth of the size of the map\n";
				while(cin>>map_size){
					if(map_size<10||map_size>15){
						cout<<"Invalid size, please enter again.\n";
						continue;
					}
					mapsize+=1;
					break;
				}
				break;
			}
		}
		
		else{
			if(in_line=="save"){	//the player wants to save the game to a file
				
			}
			
			else if(in_line=="move"){
				if(elixir>3){
					string move_ship, move_dir, move_dis; //ship to move, direction of the, distance of the move
					bool move_valid; //indicates whether the move instruction is valid, 1 for valid, 0 for invalid
					cout<<"please enter the target ship, the direction and the distance. i.e. H east 5\n";
					while(1){
						move_valid=1;
						cin>>move_ship>>move_dir>>move_dis;
						if(move_ship!="H"&&move_ship!="h"&&move_ship!="K"&&move_ship!="k"&&move_ship!="Q"&&move_ship!="q"){
							//invalid ship
							cout<<"Invalid ship.\n";
							move_valid=0;
						}
						if(move_dir!="west"&&move_dir!="east"&&move_dir!="north"&&move_dir!="south"){
							//invalid direction
							cout<<"invalid direction\.n";
							move_valid=0;
						}
						if(move_valid==1){
							playerships.
						}
					}
					
				}
				else{
					cout<<"Insufficient elixir to move the ships, each move costs 3 elixirs.\n";
				}
			}
			
			else if(in_line=="load"){	//the player wants to load another saving
				
			}
			else if(in_line=="new game"){	//the player wants to start a new game from a file
				
			}
			else if(in_line=="shop"){	//the player wants to open the shop page
				
			}
			else if(in_line=="surrender"){
				
			}
			else if(in_line=="attack"){	
				string atk_type;	//stores attack type
				string tmp_x, tmp_y;	//attack coordinates input
				int lenx,leny;	//the length of attack coordinates input
				int atk_x,atk_y;	//stores attack coordinates
				bool atk_valid;		//indicates whether the attack instruction is valid, 1 for valid, 0 for invalid.
				while(1){
					cout<<"Please enter attack type and attack coordinates. (i.e. artillery 5 5)\n";
					atk_valid=1;
					cin>>atk_type>>tmp_x>>tmp_y;
					lenx=tmp_x.length();
					leny=tmp_y.length();
					
					if(atk_type!="torpedo"&&atk_type!="artillery"&&atk_type!="missile"&&atk_type!="nuclear"){
						//check if attack type input is valid.
						cout<<"Invalid attack type.\n";
						atk_valid=0;
					}
					for(int i=0;i<lenx;i++){	//check if input x-coordinate is a number
						if(tmp_x[i]<48||tmp_x[i]>57){
							cout<<"Invalid x-coordinate.\n";
							atk_valid=0;
							break;
						}
					}
					for(int i=0;i<leny;i++){	//check if input y-coordinate is a number
						if(tmp_y[i]<48||tmp_y[i]>57){
							cout<<"Invalid y-coordinate.\n";
							atk_valid=0;
							break;
						}
					}
					
					if(atk_valid==1){	//input attack type is correct and input coordinates are numbers
						atk_x=0;
						atk_y=0;
						for(int i=0;i<lenx;i++){	//transform the coordinate string to an integer	
							atk_x*=10;
							atk_x+=(tmp_x[i]-48);
						}
						for(int i=0;i<leny;i++){	//transform the coordinate string to an integer
							atk_y*=10;
							atk_y+=(tmp_y[i]-48);
						}
						if(atk_type=="torpedo") {
							if(atk_x>0&&atk_x<map_size&&atk_y>0&&atk_y<map_size){
								if(topedo_remain>0){	//topedo is free but the player can only use it for limited times in a turn
									//cout<<"attack is valid\n";
									attack_input_conversion("enemy",ptr,ptr_seen,atk_type, atk_x, atk_y, 1);
								}
								else{
									cout<<"you can only use topedo "<<topedo_max<<" times in a turn.\n"
								}
							}
							else{
								cout<<"attack out of boundary\n";
								atk_valid=0;
							}
						}		
						else if(atk_type=="artillery"&&elixer>=2) {
							if(atk_x-1>0&&atk_x+1<map_size&&atk_y-1>0&&atk_y+1<map_size){
								//cout<<"attack is valid\n";
								attack_input_conversion("enemy",ptr,ptr_seen,atk_type, atk_x, atk_y, 1);	
							}
							else{
								cout<<"attack out of boundary\n";
								atk_valid=0;
							}
						}
							
						else if((atk_type=="missile"&&elixir>=5)||(atk_type=="nuclear"elixir>=8)) {
							if(atk_x-2>0&&atk_x+2<map_size&&atk_y-2>0&&atk_y+2<map_size){
								//cout<<"attack is valid\n";	
								if(atk_type=="missile"){
									attack_input_conversion("enemy",ptr,ptr_seen,atk_type, atk_x, atk_y, 1);
								}
								else{
									attack_input_conversion("enemy",ptr,ptr_seen,atk_type, atk_x, atk_y, 2);
								}
							}
							else{
								cout<<"attack out of boundary\n";
								atk_valid=0;
							}
						}
					}
				}
				
			}
			else if (in_line=="end turn"){
				break;
			}
		}
		cout<<"Invalid input, please enter again.\n"	
	}
}