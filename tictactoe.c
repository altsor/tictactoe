#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);


int main(){

    char winner = ' '; // if empty there is no winner, otherwise = 'X' or 'O'
    char response; 
    do
    {
        winner = ' ';
        response = ' ';
        resetBoard();

        while(winner == ' ' && checkFreeSpaces() != 0){  // While there is no winner and empty spaces remaining
            
            printBoard();

            playerMove();
            winner = checkWinner();

            if(winner != ' ' || checkFreeSpaces() == 0){
                break;
            }
            computerMove();
            winner = checkWinner();

            if(winner != ' ' || checkFreeSpaces() == 0){
                break;
            }
        }
        
        printBoard();
        printWinner(winner);

        printf("\nWould you like to play agan (Y/N)");

        scanf("%c"); // Clears the buffer incase there is a new line char
        scanf("%c", &response);
        response = toupper(response);

    } while (response == 'Y');
    
    printf("Thanks for playing!");
    printf("\n");
    
    return 0;
}

void resetBoard(){  //Resets the board to empty chars

    for(int i =0; i< 3; i++){
        for(int j = 0; j<3; j++){
            board[i][j] = ' ';
        }

    }

}
void printBoard(){  //Prints current state of the board
    printf(" %c | %c | %c", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|...\n");
    printf(" %c | %c | %c", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|...\n");
    printf(" %c | %c | %c", board[2][0], board[2][1], board[2][2]);
    printf("\n");

}
int checkFreeSpaces(){

    int freeSpaces = 9; 
    for(int i =0; i< 3; i++){
        for(int j = 0; j<3; j++){
            if(board[i][j] != ' '){
                freeSpaces--; 
            }
        }
    }
    return freeSpaces;


}
void playerMove(){
    int x;
    int y;
    
    do
    {

        printf("Enter row number (1-3)");
        scanf("%d", &x);
        x--;
        printf("Enter column number (1-3)");
        scanf("%d", &y);
        y--;

        if(board[x][y] != ' ' || x<0 || x>2 || y<0 || y>2 ){
          printf("Invalid move! \n");
        }
        else{
           board[x][y] = PLAYER;
           break;
        }

    } while (board[x][y] != ' ');
    
}
void computerMove(){ 

    //creates a seed based on current time
    srand(time(0));
    int x;
    int y;

    if(checkFreeSpaces() > 0){
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');  // Keep generating random numbers untill open space is found
        board[x][y] = COMPUTER;
    }
    else{
        printWinner(' ');
    }


}
char checkWinner(){ //Check if anyone won
    //check rows
    for(int i = 0; i<3; i++){
        if(board[i][0] == board[i][1] && board[i][0] == board [i][2]){
            return board[i][0];
        }
    }
    // check collumns
    for(int i = 0; i<3; i++){
        if(board[0][i] == board[1][i] && board[0][i] == board [2][i]){
            return board[0][i];
        }
    }
    // Check diagonals
    if(board[1][1] == board [0][0] && board[1][1] == board[2][2]){
        return board[1][1];
    }
    if(board[1][1] == board [0][2] && board[1][1] == board[2][0]){
        return board[1][1];
    }
    return ' ';

}
void printWinner(char winner){
    if(winner == PLAYER){
        printf("YOU WIN!\n");
    }else if(winner == COMPUTER){
        printf("COMPUTER WINS!\n");
    } else{
        printf("It's a draw...\n");
    }
}