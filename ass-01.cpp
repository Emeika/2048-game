// It contains functions such as getch() 
//which reads a character from the console without echoing it to the screen
#include <conio.h>
#include <iostream>
#include <iomanip>  // Include the <iomanip> library for setw()

using namespace std;

// used for switch which takes user input for arrow keys
#define KEY_UP    72  
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
int bst_score = 0;   // Global variable for User High score

void display_grid(int grid[4][4],int &score) {

    cout << "\n/-------|-------|-------|-------\\" << endl;
    for (int i = 0; i < 4; i++){ // Loop through each row
        for (int j = 0; j < 4; j++){ // Loop through each column
            if (grid[i][j] == 0) {
                cout << "|" << setw(7) << " ";  // Print empty space with a width of 7 spaces when 0 value
            }
            else {
                cout << "|" << setw(7) << grid[i][j]; // Print the value at position (i,j) with a width of 7 spaces
            }
            
        }
        cout << "|" << endl;
        if (i != 3) {
            cout << "|-------|-------|-------|-------|" << endl;
        }
    }
    cout << "\\-------|-------|-------|-------/" << endl << endl;
    cout << "================================" << endl;
    cout << "Score: " << score << endl;  // Print the score to the screen
    cout << "High Score: " << bst_score << endl;
}

void add_tile(int grid[4][4], int &score){
    int empty_tile[16][2];   //Store the empty cells in a new array 4x4 = 16
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
    system("cls");  //clear screen
    display_grid(grid, score);
}

bool game_over(int grid[4][4]){

    // Check if any tile has reached 2048
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(grid[i][j] == 2048) {
                return true;
            }
        }
    }

    // Check if there are any empty cells
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(grid[i][j] == 0) {
                return false;
            }
        }
    }

    // Check if there are any adjacent tiles with the same value
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(grid[i][j] == grid[i][j+1] || grid[i][j] == grid[i+1][j]) {
                return false;
            }
        }
    }

    return true;
}

bool move_up(int grid[4][4], int &score, bool moved){
    for (int j = 0; j < 4; j++) {           // Loop through each column
        for (int i = 1; i < 4; i++) {       // Loop through each row
            if (grid[i][j] != 0) {         // If the current cell is not empty
                int k = i;                // k is row
                while (k > 0 && grid[k-1][j] == 0) { // Move the cell up as long as the cell above it is empty and doesn't reaches edge
                    grid[k-1][j] = grid[k][j];        // Move the cell up
                    grid[k][j] = 0;                  // Set the old cell to empty
                    k--;                              // Move up to the next cell
                    moved = true;                     // moved successfully
                }
                if (k > 0 && grid[k-1][j] == grid[k][j]) { // If the cell above the current cell has the same value
                    grid[k-1][j] *= 2;                    // Double the value of the upper cell
                    score += grid[k-1][j];                 // Increase the score by the value of the upper cell
                    grid[k][j] = 0;                        // Set the current cell to empty
                    moved = true;                           // moved successfully
                }
            }
        }
    }
    return moved;
}

bool move_down(int grid[4][4], int &score, bool moved){
    for (int j = 0; j < 4; j++) {                   // Loop through each column
        for (int i = 2; i >= 0; i--) {              // Loop through each row, starting from the second last row and going backwards
            if (grid[i][j] != 0) {                  // If the current cell is not empty
                int k = i;
                while (k < 3 && grid[k+1][j] == 0) { // Move the cell down as long as the cell below it is empty
                    grid[k+1][j] = grid[k][j];       // Move the cell down
                    grid[k][j] = 0;                 // Set the old cell to empty
                    k++;                             // Move down to the next cell
                    moved = true;                    // Set moved to true, indicating a successful move
                }
                if (k < 3 && grid[k+1][j] == grid[k][j]) { // If the cell below the current cell has the same value
                    grid[k+1][j] *= 2;                    // Double the value of the lower cell
                    score += grid[k+1][j];                 // Increase the score by the value of the lower cell
                    grid[k][j] = 0;                        // Set the current cell to empty
                    moved = true;                           // Set moved to true, indicating a successful move
                }
            }
        }
    }

    return moved;

}

bool move_right(int grid[4][4], int &score, bool moved) {
    for (int i = 0; i < 4; i++) {               // Loop through each row of the grid
        for (int j = 2; j >= 0; j--) {  // Loop through each column from the second to last column, moving right to left
            if (grid[i][j] != 0) {              // If the tile is not empty
                int k = j;                    // Start checking for an empty tile to the right of the current tile
                while (k < 3 && grid[i][k+1] == 0) {  // While there is an empty tile to the right of the current tile
                    grid[i][k+1] = grid[i][k];      // Move the current tile to the right
                    grid[i][k] = 0;                // Set the current tile to empty
                    k++;                        // Check the next tile to the right
                    moved = true;              // Set moved to true since tiles were moved
                }
                if (k < 3 && grid[i][k+1] == grid[i][k]) {  // If the next tile to the right has the same value
                    grid[i][k+1] *= 2;        // Merge the two tiles by doubling the value of the next tile
                    score += grid[i][k+1];     // Add the value of the merged tile to the score
                    grid[i][k] = 0;            // Set the current tile to empty
                    moved = true;              // Set moved to true since tiles were moved
                }
            }
        }
    }
    return moved;

}

