# 1340-Group-Project

## Team members (Alphabetical Order)
Tu Xinrui 3036105387
Zhang Weizhou 3036098326
 

## Game description
Battleship is known worldwide as a pencil and paper game which dates from World War I. Players pre-deploy their ships on the grid paper and then identify the grid to attack by means of coordinates.

Our electronic version aims to restore this classic pencil-paper game for the deployment of vessels and shelling of vessels, and meanwhile offers great updates with our creative ideas, such as various attacking skills (artillery for 3x3 area attacking) and cost system. Player would fight against the computer, and the first side to destroy all 2 carriers on the opposite side wins.

### Game rule
Each player holds three types of warships: 2 carriers, 2 destroyers, and 2 tech warships. They have the different basic characteristics: carrier is 3x7, destroyer is 1x5, and tech warship is 1x4 large. Their initial HP would be maximized in 20, 5, and 4.

Deployment Phase: In the new game, the player will decide the size of the map (square of side length 15 to 20), and is asked to deploy all 6 ships in the player map. After that, enemy would randomly deploy its ships.

Attacking Phase: Player would input several commands, and the system would evaluate whether they are valid or not. Until the “end turn” command is received, enemy would start its round, to player and so on. If the attacks hit nothing, the system would reflect “O” as the fire drops to the sea, while hitting would be responded by “X” for further reference. Once the ship is fully destroyed, it will reveal all occupied grids to the opponents, and opponents gain some elixir. 

Validity: Each turn both the player and the computer have a cap on the number of torpedoes released, as presumed to be 2. Once all torpedo is released, further torpedo attacks cannot be executed, and the utilizing times would be refill to max for new rounds. Furthermore, in the single round, computer and player cannot attack the same grid twice, which encourages players to find the correct positional distribution of ships by striking the perimeter of known hit locations. Also, ships cannot be overlapped or out of the map boundaries, their validity would be tested in deployment phase and in the skill of moving ships.

### Characteristics
1. Elixir system
Ordinary Battleship would offer 2~3 torpedo attacks to players to fire, while we introduce the cost system, as elixir. As it will naturally increase with 1 point each round, and players would upgrade this increment by deploying oil wells in the local marine area. The gathered elixir would be used for various purposes, such as attacking (missile, artillery, nuclear bombs), constructions (repairing the broken ships, oil wells), and special skills (move the ships). Every action require certain elixirs, so it really tests the player's ability to operate in the long run.

2. Enemy ai
The opponent of the player is the computer, instead of another real player. The computer has the same number of ships as the player, but the damage of weapons and the cost of skills will be different. The computer would prioritize the survival of 2 carriers, otherwise would lose the game, via implementing proper moves and heals on them. Furthermore, the computer would then using free torpedo to get the location of player ships, and following artilleries for 3x3 attacks would be applied for successful elimination. Every type of attack would be considerably calculated. If the computer did not know the location of any of the player ships, it would implement random torpedo. However, through previous random attacks, if the computer get the responses of hitting the ship, it would aim to destroy this ship and consider the optimal method for both elimination efficiency and elixir cost.

## Coding Elements
### 1. Generation of random game sets or events
The enemy ships would be randomly distributed, and when the hit_grids has no elements, the computer would enforce random attacks.

### 2. Data structures for storing game status
Our game requires several global variables (stored in the support.cpp) and some pointers in the main function for execution.
map_size: determines the side length of the map, for both player and enemy from 15 t o20.
Elixir: the int array for storing the current elixir resources, [0] for player and [1] for enemy.
elixir_increament: The int array for the speed of natural increment of elixir, [0] for player and [1] for enemy.
elixir_max: Int array of maximum elixir, [0] for player and [1] for enemy.
Turn: Int for storing the current turn number.
torpedo_max: Int array for indicating the maximum releasers of torpedo, [0] for player and [1] for enemy.
torpedo_remain: The int for showing the current available times of using the torpedo.
damaged_grids: The vector to store what player has hit in one turn, for firing validity.
forbid_grids: Similar to the above one, but for computer.
empty_grids: Vector for storing all available grids for computer to attack, as the computer would never attack the grids of destroyed grids or “O” grids.
hit_grids: Vector for the computer to focus on, as the stored grids have hitting responses.
playerships and enemyships: Map containers to store all ships’s information, such as hp, coordinates, status of alive or destroyed.

### 3. Dynamic memory management
player_real, player_seen, enemy_real, enemy_seen: 4 pointers pointing to the array of string pointers, since the map size is determined by player, normal int array cannot be used (the size of the array of the string pointers is determined by user input). These pointers stores the information of ship positions, attacking traces and so on. Real for hidden and seen for shown.


### 4. File input/output (e.g., for loading/saving game status)

The program can store all the variables into the txt file upon player's request. Which can then be loaded into the game at the start of the game.

### 5. Program codes in multiple files

The main.cpp file contains the driver program and 4 pointers for ocean maps for this game. Global variables (via extern in the head files), player input for commands and enemy ai will be declared and stored in separate files.

## Compile Instructions

Run ```make game``` to compile the game.
Do ```./game``` to start the game.
