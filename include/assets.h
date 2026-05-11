#ifndef ASSETS_H
#define ASSETS_H

// the size of the board
#define BOARD_WIDTH 12
#define BOARD_HEIGHT 18

// these functions makes/initialize all the assets
void init_tetrimino(char tetrimino[7][18]);
void init_board(char *board[BOARD_WIDTH * BOARD_HEIGHT]);

#endif
