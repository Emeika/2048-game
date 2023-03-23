#include <iostream>
#include <string>
using namespace std;

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

void display_grid() {

}



int main() {

    int choice;
    cout << "\n     Welcome to 2048\n\nPress(1-3)\n1. START\n2. INSTRUCTIONS\n3. QUIT\n";
    cin >> choice;
    start_game();
}


