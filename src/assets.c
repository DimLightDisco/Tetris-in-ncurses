#include <string.h>
#include "../include/assets.h"

	// initializes all the tetrimino blocks inside the string to be used in the program
void init_tetrimino(char tetrimino[7][18]) {
		/* the x character makes the piece itself and the periods are empty space
		 + the last character is going to be used to tag the pieces to their
		 * specific color
		 */
	strncpy(tetrimino[0], "..x...x...x...x.0", 18); // I piece
	strncpy(tetrimino[1], "..x..xx..x......1", 18); // S right piece
	strncpy(tetrimino[2], ".x...xx...x.....2", 18); // S left piece
	strncpy(tetrimino[3], ".....xx..xx.....3", 18); // Square piece
	strncpy(tetrimino[4], ".....xx...x...x.4", 18); // L right piece
	strncpy(tetrimino[5], ".....xx..x...x..5", 18); // L left piece
	strncpy(tetrimino[6], "......x..xx...x.6", 18); // T piece
}

	// initializes the board, with walls as hashtags and  empty space as periods
void init_board(char *board[BOARD_WIDTH * BOARD_HEIGHT]) {
	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			if (x == 0 || x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1) {
				*board[y * BOARD_WIDTH + x] = '#';
			} else {
				*board[y * BOARD_WIDTH + x] = '.';
			}
		}
	}
}
