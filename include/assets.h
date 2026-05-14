#pragma once

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 19

	/* these functions makes/initialize all the assets in the program
	 * (aka: the tetrimino blocks and the board)
	 */
void init_tetrimino(char tetrimino[7][18]);
void init_board(char *board[BOARD_WIDTH * BOARD_HEIGHT]);
