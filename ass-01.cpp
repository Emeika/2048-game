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
    cout << "\\-------|-------|-------|-------/" << endl << endl;

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

    
    move(grid);
}

void add_tile(int grid[4][4]){
    int empty_tile[16][2];   //Store the empty cells in a new array 
    int numEmptyCells = 0;   // Column is the x and y index of the empty grid cell and row is the number of empty indices of grid

    for (int i = 0; i < 4; i++){   // Loop through each row and col of the grid
        for (int j = 0; j < 4; j++) {
            if (grid[i][j] == 0) {   // Check if empty then store the index value to the empty_tile array
                empty_tile[numEmptyCells][0] = i;
                empty_tile[numEmptyCells][1] = j;
                numEmptyCells++;  // Number of empty cell adds up as a new index is stored in the array
            }
        }
    }

    if(numEmptyCells > 0) {  // Add a new tile when there are any empty cells
        int random_tile = rand() % numEmptyCells;  // random number between 0 and Num of empty cell
        int random_row = empty_tile[random_tile][0];  // get the row value stored in that cell of empty_tile
        int random_col = empty_tile[random_tile][1];  // get the col value stored in that cell
        int random_num = (rand() % 2) ? 4 : 2; // generates either 0 or 1 and sets random_num to either 2 or 4
        grid[random_row][random_col] = random_num;  // place the random num to the available index in grid


    }
    display_grid(grid);
}




void move(int grid[4][4]){
    int score = 0;
    bool moved = false;

    char ch;
    cin >> ch;

    if (ch == 27) { // Check if it's an escape sequence
        char arrow;
        cin >> arrow; // Read the next character

        if (arrow == '[') { // Check if it's a control sequence
            cin >> arrow; // Read the control character

            switch (arrow) { // Check which arrow key was pressed
                case 'A':
                    for (int j = 0; j < 4;  j++){ 
                        for (int i = 1; i < 4; i++){
                            if(grid[i][j] != 0) {
                                int k = i;
                                while(k > 0 && grid[k-1][j] == 0) {
                                    grid[k-1][j] = grid[k][j];
                                    grid[k][j] = 0;
                                    k--;
                                    moved = true;
                                }
                                if(k > 0 && grid[k-1][j] == grid[k][j]) {
                                    grid[k - 1][j] *= 2;
                                    score += grid[k - 1][j];
                                    grid[k][j] = 0;
                                    moved = true;
                                }
                            }
                        }
                    }
                    break;
                case 'B':  //Move down
                    for(int j = 0; j < 4; j++) {
                        for(int i = 2; i >= 0; i--) {
                            if(grid[i][j] != 0) {
                                int k = i;
                                while(k < 3 && grid[k+1][j] == 0) {
                                    grid[k+1][j] = grid[k][j];
                                    grid[k][j] = 0;
                                    k++;
                                    moved = true;
                                }
                                if(k < 3 && grid[k+1][j] == grid[k][j]) {
                                    grid[k + 1][j] *= 2;
                                    score += grid[k + 1][j];
                                    grid[k][j] = 0;
                                    moved = true;
                                }
                            }
                        }
                    }
                    break;
                case 'C':  //Move right
                    for(int i = 0; i < 4; i++) {
                        for(int j = 2; j >= 0; j--) {
                            if(grid[i][j] != 0) {
                                int k = j;
                                while(k < 3 && grid[i][k+1] == 0) {
                                    grid[i][k+1] = grid[i][k];
                                    grid[i][k] = 0;
                                    k++;
                                    moved = true;
                                }
                                if(k < 3 && grid[i][k+1] == grid[i][k]) {
                                    grid[i][k + 1] *= 2;
                                    score += grid[k + 1][j];
                                    grid[i][k] = 0;
                                    moved = true;
                                }
                            }
                        }
                    }
                    break;

                case 'D':// Move tiles left
                    for(int i = 0; i < 4; i++) {
                        for(int j = 1; j < 4; j++) {
                            if(grid[i][j] != 0) {
                                int k = j;
                                while(k > 0 && grid[i][k-1] == 0) {
                                    grid[i][k-1] = grid[i][k];
                                    grid[i][k] = 0;
                                    k--;
                                    moved = true;
                                }
                                if(k > 0 && grid[i][k-1] == grid[i][k]) {
                                    grid[i][k - 1] *= 2;
                                    score += grid[k - 1][j];
                                    grid[i][k] = 0;
                                    moved = true;
                                }
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    } else {
        move(grid);
    }
    display_grid(grid);
    cout << "Score: " << score << endl;  // Print the score to the screen

    if(moved) {
        // Place a new tile
        add_tile(grid);
}


int main() {
    int choice;
    cout << "\n     Welcome to 2048\n\nPress(1-3)\n1. START\n2. INSTRUCTIONS\n3. QUIT\n";
    cin >> choice;
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


