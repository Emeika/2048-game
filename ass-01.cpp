#include <iostream>
#include <string>
using namespace std;

void display_grid(int grid[4][4]) {

    cout << "/-------|-------|-------|-------\\" << endl;
    for (int i = 0; i < 4; i++){ // Loop through each row
        for (int j = 0; j < 4; j++){ // Loop through each column
            if (grid[i][j] == 0) {
                cout << "|" << "\t";  // Print empty space when 0/ No value
            }
            else {
                cout << "|" << "      " << grid[i][j]; // Print the value at position (i,j)
            }
            
        }
        cout << "|" << endl;
        if (i != 3) {
            cout << "|-------|-------|-------|-------|" << endl;
        }
    }
    cout << "\\-------|-------|-------|-------/" << endl;

}


// This function initializes a 4x4 grid with all values starting at 0.
void start_game() {
    int grid[4][4]; // Initializes an integer array called 'grid' with dimensions of 4x4.
    srand(time(0));
    int rand_row1 = rand() % 4;
    int rand_col1 = rand() % 4;

    int rand_row2 = rand() % 4;
    int rand_col2 = rand() % 4;
    while ( (rand_row1 == rand_row2) && (rand_col1 == rand_col2) ) {  // To make sure that the 2 random tiles aren't the same
        int rand_row2 = rand() % 4;
        int rand_col2 = rand() % 4;
    }


    for (int i = 0; i < 4; i++){ // Loop through each row of the grid.
        for (int j = 0; j < 4; j++){ // Loop through each column of the grid.
            if ( i ==  rand_row1 && j == rand_col1) {
                int random_num = (rand() % 2) ? 4 : 2; // generates either 0 or 1 and sets random_num to either 2 or 4
                grid[i][j] = random_num;
            }
            else if ( i ==  rand_row2 && j == rand_col2) {
                int random_num = (rand() % 2) ? 4 : 2; // generates either 0 or 1 and sets random_num to either 2 or 4
                grid[i][j] = random_num;
            }
            else {
                grid[i][j] = 0; // Set the value at position (i,j) to 0

            }

        }
    }
    display_grid(grid);
    move();
}





int main() {

    int choice;
    cout << "\n     Welcome to 2048\n\nPress(1-3)\n1. START\n2. INSTRUCTIONS\n3. QUIT\n";
    cin >> choice;
    move();
    while (choice != 3) {
        if (choice == 1){
            start_game();
            cout << "Press(1-3)\n1. START New Game\n2. INSTRUCTIONS\n3. QUIT\n";
            cin >> choice;
        }
        else if (choice == 2) {
            cout << "When the user choose Start, the game starts with two tiles, each with a value of either 2 or 4, on a 4x4 grid. \n";
            cout << "The player can move the tiles up, down, left, or right using the arrow keys.All tiles slide as far as possible in the chosen direction,\n";
            cout << "until they are stopped by either another tile or the edge of the grid.\n";
            cout << "If two tiles of the same number collide while moving, they merge into a single tile with the total value of the two tiles.\n";
            cout << "Every time the player makes a move, a new tile randomly appears on the grid with a value of either 2 or 4.\n";
            cout << "The game ends when the player reaches the 2048 tile or there are no more possible moves.\n";
            cout << "Move on the tiles using the arrow keys. ← → ↑ ↓ \n\n";
            cout << "Press(1-3)\n1. START New Game\n2. INSTRUCTIONS\n3. QUIT\n";
            cin >> choice;
        }
    }

}


