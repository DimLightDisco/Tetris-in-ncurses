#pragma once

#include <stdbool.h>
#include <string.h>
#include "assets.h"

typedef struct {
	int x, y;
} vector2;

	// some logic functions around manipulating the pieces and the board
int rotate(int x, int y, int currentRotation);
bool does_piece_fit(char *board[BOARD_WIDTH * BOARD_HEIGHT], char currentPiece[18], int currentRotation, int piecePosX, int piecePosY);
void freeze_piece(char *board[BOARD_WIDTH * BOARD_HEIGHT], char currentPiece[18], int currentRotation, int piecePosX, int piecePosY);
