#include <string.h>
#include "../include/assets.h"

void init_tetrimino(char tetrimino[7][18]) {
	strcpy(tetrimino[0], "..x...x...x...x.0"); // I piece
	strcpy(tetrimino[1], "..x..xx..x......1"); // S right piece
	strcpy(tetrimino[2], ".x...xx...x.....2"); // S left piece
	strcpy(tetrimino[3], ".....xx..xx.....3"); // Square piece
	strcpy(tetrimino[4], ".....xx...x...x.4"); // L right piece
	strcpy(tetrimino[5], ".....xx..x...x..5"); // L left piece
	strcpy(tetrimino[6], "......x..xx...x.6"); // T piece
}

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
