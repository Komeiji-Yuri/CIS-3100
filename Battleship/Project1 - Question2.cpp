#include <iostream>
#include <cstdlib> //for random
#include <ctime> //for random
#include <string> // for string
#include <algorithm> //for transform function
#include <cctype> //for upper lower case
using namespace std;

//function prototype
void PrintInstruction();
void PrintFleet(string[][11], string[][11]);
void GenerateRandomGrid(string[][11]);
void PlayerInputGrid(string[][11]);

//a global variable used for letter checking, which can be accessed through both main and functions
string letter_array[10] = { "A","B","C","D","E","F","G","H","I","J" };

int main()
{

    //variables of user input
    string user_input, user_input_row, user_input_col;
    //variables of cpu input
    int cpu_input_row, cpu_input_col;
    //int format is needed, since we need to use them to enter the coordinate
    int user_input_row_int, user_input_col_int;
    bool exist_in_array = false;
    //in-game variable
    bool player_hit = false;
    bool cpu_hit = false;
    int player_hit_amount = 0;
    int cpu_hit_amount = 0;
    //statistical data
    int game_round = 1;
    int remain_enemy_fleet = 30;
    //other variables
    bool win = false;
    bool exit_game = false;
    bool view_instruction = false;
    char game_menu = '0';
    char game_menu_2 = '0';

    //game menu loop, will only end if player choose exit
    while (true) {

        //initialize some variables to prepare for next round of game
        win = false;
        exit_game = false;
        view_instruction = false;
        game_round = 1;
        remain_enemy_fleet = 30;

        //print the game menu
        cout << "\n\n";
        cout << "**************************************************" << endl;
        cout << "                    BATTLESHIP                    " << endl;
        cout << "**************************************************" << endl;
        cout << "                                                  " << endl;
        cout << "                                                  " << endl;
        cout << "Enter [0] to start the Game:                      " << endl;
        cout << "Enter [1] to view Instruction:                    " << endl;
        cout << "Enter [2] to exit the Game:                       " << endl;

        //include the switch statement inside a while loop so that when user enter invalid input, program won't jump back to the beginning to print the menu again
        while (true) {
            //prompting player to enter the number
            cin >> game_menu;
            //switch statment to handling different situations: start the game, exit the game, invalid input
            switch (game_menu) {
            case '0':
                cout << "Establishing Battlefield Control..." << endl << endl;
                break;
            case '1':
                view_instruction = true;
                PrintInstruction();
                break;
            case '2':
                cout << "Game Exit." << endl;
                exit_game = true;
                break;
            default:
                cout << "Invalid Command, please try again." << endl;
                continue;
            }
            break;
        }

        //return to the beginning of the loop and display the game menu again if player choose to view instruction
        if (view_instruction == true)
            continue;

        //terminate the game menu loop if player choose to exit the game
        if (exit_game == true)
            break;

        //before launching the game, initialize the random function
        srand(time(0));

        //generate the boards for both player and cpu
        //create the cpu's board in player's view (which has nothing on the board, visible for player. This is the board where player make their operations)
        string cpu_board_visible[11][11] = {
            {"  ", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"},
            {" 1", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 2", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 3", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 4", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 5", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 6", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 7", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 8", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 9", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {"10", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
        };

        //create the cpu's actual board (which contains all cpu's ships on the board, not visible for player)
        string cpu_board_invisible[11][11] = {
            {"  ", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"},
            {" 1", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 2", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 3", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 4", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 5", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 6", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 7", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 8", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 9", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {"10", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
        };

        //starting to put the random generated ship locations onto the board
        GenerateRandomGrid(cpu_board_invisible);

        //create the player's board
        string player_board[11][11] = {
            {"  ", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"},
            {" 1", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 2", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 3", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 4", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 5", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 6", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 7", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 8", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {" 9", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
            {"10", "~", "~", "~", "~", "~", "~", "~", "~", "~", "~"},
        };

        //ask player if they want to place ships by themselves or let the program place ships randomly for them
        cout << "Would you like to place your own ships? If not, your ship positions will be random." << endl;
        cout << "[0] - no" << endl;
        cout << "[1] - yes" << endl;

        while (true) {
            //prompting player to enter the number
            cin >> game_menu_2;
            //switch statment to check user's input, if user want to choose their own ships or let the program do it for them
            switch (game_menu_2) {
            case '0':
                //put the random generated ship locations onto the board
                GenerateRandomGrid(player_board);
                cout << "\n" << endl;
                break;
            case '1':
                //let the player determine ship locations themselves
                PlayerInputGrid(player_board);
                cout << "\n" << endl;
                break;
            default:
                cout << "Invalid Command, please try again." << endl;
                continue;
            }
            break;
        }

        //Game Start
        cout << "Game Start! Good Luck!!" << endl << endl;
        //loop will end if a winner is determined
        while (win == false) {
            //player's turn
            while (true) {
                //statistical message
                cout << "Number of Steps Taken: " << game_round << "\t Enemy Grids Remaining: " << remain_enemy_fleet << endl << endl;

                //the battlefield will be printed once whenever it's player's turn
                PrintFleet(cpu_board_visible, player_board);

                //display the player hit message if enemy ship was hit last round
                if (game_round > 1 && player_hit == true)
                    cout << "DIRECT HIT!!! *" << player_hit_amount;
                else
                    cout << "             ";

                //display the cpu hit message if enemy ship was hit last round
                if (game_round > 1 && cpu_hit == true)
                    cout << "\t\t\tDIRECT HIT!!! *" << cpu_hit_amount << endl;
                else
                    cout << "\t\t\t             " << endl;

                //initialize hit boolean variables
                player_hit = false;
                cpu_hit = false;
                //initialize cpu times of hit variable
                cpu_hit_amount = 0;

                cout << endl;

                //checking if winner is player
                //suppose player win at the beginning
                win = true;

                for (int i = 1; i < 11; i++)
                {
                    for (int j = 1; j < 11; j++)
                    {
                        //if a single live ship is detected in enemy fleet, we confirm player isn't the winner
                        if (cpu_board_invisible[i][j] == "O") {
                            win = false;
                        }
                    }
                }

                //as player is confirmed to be the winner, display the victory message and terminate the loop
                if (win == true) {
                    cout << endl;
                    cout << endl;
                    cout << "**** \\ YOU ARE VICTORIOUS!!! // ****" << endl;
                    cout << endl;
                    cout << endl;
                    break;
                }

                //player's input
                while (true) {
                    //display the tutorial message if it's first round
                    if (game_round == 1)
                        cout << "Please enter the coordinate you wish to bombard. (HINT - enter Column & Row. ex: A1, B5, H10)" << endl;
                    else
                        cout << "Please enter the coordinate you wish to bombard." << endl;
                    //prompting user to input the coordinate
                    cin >> user_input;
                    //breaking down the user input into two seperate values
                    user_input_col = user_input[0];
                    user_input_row = user_input.substr(1, 2);

                    //start checking if the user input is a legal value

                    //STEP 1: check the length of input; if greater than 3, the input is invalid
                    if (user_input.size() > 3) {
                        cout << "Invalid input, please try again." << endl << endl;
                        continue;
                    }

                    //STEP 2: checking the row number; it can only be integers between 1 and 10
                    //first, checking if the first digit of the input value is a number
                    if (isdigit(user_input_row[0])) {
                        //further check if the input has two digit
                        if (user_input_row.size() == 2) {
                            //checking if the second digit is a number
                            if (isdigit(user_input_row[1])) {
                                //does nothing
                            }
                            //if the value is not a number
                            else {
                                cout << "Invalid input, please try again." << endl << endl;
                                continue;
                            }
                        }
                        //does nothing
                    }
                    //if the value is not a number
                    else {
                        cout << "Invalid input, please try again." << endl << endl;
                        continue;
                    }
                    //if the input value is a number, convert string to integer
                    user_input_row_int = stoi(user_input_row);
                    //checking if the integer is valid
                    if (user_input_row_int >= 1 && user_input_row_int <= 10) {
                        //does nothing
                    }
                    //this will happen when integer value is invalid
                    else {
                        cout << "Invalid input, please try again." << endl << endl;
                        continue;
                    }

                    //STEP 3: checking the column letter; it can only be Uppercase or Lowercase letters from A to J
                    //if user enter lowercase, transform it into uppercase
                    transform(user_input_col.begin(), user_input_col.end(), user_input_col.begin(), ::toupper);
                    //check if the value exist in the letter array
                    for (int i = 0; i < 10; i++) {
                        if (user_input_col == letter_array[i]) {
                            //once the existance of the letter has been confirmed, find what position is the letter located in array
                            user_input_col_int = i + 1;
                            exist_in_array = true;
                        }
                    }
                    //if the value doesn't exist in the array, the input is invalid
                    if (exist_in_array == false) {
                        cout << "Invalid input, please try again." << endl << endl;
                        continue;
                    }
                    //initialize the value of exist_in_array after finish testing
                    exist_in_array = false;

                    //STEP 4: checking if the coordinate that player wish to bombard has already been bombarded before
                    if (cpu_board_invisible[user_input_row_int][user_input_col_int] == "#" ||
                        cpu_board_invisible[user_input_row_int][user_input_col_int] == "X") {
                        cout << "You are unable to bombard the same location twice! Please try again." << endl << endl;
                        continue;
                    }
                    break;
                }

                //start doing the actual bombardment once the user input was proven to be valid

                //checking the current bombardment is a hit or miss
                //hit
                if (cpu_board_invisible[user_input_row_int][user_input_col_int] == "O") {
                    cpu_board_invisible[user_input_row_int][user_input_col_int] = "X";
                    cpu_board_visible[user_input_row_int][user_input_col_int] = "X";
                    //number of enemy remaining ship - 1
                    remain_enemy_fleet -= 1;
                    player_hit = true;
                    //player times of hit + 1
                    player_hit_amount += 1;
                    //game round + 1
                    game_round++;
                    //if hit, player get another chance to hit
                    continue;
                }
                //miss
                else if (cpu_board_invisible[user_input_row_int][user_input_col_int] == "~") {
                    cpu_board_invisible[user_input_row_int][user_input_col_int] = "#";
                    cpu_board_visible[user_input_row_int][user_input_col_int] = "#";
                    //initialize player times of hit variable
                    player_hit_amount = 0;
                    //game round + 1
                    game_round++;
                    //if miss, loop will terminate and now it's cpu's turn
                    break;
                }
            }

            //if winner has been determined in player's turn, break the loop
            if (win == true) {
                break;
            }

            //cpu's turn
            while (true) {
                //checking if winner is cpu
                //suppose cpu win at the beginning
                win = true;

                for (int i = 1; i < 11; i++)
                {
                    for (int j = 1; j < 11; j++)
                    {
                        //if a single live ship is detected in enemy fleet, we confirm cpu isn't the winner
                        if (player_board[i][j] == "O") {
                            win = false;
                        }
                    }
                }

                //as cpu is confirmed to be the winner, display the lose message and terminate the loop
                if (win == true) {
                    cout << endl;
                    cout << endl;
                    cout << "--- YOU HAVE LOST ---" << endl;
                    cout << endl;
                    cout << endl;
                    break;
                }

                //cpu's input
                while (true) {
                    //cpu will randomly choose a bombardment location first
                    cpu_input_row = rand() % 10 + 1; // set value to random between 1 and 10
                    cpu_input_col = rand() % 10 + 1; // set value to random between 1 and 10

                    //checking if the coordinate that cpu wish to bombard has already been bombarded before
                    if (player_board[cpu_input_row][cpu_input_col] == "#" ||
                        player_board[cpu_input_row][cpu_input_col] == "X") {
                        //if the current location has been bombarded before, cpu will reselect the bombardment location
                        continue;
                    }
                    break;
                }

                //checking the current bombardment is a hit or miss
                //hit
                if (player_board[cpu_input_row][cpu_input_col] == "O") {
                    player_board[cpu_input_row][cpu_input_col] = "X";
                    cpu_hit = true;
                    //cpu times of hit + 1
                    cpu_hit_amount += 1;
                    //game round + 1
                    game_round++;
                    //if hit, player get another chance to hit
                    continue;
                }
                //miss
                else if (player_board[cpu_input_row][cpu_input_col] == "~") {
                    player_board[cpu_input_row][cpu_input_col] = "#";
                    //game round + 1
                    game_round++;
                    //if miss, loop will terminate and now it's player's turn
                    break;
                }
            }
        }
    }
    return 0;
}

//function defination

//the function used to display game instruction
void PrintInstruction()
{
    cout << "\n\t\t\t\tGame Instruction" << endl << endl;
    cout << "1. Player and Cpu will take turn guessing enemy grids that contains their ship." << endl;
    cout << "2. As players hit an enemy ship, they can keep hitting until they miss." << endl;
    cout << "3. Once all ships are sunk on enemy board, the player is victorious!" << endl;
    cout << "\n\n";
    cout << "Symbol Meaning:" << endl;
    cout << "~: empty grid" << endl;
    cout << "O: ship" << endl;
    cout << "#: miss" << endl;
    cout << "X: hit" << endl;
    cout << "\n\n";
    cout << "Ship Types:" << endl;
    cout << "O O O O O     Carrier - Occupys 5 grids, maximum at one in a round of game" << endl;
    cout << "O O O O     Battleship - Occupys 4 grids, maximum at two in a round of game" << endl;
    cout << "O O O     Cruiser & Submarine - Occupys 3 grids, maximum at three in a round of game" << endl;
    cout << "O O     Destroyer & Patrol Boat - Occupys 2 grids, maximum at four in a round of game" << endl;
    return;
}

//the function used to display both player and cpu's fleet
void PrintFleet(string arra[][11], string arrb[][11])
{
    cout << " Enemy Fleet \t\t  ||     Your Fleet" << endl;
    cout << "             \t\t  ||               " << endl;
    for (int i = 0; i < 11; i++)
    {
        //print the line from the first array
        for (int j = 0; j < 11; j++)
        {
            cout << arra[i][j] << " ";
        }

        //add some space between two array
        cout << "\t  ||\t";

        //print the line from the second array
        for (int j = 0; j < 11; j++)
        {
            cout << arrb[i][j] << " ";
        }

        //jump to the next line
        cout << endl;
    }
    return;
}

//the function used to generate random locations for ships
void GenerateRandomGrid(string field[][11])
{
    //declare variables of random values
    int row_random, col_random, direction;

    //declare variables of ship number
    int ship_number = 0;

    //loop won't end until the number of ship exist on the board reaches 10
    while (ship_number < 10) {

        //set the random position for ships
        row_random = rand() % 10 + 1; // set value to random between 1 and 10
        col_random = rand() % 10 + 1; // set value to random between 1 and 10
        direction = rand() % 2; // set value to random between 0 and 1

        //CARRIER (quantity: 1, grids: 5)
        //a carrier will always be generated at the very beginning
        if (ship_number == 0) {
            // "0" represents horizontal direction
            if (direction == 0) {
                //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop to find another random grid.
                if (field[row_random][col_random] == "~" &&
                    field[row_random + 1][col_random] == "~" &&
                    field[row_random + 2][col_random] == "~" &&
                    field[row_random + 3][col_random] == "~" &&
                    field[row_random + 4][col_random] == "~") {
                    //"O" represents a grid that contains enemy ships
                    field[row_random][col_random] = "O";
                    field[row_random + 1][col_random] = "O";
                    field[row_random + 2][col_random] = "O";
                    field[row_random + 3][col_random] = "O";
                    field[row_random + 4][col_random] = "O";
                    //variable of ship number + 1
                    ship_number++;
                }
                else {
                    //restart the loop
                    continue;
                }
            }
            // if not horizontal, it would be vertical
            else {
                //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop to find another random grid.
                if (field[row_random][col_random] == "~" &&
                    field[row_random][col_random + 1] == "~" &&
                    field[row_random][col_random + 2] == "~" &&
                    field[row_random][col_random + 3] == "~" &&
                    field[row_random][col_random + 4] == "~") {
                    //"O" represents a grid that contains enemy ships
                    field[row_random][col_random] = "O";
                    field[row_random][col_random + 1] = "O";
                    field[row_random][col_random + 2] = "O";
                    field[row_random][col_random + 3] = "O";
                    field[row_random][col_random + 4] = "O";
                    //variable of ship number + 1
                    ship_number++;
                }
                else {
                    //restart the loop
                    continue;
                }
            }
        }

        //BATTLESHIP (quantity: 2, grids: 4)
        //if the number of ship is within this range, code will decide to generate battleship
        else if (ship_number >= 1 && ship_number < 3) {
            // "0" represents horizontal direction
            if (direction == 0) {
                //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop to find another random grid.
                if (field[row_random][col_random] == "~" &&
                    field[row_random + 1][col_random] == "~" &&
                    field[row_random + 2][col_random] == "~" &&
                    field[row_random + 3][col_random] == "~") {
                    //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop to find another random grid.
                    if (field[row_random - 1][col_random] == "O" ||
                        field[row_random][col_random - 1] == "O" ||
                        field[row_random][col_random + 1] == "O" ||
                        field[row_random + 1][col_random - 1] == "O" ||
                        field[row_random + 1][col_random + 1] == "O" ||
                        field[row_random + 2][col_random - 1] == "O" ||
                        field[row_random + 2][col_random + 1] == "O" ||
                        field[row_random + 3][col_random - 1] == "O" ||
                        field[row_random + 3][col_random + 1] == "O" ||
                        field[row_random + 4][col_random] == "O") {
                        continue;
                    }
                    //"O" represents a grid that contains enemy ships
                    field[row_random][col_random] = "O";
                    field[row_random + 1][col_random] = "O";
                    field[row_random + 2][col_random] = "O";
                    field[row_random + 3][col_random] = "O";
                    //variable of ship number + 1
                    ship_number++;
                }
                else {
                    //restart the loop
                    continue;
                }
            }
            // if not horizontal, it would be vertical
            else {
                //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop to find another random grid.
                if (field[row_random][col_random] == "~" &&
                    field[row_random][col_random + 1] == "~" &&
                    field[row_random][col_random + 2] == "~" &&
                    field[row_random][col_random + 3] == "~") {
                    //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop to find another random grid.
                    if (field[row_random][col_random - 1] == "O" ||
                        field[row_random - 1][col_random] == "O" ||
                        field[row_random + 1][col_random] == "O" ||
                        field[row_random - 1][col_random + 1] == "O" ||
                        field[row_random + 1][col_random + 1] == "O" ||
                        field[row_random - 1][col_random + 2] == "O" ||
                        field[row_random + 1][col_random + 2] == "O" ||
                        field[row_random - 1][col_random + 3] == "O" ||
                        field[row_random + 1][col_random + 3] == "O" ||
                        field[row_random][col_random + 4] == "O") {
                        continue;
                    }
                    //"O" represents a grid that contains enemy ships
                    field[row_random][col_random] = "O";
                    field[row_random][col_random + 1] = "O";
                    field[row_random][col_random + 2] = "O";
                    field[row_random][col_random + 3] = "O";
                    //variable of ship number + 1
                    ship_number++;
                }
                else {
                    //restart the loop
                    continue;
                }
            }
        }

        //CRUISER & SUBMARINE (quantity: 3, grids: 3)
        //if the number of ship is within this range, code will decide to generate cruiser or submarine
        else if (ship_number >= 3 && ship_number < 6) {
            // "0" represents horizontal direction
            if (direction == 0) {
                //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop to find another random grid.
                if (field[row_random][col_random] == "~" &&
                    field[row_random + 1][col_random] == "~" &&
                    field[row_random + 2][col_random] == "~") {
                    //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop to find another random grid.
                    if (field[row_random - 1][col_random] == "O" ||
                        field[row_random][col_random - 1] == "O" ||
                        field[row_random][col_random + 1] == "O" ||
                        field[row_random + 1][col_random - 1] == "O" ||
                        field[row_random + 1][col_random + 1] == "O" ||
                        field[row_random + 2][col_random - 1] == "O" ||
                        field[row_random + 2][col_random + 1] == "O" ||
                        field[row_random + 3][col_random] == "O") {
                        continue;
                    }
                    //"O" represents a grid that contains enemy ships
                    field[row_random][col_random] = "O";
                    field[row_random + 1][col_random] = "O";
                    field[row_random + 2][col_random] = "O";
                    //variable of ship number + 1
                    ship_number++;
                }
                else {
                    //restart the loop
                    continue;
                }
            }
            // if not horizontal, it would be vertical
            else {
                //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop to find another random grid.
                if (field[row_random][col_random] == "~" &&
                    field[row_random][col_random + 1] == "~" &&
                    field[row_random][col_random + 2] == "~") {
                    //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop to find another random grid.
                    if (field[row_random][col_random - 1] == "O" ||
                        field[row_random - 1][col_random] == "O" ||
                        field[row_random + 1][col_random] == "O" ||
                        field[row_random - 1][col_random + 1] == "O" ||
                        field[row_random + 1][col_random + 1] == "O" ||
                        field[row_random - 1][col_random + 2] == "O" ||
                        field[row_random + 1][col_random + 2] == "O" ||
                        field[row_random][col_random + 3] == "O") {
                        continue;
                    }
                    //"O" represents a grid that contains enemy ships
                    field[row_random][col_random] = "O";
                    field[row_random][col_random + 1] = "O";
                    field[row_random][col_random + 2] = "O";
                    //variable of ship number + 1
                    ship_number++;
                }
                else {
                    //restart the loop
                    continue;
                }
            }
        }

        //DESTROYER & PATROL BOAT (quantity: 4, grids: 2)
        //if the number of ship is within this range, code will decide to generate destroyer or patrol boat
        else if (ship_number >= 6 && ship_number < 10) {
            // "0" represents horizontal direction
            if (direction == 0) {
                //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop to find another random grid.
                if (field[row_random][col_random] == "~" &&
                    field[row_random + 1][col_random] == "~") {
                    //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop to find another random grid.
                    if (field[row_random - 1][col_random] == "O" ||
                        field[row_random][col_random - 1] == "O" ||
                        field[row_random][col_random + 1] == "O" ||
                        field[row_random + 1][col_random - 1] == "O" ||
                        field[row_random + 1][col_random + 1] == "O" ||
                        field[row_random + 2][col_random] == "O") {
                        continue;
                    }
                    //"O" represents a grid that contains enemy ships
                    field[row_random][col_random] = "O";
                    field[row_random + 1][col_random] = "O";
                    //variable of ship number + 1
                    ship_number++;
                }
                else {
                    //restart the loop
                    continue;
                }
            }
            // if not horizontal, it would be vertical
            else {
                //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop to find another random grid.
                if (field[row_random][col_random] == "~" &&
                    field[row_random][col_random + 1] == "~") {
                    //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop to find another random grid.
                    if (field[row_random][col_random - 1] == "O" ||
                        field[row_random - 1][col_random] == "O" ||
                        field[row_random + 1][col_random] == "O" ||
                        field[row_random - 1][col_random + 1] == "O" ||
                        field[row_random + 1][col_random + 1] == "O" ||
                        field[row_random][col_random + 2] == "O") {
                        continue;
                    }
                    //"O" represents a grid that contains enemy ships
                    field[row_random][col_random] = "O";
                    field[row_random][col_random + 1] = "O";
                    //variable of ship number + 1
                    ship_number++;
                }
                else {
                    //restart the loop
                    continue;
                }
            }
        }
    }
    return;
}

//the function used to let player place their own ships
void PlayerInputGrid(string field[][11])
{
    //declare variables of user inputs
    char ship_type;
    char direction;
    string coordinate, coordinate_col, coordinate_row;
    int coordinate_col_int, coordinate_row_int;
    //declare variables of the number of different ships
    int carrier = 0;
    int battleship = 0;
    int cruiser = 0;
    int destroyer = 0;
    //declare other variables
    string current_ship_type;
    bool exist_in_array = false;

    //loop won't end until the number of each type of ship exist on the board reaches the specified target
    while (carrier < 1 || battleship < 2 || cruiser < 3 || destroyer < 4) {

        //User Inputs
        //input 1: ship type
        cout << "\n" << endl;
        cout << "Which type of ship would you like to place? (1: Carrier, 2: Battleship, 3: Cruiser & Submarine, 4: Destroyer & Patrol Boat)" << endl;
        while (true) {
            //reset this varaible everytime before player's input to prevent error
            ship_type = '0';
            //player's input
            cin >> ship_type;
            switch (ship_type) {
                //as long as player input is a valid input or the number of current ship type haven't reach maximum, the loop will break and input process continue; otherwise jump back to beginning.
            case '1':
                if (carrier >= 1) {
                    cout << "Error - the number of carrier on map has already reach maximum! Please reenter a different ship type:" << endl;
                    continue;
                }
                current_ship_type = "Carrier";
                carrier++;
                break;
            case '2':
                if (battleship >= 2) {
                    cout << "Error - the number of battleship on map has already reach maximum! Please reenter a different ship type:" << endl;
                    continue;
                }
                current_ship_type = "Battleship";
                battleship++;
                break;
            case '3':
                if (cruiser >= 3) {
                    cout << "Error - the number of cruiser and submarine on map has already reach maximum! Please reenter a different ship type:" << endl;
                    continue;
                }
                current_ship_type = "Cruiser";
                cruiser++;
                break;
            case '4':
                if (destroyer >= 4) {
                    cout << "Error - the number of destroyer and patrol boat on map has already reach maximum! Please reenter a different ship type:" << endl;
                    continue;
                }
                current_ship_type = "Destroyer";
                destroyer++;
                break;
            default:
                cout << "Error - Invalid input, please try again." << endl;
                continue;
            }
            break;
        }

        //input 2: ship direction
        cout << "\n" << endl;
        cout << "Which direction would you like to place your ship? (0: horizontal, 1: vertical)" << endl;
        while (true) {
            //reset this varaible everytime before player's input to prevent error
            direction = '2';
            //player's input
            cin >> direction;
            switch (direction) {
                //as long as player input is a valid input, the loop will break and input process continue; otherwise jump back to beginning.
            case '0':
                break;
            case '1':
                break;
            default:
                cout << "Error - Invalid input, please try again." << endl;
                continue;
            }
            break;
        }

        //input 3: ship coordinate
        //print the player's board
        cout << "\n" << endl;
        for (int i = 0; i < 11; i++)
        {
            //print the line from the first array
            for (int j = 0; j < 11; j++)
            {
                cout << field[i][j] << " ";
            }
            cout << endl;
        }
        cout << "\n" << endl;

        //if dectect that this is the first time player start to place the ship, display the toturial message
        if (carrier == 0 || battleship == 0 || cruiser == 0 || destroyer == 0) {
            cout << "Your current ship type is: " << current_ship_type << endl;
            cout << "Please enter the coordinate you wish to place your ship. (HINT - enter Column & Row.ex: A1, B5, H10)" << endl;
        }
        else {
            cout << "Your current ship type is: " << current_ship_type << endl;
            cout << "Please enter the coordinate you wish to place your ship." << endl;
        }

        while (true) {
            //reset this varaible everytime before player's input to prevent error
            coordinate = "0";
            //player's input
            cin >> coordinate;
            //breaking down the user input into two seperate values
            coordinate_col = coordinate[0];
            coordinate_row = coordinate.substr(1, 2);

            //start checking if the user input is a legal value

            //STEP 1: check the length of input; if greater than 3, the input is invalid
            if (coordinate.size() > 3) {
                cout << "Invalid input, please try again." << endl << endl;
                continue;
            }

            //STEP 2: checking the row number; it can only be integers between 1 and 10
            //first, checking if the first digit of the input value is a number
            if (isdigit(coordinate_row[0])) {
                //further check if the input has two digit
                if (coordinate_row.size() == 2) {
                    //checking if the second digit is a number
                    if (isdigit(coordinate_row[1])) {
                        //does nothing
                    }
                    //if the value is not a number
                    else {
                        cout << "Invalid input, please try again." << endl << endl;
                        continue;
                    }
                }
                //does nothing
            }
            //if the value is not a number
            else {
                cout << "Invalid input, please try again." << endl << endl;
                continue;
            }
            //if the input value is a number, convert string to integer
            coordinate_row_int = stoi(coordinate_row);
            //checking if the integer is valid
            if (coordinate_row_int >= 1 && coordinate_row_int <= 10) {
                //does nothing
            }
            //this will happen when integer value is invalid
            else {
                cout << "Invalid input, please try again." << endl << endl;
                continue;
            }

            //STEP 3: checking the column letter; it can only be Uppercase or Lowercase letters from A to J
            //if user enter lowercase, transform it into uppercase
            transform(coordinate_col.begin(), coordinate_col.end(), coordinate_col.begin(), ::toupper);
            //check if the value exist in the letter array
            for (int i = 0; i < 10; i++) {
                if (coordinate_col == letter_array[i]) {
                    //once the existance of the letter has been confirmed, find what position is the letter located in array
                    coordinate_col_int = i + 1;
                    exist_in_array = true;
                }
            }
            //if the value doesn't exist in the array, the input is invalid
            if (exist_in_array == false) {
                cout << "Invalid input, please try again." << endl << endl;
                continue;
            }
            //initialize the value of exist_in_array after finish testing
            exist_in_array = false;

            //STEP 4: checking if the coordinate that player wish to place ship has already been occupied by other ship
            if (field[coordinate_row_int][coordinate_col_int] == "O") {
                cout << "You are unable to place ship at a location that already have a ship! Please try again." << endl << endl;
                continue;
            }

            //STEP 5: checking if the coordinate where player choose to place the ship will cause collision with other ships (which means making sure there's 1 grid distance between ships); if not, generate the ship at player chosen location
            switch (ship_type) {
            case '1':
                // "1" represents vertical direction
                if (direction == '1') {
                    //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop.
                    if (field[coordinate_row_int][coordinate_col_int] == "~" &&
                        field[coordinate_row_int + 1][coordinate_col_int] == "~" &&
                        field[coordinate_row_int + 2][coordinate_col_int] == "~" &&
                        field[coordinate_row_int + 3][coordinate_col_int] == "~" &&
                        field[coordinate_row_int + 4][coordinate_col_int] == "~") {
                        //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop.
                        if (field[coordinate_row_int - 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 2][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int + 2][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 3][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int + 3][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 4][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int + 4][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 5][coordinate_col_int] == "O") {
                            cout << "You can not place at this location because the ship generated here will be too close from another ship! Please try again." << endl;
                            continue;
                        }
                        //"O" represents a grid that contains enemy ships
                        field[coordinate_row_int][coordinate_col_int] = "O";
                        field[coordinate_row_int + 1][coordinate_col_int] = "O";
                        field[coordinate_row_int + 2][coordinate_col_int] = "O";
                        field[coordinate_row_int + 3][coordinate_col_int] = "O";
                        field[coordinate_row_int + 4][coordinate_col_int] = "O";
                    }
                    else {
                        cout << "You can not place at this location because the ship generated here will overlap with other ship or touch the border! Please try again." << endl;
                        continue;
                    }
                }
                // "0" represents horizontal direction
                else if (direction == '0') {
                    //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop.
                    if (field[coordinate_row_int][coordinate_col_int] == "~" &&
                        field[coordinate_row_int][coordinate_col_int + 1] == "~" &&
                        field[coordinate_row_int][coordinate_col_int + 2] == "~" &&
                        field[coordinate_row_int][coordinate_col_int + 3] == "~" &&
                        field[coordinate_row_int][coordinate_col_int + 4] == "~") {
                        //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop.
                        if (field[coordinate_row_int][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int + 2] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 2] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int + 3] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 3] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int + 4] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 4] == "O" ||
                            field[coordinate_row_int][coordinate_col_int + 5] == "O") {
                            cout << "You can not place at this location because the ship generated here will be too close from another ship! Please try again." << endl;
                            continue;
                        }
                        //"O" represents a grid that contains enemy ships
                        field[coordinate_row_int][coordinate_col_int] = "O";
                        field[coordinate_row_int][coordinate_col_int + 1] = "O";
                        field[coordinate_row_int][coordinate_col_int + 2] = "O";
                        field[coordinate_row_int][coordinate_col_int + 3] = "O";
                        field[coordinate_row_int][coordinate_col_int + 4] = "O";
                    }
                    else {
                        cout << "You can not place at this location because the ship generated here will overlap with other ship or touch the border! Please try again." << endl;
                        continue;
                    }
                }
                else {
                    cout << "Error - please try again." << endl;
                    continue;
                }
                break;
            case '2':
                // "1" represents vertical direction
                if (direction == '1') {
                    //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop.
                    if (field[coordinate_row_int][coordinate_col_int] == "~" &&
                        field[coordinate_row_int + 1][coordinate_col_int] == "~" &&
                        field[coordinate_row_int + 2][coordinate_col_int] == "~" &&
                        field[coordinate_row_int + 3][coordinate_col_int] == "~") {
                        //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop.
                        if (field[coordinate_row_int - 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 2][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int + 2][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 3][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int + 3][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 4][coordinate_col_int] == "O") {
                            cout << "You can not place at this location because the ship generated here will be too close from another ship! Please try again." << endl;
                            continue;
                        }
                        //"O" represents a grid that contains enemy ships
                        field[coordinate_row_int][coordinate_col_int] = "O";
                        field[coordinate_row_int + 1][coordinate_col_int] = "O";
                        field[coordinate_row_int + 2][coordinate_col_int] = "O";
                        field[coordinate_row_int + 3][coordinate_col_int] = "O";
                    }
                    else {
                        cout << "You can not place at this location because the ship generated here will overlap with other ship or touch the border! Please try again." << endl;
                        continue;
                    }
                }
                // "0" represents horizontal direction
                else if (direction == '0') {
                    //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop.
                    if (field[coordinate_row_int][coordinate_col_int] == "~" &&
                        field[coordinate_row_int][coordinate_col_int + 1] == "~" &&
                        field[coordinate_row_int][coordinate_col_int + 2] == "~" &&
                        field[coordinate_row_int][coordinate_col_int + 3] == "~") {
                        //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop.
                        if (field[coordinate_row_int][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int + 2] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 2] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int + 3] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 3] == "O" ||
                            field[coordinate_row_int][coordinate_col_int + 4] == "O") {
                            cout << "You can not place at this location because the ship generated here will be too close from another ship! Please try again." << endl;
                            continue;
                        }
                        //"O" represents a grid that contains enemy ships
                        field[coordinate_row_int][coordinate_col_int] = "O";
                        field[coordinate_row_int][coordinate_col_int + 1] = "O";
                        field[coordinate_row_int][coordinate_col_int + 2] = "O";
                        field[coordinate_row_int][coordinate_col_int + 3] = "O";
                    }
                    else {
                        cout << "You can not place at this location because the ship generated here will overlap with other ship or touch the border! Please try again." << endl;
                        continue;
                    }
                }
                else {
                    cout << "Error - please try again." << endl;
                    continue;
                }
                break;
            case '3':
                // "1" represents vertical direction
                if (direction == '1') {
                    //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop.
                    if (field[coordinate_row_int][coordinate_col_int] == "~" &&
                        field[coordinate_row_int + 1][coordinate_col_int] == "~" &&
                        field[coordinate_row_int + 2][coordinate_col_int] == "~") {
                        //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop.
                        if (field[coordinate_row_int - 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 2][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int + 2][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 3][coordinate_col_int] == "O") {
                            cout << "You can not place at this location because the ship generated here will be too close from another ship! Please try again." << endl;
                            continue;
                        }
                        //"O" represents a grid that contains enemy ships
                        field[coordinate_row_int][coordinate_col_int] = "O";
                        field[coordinate_row_int + 1][coordinate_col_int] = "O";
                        field[coordinate_row_int + 2][coordinate_col_int] = "O";
                    }
                    else {
                        cout << "You can not place at this location because the ship generated here will overlap with other ship or touch the border! Please try again." << endl;
                        continue;
                    }
                }
                // "0" represents horizontal direction
                else if (direction == '0') {
                    //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop.
                    if (field[coordinate_row_int][coordinate_col_int] == "~" &&
                        field[coordinate_row_int][coordinate_col_int + 1] == "~" &&
                        field[coordinate_row_int][coordinate_col_int + 2] == "~") {
                        //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop.
                        if (field[coordinate_row_int][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int + 2] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 2] == "O" ||
                            field[coordinate_row_int][coordinate_col_int + 3] == "O") {
                            cout << "You can not place at this location because the ship generated here will be too close from another ship! Please try again." << endl;
                            continue;
                        }
                        //"O" represents a grid that contains enemy ships
                        field[coordinate_row_int][coordinate_col_int] = "O";
                        field[coordinate_row_int][coordinate_col_int + 1] = "O";
                        field[coordinate_row_int][coordinate_col_int + 2] = "O";
                    }
                    else {
                        cout << "You can not place at this location because the ship generated here will overlap with other ship or touch the border! Please try again." << endl;
                        continue;
                    }
                }
                else {
                    cout << "Error - please try again." << endl;
                    continue;
                }
                break;
            case '4':
                // "1" represents vertical direction
                if (direction == '1') {
                    //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop.
                    if (field[coordinate_row_int][coordinate_col_int] == "~" &&
                        field[coordinate_row_int + 1][coordinate_col_int] == "~") {
                        //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop.
                        if (field[coordinate_row_int - 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 2][coordinate_col_int] == "O") {
                            cout << "You can not place at this location because the ship generated here will be too close from another ship! Please try again." << endl;
                            continue;
                        }
                        //"O" represents a grid that contains enemy ships
                        field[coordinate_row_int][coordinate_col_int] = "O";
                        field[coordinate_row_int + 1][coordinate_col_int] = "O";
                    }
                    else {
                        cout << "You can not place at this location because the ship generated here will overlap with other ship or touch the border! Please try again." << endl;
                        continue;
                    }
                }
                // "0" represents horizontal direction
                else if (direction == '0') {
                    //checking if this random grids and its next a few adjacent grids are valid; if not, restart the loop.
                    if (field[coordinate_row_int][coordinate_col_int] == "~" &&
                        field[coordinate_row_int][coordinate_col_int + 1] == "~") {
                        //checking if the chosen position has neighboring grids that has already been occupied; if so, restart the loop.
                        if (field[coordinate_row_int][coordinate_col_int - 1] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int] == "O" ||
                            field[coordinate_row_int - 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int + 1][coordinate_col_int + 1] == "O" ||
                            field[coordinate_row_int][coordinate_col_int + 2] == "O") {
                            cout << "You can not place at this location because the ship generated here will be too close from another ship! Please try again." << endl;
                            continue;
                        }
                        //"O" represents a grid that contains enemy ships
                        field[coordinate_row_int][coordinate_col_int] = "O";
                        field[coordinate_row_int][coordinate_col_int + 1] = "O";
                    }
                    else {
                        cout << "You can not place at this location because the ship generated here will overlap with other ship or touch the border! Please try again." << endl;
                        continue;
                    }
                }
                else {
                    cout << "Error - please try again." << endl;
                    continue;
                }
                break;
            default:
                // logically, this will never happen, but let's keep it here just in case
                cout << "Error - please try again." << endl;
                continue;
            }
            break;
        }

        //print the player's board again once the ship placement is successful
        cout << "Placement successful." << endl << endl;
        for (int i = 0; i < 11; i++)
        {
            //print the line from the first array
            for (int j = 0; j < 11; j++)
            {
                cout << field[i][j] << " ";
            }
            cout << endl;
        }

        //loop will jump back to the beginning
    }
    return;
}