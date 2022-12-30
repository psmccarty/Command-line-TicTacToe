#ifndef __TicTacToe_h__
#define __TicTacToe_h__
/**
 * Place the move of the player on the board. Return 0 on fail anything else on success
 */
int move(int player, int row, int col, char** board);
/**
 * Print the board to stdout
 */
void printBoard(char** board);

/**
 * Initialize board. Return 0 on fail, anything else on success
 */
char** initBoard();

/**
 * Check the winner. Return 0 if there is a winner. false otherwise
 */
int checkWin(char** board, int player);

/**
 * Run command loop for game
 */
void runCommandLoop(char** board);

/**
 * Get the coordinates of the next move
 */
int getMove(int* row, int* col);
#endif 
