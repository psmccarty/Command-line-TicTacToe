#include <stdio.h>
#include <stdlib.h>

#include "TicTacToe.h"

// A command line tic tac toe game for two players
// Author: Patrick McCarty
// Status: complete, working properly
// Date created: 12/25/2022
// Date compleated: 12/26/2022

#define ROWS 3
#define COLS 3


/**
 * Run the tic tac toe application
 */
int main(void){

	char ** board = initBoard(); // tic tac toe board
	
	runCommandLoop(board);

	for(int i = 0; i < ROWS; i++){
		free(board[i]);	
	}

	free(board);
	return 0;
}

/**
 * Place the move of the player on the board. Return 1 on fail and 0 on success
 */
int move(int player, int row, int col, char** board){
	if(row < 0 || row >= ROWS){
		return 1;	
	}
	if(col < 0 || col >= COLS){
		return 1;	
	}
	if(board[row][col] != ' '){
		return 1;	
	}
	board[row][col] = player == 1 ? 'X' : 'O';
	return 0;
}

/**
 * Print the board to stdout
 */
void printBoard(char** board){

	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			printf("%c", board[i][j]);
			if(j != 2){
				printf(" | ");	
			}	
		}
		printf("\n");
		if(i != 2){
			printf("---------\n");
		}
	}

}

/**
 * Initialize board. Return 0 on fail, anything else on success
 */
char** initBoard(){
	char** board;
	if((board = malloc(sizeof(char*) * ROWS)) == NULL){
		printf("Unable to allocate memory\n");
		exit(1);	
	}
	for(int i = 0; i < ROWS; i++){
		if((board[i] = malloc(sizeof(char) * COLS)) == NULL){
			printf("Unable to allocate memory\n");
			exit(1);	
		}	
		for(int j = 0; j < COLS; j++){
			board[i][j] = ' ';	
		}
	}
	return board;
}

/**
 * Check the winner. Return 1 if there is a winner, 0 otherwise
 */
int checkWin(char** board, int player){

	char symbol = player == 1 ? 'X' : 'O'; // symbol of the current player

	for(int i = 0; i < ROWS; i++){
		if(board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol){
			return 1;		
		}
		if(board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol){
			return 1;	
		}
	}
	if(board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol){
		return 1;	
	}

	if(board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol){
		return 1;	
	}

	return 0;
}

/**
 * Run command loop for game
 */
void runCommandLoop(char** board){
	int moves = 0;  // number of moves that have been completed
	char win = 0;   // 1 if a player has won. 0 otherwise
	int currPlayer; // 1 for player 1. 2 for player 2
	int row;        // row selected for next move
	int col;        // col selected for next move

	while(moves < 9 && !win){
		currPlayer = (moves % 2) + 1;
		printBoard(board);
		printf("\n");
		printf("Player%d\'s turn\n", currPlayer);
		if(getMove(&row, &col)){
			printf("Unable to read input. Please type a number in the range 0-2.\n");
			continue;
		}
		printf("\n");
		if(move(currPlayer, row, col, board)){
			printf("Invalid move. Please type a number in the range 0-2.\n");	
			continue;
		}
		if(checkWin(board, currPlayer)){
			printf("Congratulations! Player%d wins!\n", currPlayer);
			printBoard(board);		
			win = 1;	
		}
		moves++;
	}
	if(!win){
		printf("Its a draw\n");	
	}

}

/**
 * Get the coordinates of the next move. Return 0 on success and 1 on failure
 */
int getMove(int* row, int* col){
	char buf1[100]; // buffer to hold input for rows
	char buf2[100]; // buffer to hold input for cols 
	char* str1;     // used for error checking for fgets
	char* str2;     // used for error checking for fgets
	char* ptr1;     // used for error checking for strtol
	char* ptr2;     // used for error checking for strtol
	int r;          // temp to store the int representation for row
	int c;          // temp to store the int representation for col 
	printf("Row of your placement: ");
	if((str1 = fgets(buf1, 100, stdin)) == NULL){
		printf("Unable to read from stdin\n");
		exit(1);	
	}
	
	printf("Col of your placement: ");
	if((str2 = fgets(buf2, 100, stdin)) == NULL){
		printf("Unable to read from stdin\n");
		exit(1);	
	}


	r = strtol(buf1, &ptr1, 10);
	c = strtol(buf2, &ptr2, 10);
	if(str1 == ptr1 || str2 == ptr2){
		return 1;	
	}
	*row = r;
	*col = c;

	return 0;
}
