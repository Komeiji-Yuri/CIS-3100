#include <iostream>
using namespace std;

//function prototype
void print2Darray(char[][3], int, int);

int main()
{
    //declare the variable of game round
    int rounds = 1;
    //declare the user input variable as char so that it will prevent error if user enter a letter
    char user_input_row, user_input_col;
    //int format is also needed as calculating the coordinate
    int user_input_row_int, user_input_col_int;
    //delcare the variable of winning condition, default is false
    bool win = false;
    bool exit_game = false;
    char game_menu = '0';

        //game menu loop, will only end if player choose exit
        while (true) {

            //create an array of integers with numbers from 1 to 5
            char grid[3][3] = {
                {'-', '-', '-'},
                {'-', '-', '-'},
                {'-', '-', '-'}
            };

            //initialize some variables to prepare for next round of game
            rounds = 1;
            win = false;
            exit_game = false;

            //print the game menu
            cout << "\n\n";
            cout << "**************************************************" << endl;
            cout << "                   TIC TAC TOE                    " << endl;
            cout << "**************************************************" << endl;
            cout << "                                                  " << endl;
            cout << "                                                  " << endl;
            cout << "Enter [0] to start the Game:                      " << endl;
            cout << "Enter [1] to exit the Game:                       " << endl;

            //prompting player to enter the number
            cin >> game_menu;
            //switch statment to handling different situations: start the game, exit the game, invalid input
            switch (game_menu) {
            case '0':
                cout << "Game Start! Good Luck!" << endl;
                break;
            case '1':
                cout << "Game Exit." << endl;
                exit_game = true;
                break;
            default:
                cout << "Invalid Command, please try again." << endl;
                continue;
            }

            //terminate the game menu loop if player choose to exit the game
            if (exit_game == true)
                break;

            //loop will only be terminated by break statemnet inside the loop.
            while (true) {
                //player X's turn, this is a loop inside a signle round. The loop will automatically be terminated by the break statement in the end.
                while (true) {
                    //print two lines of space and current array first
                    cout << "\n\n";
                    print2Darray(grid, 3, 3);
                    cout << "Player X: Enter the row & col numbers for your move: " << endl;
                    cout << "Row: ";
                    cin >> user_input_row;
                    cout << "Column: ";
                    cin >> user_input_col;

                    //char minus '0' will convert itself into int format. This step is used for calculating the coordinate
                    user_input_row_int = user_input_row - '0';
                    user_input_col_int = user_input_col - '0';

                    //only 1, 2 and 3 are legal input values, any other input will receive an error
                    if ((user_input_row == '1' || user_input_row == '2' || user_input_row == '3') &&
                        (user_input_col == '1' || user_input_col == '2' || user_input_col == '3')) {
                        //Frist, turn the actual row & column number into index value, so the coordinate will be calculated correctly
                        //Then detect if the cell has already been taken. If not, allow the player to take this cell.
                        if (grid[user_input_row_int - 1][user_input_col_int - 1] == '-')
                            grid[user_input_row_int - 1][user_input_col_int - 1] = 'x';
                        else {
                            cout << "You can't occupy the cell that has already been taken! - Please try again. \n" << endl;
                            //Return to the beginning of the loop and let user try again if error occur
                            continue;
                        }
                    }
                    else {
                        cout << "Invalid input - Please try again. \n" << endl;
                        //Return to the beginning of the loop and let user try again if error occur
                        continue;
                    }
                    break;
                }
                //check the winning condition
                if ((grid[0][0] == 'x' && grid[0][1] == 'x' && grid[0][2] == 'x') ||
                    (grid[1][0] == 'x' && grid[1][1] == 'x' && grid[1][2] == 'x') ||
                    (grid[2][0] == 'x' && grid[2][1] == 'x' && grid[2][2] == 'x') || //hroizontal 3 cells
                    (grid[0][0] == 'x' && grid[1][0] == 'x' && grid[2][0] == 'x') ||
                    (grid[0][1] == 'x' && grid[1][1] == 'x' && grid[2][1] == 'x') ||
                    (grid[0][2] == 'x' && grid[1][2] == 'x' && grid[2][2] == 'x') || //vertical 3 cells
                    (grid[0][0] == 'x' && grid[1][1] == 'x' && grid[2][2] == 'x') ||
                    (grid[0][2] == 'x' && grid[1][1] == 'x' && grid[2][0] == 'x'))   //diagonal 3 cells
                {
                    //once here's a winner, the array will be printed again to show the final result
                    cout << "\n";
                    print2Darray(grid, 3, 3);
                    cout << "\n";
                    cout << "**************************************************" << endl;
                    cout << "**  CONGRATULATION! Player X has won the game!  **" << endl;
                    cout << "**************************************************" << endl;

                    //set the winning condition variable as true, indicates that a winner has been decided
                    win = true;
                    //terminate the entire loop
                    break;
                }

                //if winner cannot be decided yet, game round count + 1
                rounds++;

                //if the max possible game round has been reached, that means a draw, which will end the game
                if (rounds > 9)
                    break;

                //player O's turn, this is a loop inside a signle round. The loop will automatically be terminated by the break statement in the end.
                while (true) {
                    //print two lines of space and current array first
                    cout << "\n\n";
                    print2Darray(grid, 3, 3);
                    cout << "Player O: Enter the row & col numbers for your move: " << endl;
                    cout << "Row: ";
                    cin >> user_input_row;
                    cout << "Column: ";
                    cin >> user_input_col;

                    //char minus '0' will convert itself into int format. This step is used for calculating the coordinate
                    user_input_row_int = user_input_row - '0';
                    user_input_col_int = user_input_col - '0';

                    //only 1, 2 and 3 are legal input values, any other input will receive an error
                    if ((user_input_row == '1' || user_input_row == '2' || user_input_row == '3') &&
                        (user_input_col == '1' || user_input_col == '2' || user_input_col == '3')) {
                        //Frist, turn the actual row & column number into index value, so the coordinate will be calculated correctly
                        //Then detect if the cell has already been taken. If not, allow the player to take this cell.
                        if (grid[user_input_row_int - 1][user_input_col_int - 1] == '-')
                            grid[user_input_row_int - 1][user_input_col_int - 1] = 'o';
                        else {
                            cout << "You can't occupy the cell that has already been taken! - Please try again. \n" << endl;
                            //Return to the beginning of the loop and let user try again if error occur
                            continue;
                        }
                    }
                    else {
                        cout << "Invalid input - Please try again. \n" << endl;
                        //Return to the beginning of the loop and let user try again if error occur
                        continue;
                    }
                    break;
                }
                //check the winning condition
                if ((grid[0][0] == 'o' && grid[0][1] == 'o' && grid[0][2] == 'o') ||
                    (grid[1][0] == 'o' && grid[1][1] == 'o' && grid[1][2] == 'o') ||
                    (grid[2][0] == 'o' && grid[2][1] == 'o' && grid[2][2] == 'o') || //hroizontal 3 cells
                    (grid[0][0] == 'o' && grid[1][0] == 'o' && grid[2][0] == 'o') ||
                    (grid[0][1] == 'o' && grid[1][1] == 'o' && grid[2][1] == 'o') ||
                    (grid[0][2] == 'o' && grid[1][2] == 'o' && grid[2][2] == 'o') || //vertical 3 cells
                    (grid[0][0] == 'o' && grid[1][1] == 'o' && grid[2][2] == 'o') ||
                    (grid[0][2] == 'o' && grid[1][1] == 'o' && grid[2][0] == 'o'))   //diagonal 3 cells
                {
                    //once here's a winner, the array will be printed again to show the final result
                    cout << "\n";
                    print2Darray(grid, 3, 3);
                    cout << "\n";
                    cout << "**************************************************" << endl;
                    cout << "**  CONGRATULATION! Player O has won the game!  **" << endl;
                    cout << "**************************************************" << endl;

                    //set the winning condition variable as true, indicates that a winner has been decided
                    win = true;
                    //terminate the entire loop
                    break;
                }

                //if winner cannot be decided yet, game round count + 1
                rounds++;
            }

            //variable win will only equals to false if winner cannot be decided in last round of game, which means a draw
            if (win == false) {
                //print the draw message
                cout << "\n";
                print2Darray(grid, 3, 3);
                cout << "That's a Draw! Try harder next time!" << endl;
            }

        }
    return 0;  
}

//function defination
void print2Darray(char arr[][3], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return;
}