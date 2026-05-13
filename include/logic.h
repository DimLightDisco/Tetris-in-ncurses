#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include "assets.h"

typedef struct {
	int x, y;
} vector2;

// some game logic functions around manipulating the pieces
int rotate(int x, int y, int currentRotation);
bool does_piece_fit(char *board[BOARD_WIDTH * BOARD_HEIGHT], char currentPiece[18], int currentRotation, int piecePosX, int piecePosY);

#endif
