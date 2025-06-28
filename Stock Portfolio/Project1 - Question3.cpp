#include <iostream>
#include <cstdlib> //for random
#include <ctime> //for random
#include <iomanip> //for decimal places
#include <sstream> //for float to string and keep decimal places
#include <string>
#include <algorithm> //for sort
#include <vector> //for auto adjusting array size
using namespace std;

//function prototype
void AddNewStock();
void DeleteStock();
void ViewPortfolio();
void TotalValue();
string GenerateRandomValue();

//a global variable used for letter checking, which can be accessed through both main and functions
char letter_array[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','V','X','Y','Z' };

//a global variable used for number checking, which can be accessed through both main and functions
char number_array[11] = { '1','2','3','4','5','6','7','8','9','0','.' };

//create a vector for the global variable matrix
vector<vector<string>> purchased_stock;

int main()
{
    //first, add a few default stocks inside the matrix
    purchased_stock = {
    {"AACG", "3", "20.2", "22.31"},
    {"CBRL", "5", "10.5", "12.2"},
    {"PNM", "1", "5.61", "4.1"}
    };

    //declaring variables
    char user_input;
    bool exit = false;

    while (exit == false) {
        // Print the Stock Portfolio Menu
        cout << "\n\n";
        cout << "**************************************************" << endl;
        cout << "                  Stock Portfolio                 " << endl;
        cout << "**************************************************" << endl;
        cout << "                                                  " << endl;
        cout << "                                                  " << endl;
        cout << "Enter [0] to add new stock:                       " << endl;
        cout << "Enter [1] to delete existing stock:               " << endl;
        cout << "Enter [2] to view the portfolio:                  " << endl;
        cout << "Enter [3] to view the total stock value:          " << endl;
        cout << "Enter [4] to exit:                                " << endl;
        cout << "\n\n";

        //initialize random
        srand(time(0));

        //include the switch statement inside a while loop so that when user enter invalid input, program won't jump back to the beginning to print the menu again
        while (true) {
            //prompting user to enter a number
            cin >> user_input;
            switch (user_input) {
            case '0':
                AddNewStock();
                break;
            case '1':
                DeleteStock();
                break;
            case '2':
                ViewPortfolio();
                break;
            case '3':
                TotalValue();
                break;
            case '4':
                cout << "Exit the progam." << endl;
                exit = true;
                break;
            default:
                cout << "Invalid input, please try again." << endl;
                continue;
            }
            break;
        }
    }

    return 0;
}

//function defination
void AddNewStock()
{
    //declare variables
    string symbol;
    string number_of_shares;
    string purchase_price;
    string current_value;
    bool exist_in_array = false;
    bool error_occur = false;
    //create a vector for an array that going to be added into the matrix
    vector <string> appending_array;

    //let user input stock symbol
    while (true) {
        //reset the error variable
        error_occur = false;
        cout << "Please enter the symbol of the stock you would like to buy." << endl;
        cin >> symbol;
        //check if the input exceed 4 character limit.
        if (symbol.size() > 4) {
            cout << "The maximum input is 4 character! Please try again." << endl;
            continue;
        }
        //check if input contains only uppercase letter.
        for (int i = 0; i < symbol.size(); i++) {
            exist_in_array = false;
            for (int j = 0; j < 26; j++) {
                if (symbol[i] == letter_array[j]) {
                    exist_in_array = true;
                }
            }
            if (exist_in_array == true) {
                //if detect that previous character exist in the letter array, that means the current part of the input is legal and program does nothing
            }
            else {
                //otherwise, display the error message and restart the loop
                cout << "You can only input uppercase letters! Please try again." << endl;
                error_occur = true;
            }
        }
        //check if the input symbol already exist
        for (int i = 0; i < purchased_stock.size(); i++) {
            if (purchased_stock[i][0] == symbol) {
                cout << "This stock already exists in your portfolio! Please try again." << endl;
                error_occur = true;
            }
        }
        //if error occurs in previous codes, loop will restart and user will enter input again
        if (error_occur == true)
            continue;
        break;
    }

    //let user input number of shares
    while (true) {
        //reset the error variable
        error_occur = false;
        cout << "Please enter the number of shares you would like to buy." << endl;
        cin >> number_of_shares;
        //check if input contains only number.
        for (int i = 0; i < number_of_shares.size(); i++) {
            //reset the boolean value
            exist_in_array = false;
            for (int j = 0; j < 11; j++) {
                if (number_of_shares[i] == number_array[j]) {
                    exist_in_array = true;
                }
            }
            if (exist_in_array == true) {
                //if detect that previous character exist in the number array, that means the current part of the input is legal and program does nothing
            }
            else {
                //otherwise, display the error message and restart the loop
                cout << "You can only input numbers! Please try again." << endl;
                error_occur = true;
                break;
            }
        }
        //if error occurs in previous codes, loop will restart and user will enter input again
        if (error_occur == true)
            continue;
        break;
    }

    //let user input purchase price
    while (true) {
        //reset the error variable
        error_occur = false;
        cout << "What is the purchase price of the stock?" << endl;
        cin >> purchase_price;
        //check if input contains only number.
        for (int i = 0; i < purchase_price.size(); i++) {
            //reset the boolean value
            exist_in_array = false;
            for (int j = 0; j < 11; j++) {
                if (purchase_price[i] == number_array[j]) {
                    exist_in_array = true;
                }
            }
            if (exist_in_array == true) {
                //if detect that previous character exist in the number array, that means the current part of the input is legal and program does nothing
            }
            else {
                //otherwise, display the error message and restart the loop
                cout << "You can only input numbers! Please try again." << endl;
                error_occur = true;
                break;
            }
        }
        //if error occurs in previous codes, loop will restart and user will enter input again
        if (error_occur == true)
            continue;
        break;
    }

    //Generate a random current value
    current_value = GenerateRandomValue();

    //include all previous values inside a new array and append them to the purchased_stock
    appending_array = { symbol, number_of_shares , purchase_price, current_value };
    purchased_stock.push_back(appending_array);
    //display the success message
    cout << "Stock successfully added!" << endl;

    return;
}

void DeleteStock()
{
    //declare variables
    string symbol;
    bool exist_in_array = false;
    bool error_occur = false;

    //let user input stock symbol
    while (true) {
        //reset the error variable
        error_occur = false;
        cout << "Please enter the symbol of the stock you would like to delete." << endl;
        cin >> symbol;
        //check if the input exceed 4 character limit.
        if (symbol.size() > 4) {
            cout << "The maximum input is 4 character! Please try again." << endl;
            continue;
        }
        //check if input contains only uppercase letter.
        for (int i = 0; i < symbol.size(); i++) {
            //reset the boolean value
            exist_in_array = false;
            for (int j = 0; j < 26; j++) {
                if (symbol[i] == letter_array[j]) {
                    exist_in_array = true;
                }
            }
            if (exist_in_array == true) {
                //if detect that previous character exist in the letter array, that means the current part of the input is legal and program does nothing
            }
            else {
                //otherwise, display the error message and restart the loop
                cout << "You can only input uppercase letters! Please try again." << endl;
                error_occur = true;
                break;
            }
        }

        //find the symbol to delete the stock; if unable to find it, restart the loop
        for (int i = 0; i < purchased_stock.size(); i++) {
            if (purchased_stock[i][0] == symbol) {
                //delete the row i of the matrix, which is the one user hope to delete
                purchased_stock.erase(purchased_stock.begin() + i);
                break;
            }
            if ( i == purchased_stock.size() - 1) {
                //when reaches the last row of the matrix, display the error message
                cout << "No such stock in your portfolio! Please try again." << endl;
                error_occur = true;
            }
        }
        //if error occurs in previous codes, loop will restart and user will enter input again
        if (error_occur == true)
            continue;
        break;
    }

    //display the success message
    cout << "Stock successfully deleted!" << endl;

    return;
}

void ViewPortfolio()
{
    //sort the martix
    sort(purchased_stock.begin(), purchased_stock.end());

    //print titles
    cout << "Stock Name\tNumber of Shares\tPurchase Price\t\tCurrent Value" << endl;
    for (int row = 0; row < purchased_stock.size(); row++) {
        for (int col = 0; col < 4; col++) {
            //if the column is purchase_price or current_value, add an additional $ sign
            if (col > 1)
                cout << "\t$" << purchased_stock[row][col] << "\t\t";
            else
                cout << purchased_stock[row][col] << "\t\t";
        }
        cout << endl;
    }

    return;
}

void TotalValue()
{
    double sum = 0;
    for (int row = 0; row < purchased_stock.size(); row++) {
        //convert string to float, then add to sum
        //total value = number of shares * current value
        sum += stod(purchased_stock[row][1]) * stod(purchased_stock[row][3]);
    }
    
    cout << "The total value of your stocks is $" << sum << "." << endl;
}

string GenerateRandomValue()
{
    //declare a string stream
    stringstream decimal;
    //generate a random number between 1 to 100
    double random_price = rand() % 100 + 1;
    //round the number to 2 decimals
    decimal << fixed << setprecision(2) << random_price;
    //convert the the number to string
    string number = decimal.str();
    return number;
}