bool move_left(int grid[4][4], int &score, bool moved){
    for (int i = 0; i < 4; i++) {              // Loop through each row
        for (int j = 1; j < 4; j++) {          // Loop through each column starting from the second column
            if (grid[i][j] != 0) {             // If the cell at (i, j) is not empty
                int k = j;                     // Set k to the current column index
                while (k > 0 && grid[i][k-1] == 0) { // Move the cell to the left until it reaches the leftmost column or encounters a non-empty cell
                    grid[i][k-1] = grid[i][k];      // Move the cell to the left
                    grid[i][k] = 0;                 // Set the current cell to empty
                    k--;                      // Decrement k to move to the next column to the left
                    moved = true;              // Set the moved flag to true
                }
                if (k > 0 && grid[i][k-1] == grid[i][k]) {    // If the cell to the left has the same value
                    grid[i][k-1] *= 2;         // Double the value of the cell to the left
                    score += grid[i][k-1];     // Update the score with the new value
                    grid[i][k] = 0;            // Set the current cell to empty
                    moved = true;              // Set the moved flag to true
                }
            }
        }
    }
    return moved;

}

void movement(int grid[4][4], int &score) {
    // A flag to check if any movement was made or not for placing a new tile on the grid
    bool moved = false;
    
    // Keep playing until the game is over
    while (!game_over(grid)) {
        int c, ex;
        
        // Get the input using getch() function
        c = getch();
    
        // If the input is not an arrow key, skip this iteration of the loop and continue waiting for an arrow key
        if (c && c != 224){
            continue;
        }
    
        // Otherwise, get the next character using getch()
        else{
            switch (ex = getch()) {
                // Move up
                case KEY_UP:
                    moved = move_up(grid, score, moved);
                    break;
                // Move down
                case KEY_DOWN:
                    moved = move_down(grid, score, moved);
                    break;
    
                // Move right
                case KEY_RIGHT:
                    moved = move_right(grid, score, moved);
                    break;
    
                // Move left
                case KEY_LEFT:
                    moved = move_left(grid, score, moved);
                    break;
    
                // If any other key is pressed, skip this iteration of the loop and wait for an arrow key
                default:
                    continue;
            }
        }
    
        // After each movement, display the updated grid and score
        display_grid(grid, score);
    
        // If any movement was made, place a new tile on the grid
        if(moved) {
            add_tile(grid, score);
        }
    }
    

    system("cls");

    cout << "\n\n";
    cout << "====================================\n" << endl;
    cout << "            Game Over               \n" << endl;
    cout << "====================================\n" << endl;
    cout << "    Congratulations!          \n" << endl;
    cout << "    Best Record: " << score << endl;
    cout << "====================================\n\n" << endl;

    if (bst_score < score) {          // Check if current score is higher than the best score
        cout << "    New Record Made!               \n" << endl;
        cout << "====================================\n\n" << endl;
        bst_score = score;        // update the High score if yes

    }
}


void start_game(int &bst_score) {
    system("cls");        //To clear screen

    int grid[4][4];      // Initializes an integer array called 'grid' with dimensions of 4x4.
    srand(time(0));   // seeds the random number generator with the current time to generate a different sequence of random numbers.
    // random index position for first number
    int rand_row1 = rand() % 4;   // generates a random number between 0 and 3 
    int rand_col1 = rand() % 4;

    // random index position for second number   
    int rand_row2 = rand() % 4;
    int rand_col2 = rand() % 4;
    while ( (rand_row1 == rand_row2) && (rand_col1 == rand_col2) ) {  // To make sure that the 2 random tiles aren't the same
        int rand_row2 = rand() % 4;
        int rand_col2 = rand() % 4;
    }


    for (int i = 0; i < 4; i++){ // Loop through each row of the grid.
        for (int j = 0; j < 4; j++){ // Loop through each column of the grid.
            if ( i ==  rand_row1 && j == rand_col1) {   // Iterate till the index position is matched for 1st random tile
                int random_num = (rand() % 2) ? 4 : 2; // generates either 0 or 1 and sets random_num to either 2 or 4
                grid[i][j] = random_num;    // Set the index position with either 2 or 4
            }
            else if ( i ==  rand_row2 && j == rand_col2) {   // Iterate till the index position is matched for 2nd random tile
                int random_num = (rand() % 2) ? 4 : 2; // generates either 0 or 1 and sets random_num to either 2 or 4
                grid[i][j] = random_num;         // Set the index position with either 2 or 4
            }
            else {
                grid[i][j] = 0; // Set the value at the remaining positions to 0
            }
        }
    }
    int s = 0; //Score
    // Function call with pass by value for score
    display_grid(grid, s);

    movement(grid, s);

}


int main() {
    int choice, inp, bst_score=0;
    cout << "\n     Welcome to 2048\n\nPress(1-3)\n1. START\n2. INSTRUCTIONS\n3. QUIT\n";
    cin >> choice;
    while (choice != 3) {   // loop runs until quit game
        if (choice == 1){
            start_game(bst_score);
            cout << "1. Restart New game\n" << endl;
            cout << "2. Exit to main menu\n" << endl;
            cin >> inp;
            while (inp == 1) {    // loop after game ends prompting user to go back to exit or restart 
                start_game(bst_score);
                cout << "1. Restart New game\n" << endl;
                cout << "2. Exit to main menu\n" << endl;
                cin >> inp;
            }
            system("cls");
            
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
            cout << "Move on the tiles using the arrow keys.\n\n";
            cout << "Press(1-3)\n1. START New Game\n2. INSTRUCTIONS\n3. QUIT\n";
            cin >> choice;
        }
    }
}


