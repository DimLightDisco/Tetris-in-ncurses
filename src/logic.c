#include "../include/logic.h"
#include "../include/assets.h"


int rotate(int x, int y, int currentRotation) {
	int output;
	switch(currentRotation) {
		case 0: output = y * 4 + x; break;
		case 1: output = 12 + y - (x * 4); break;
		case 2: output = 15 - (y * 4) - x; break;
		case 3: output = 3 - y + (x * 4); break;
	}

	return output;
}

bool does_piece_fit(char *board[BOARD_WIDTH * BOARD_HEIGHT], char currentPiece[18], int currentRotation, int piecePosX, int piecePosY) {
	for(int y = 0; y < 4; ++y) {
		for(int x = 0; x < 4; ++x) {
			int boardIndex = (piecePosY + y) * BOARD_WIDTH + (piecePosX + x);
			
				// this checks wether the piece is within the board
			if (piecePosY + y >= 0 && piecePosY + y < BOARD_HEIGHT) {
				if (piecePosX + x >= 0 && piecePosX + x < BOARD_WIDTH) {
						// the piece is in bound, check collision
					if (currentPiece[rotate(x, y, currentRotation)] == 'x' && *board[boardIndex] == '#') {
						return false;
					}
				}
			}
		}
	}

	return true;
}
