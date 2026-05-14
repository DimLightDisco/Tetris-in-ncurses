#include "../include/logic.h"
#include "../include/assets.h"

	// this function is used to rotate the pieces by indexing it in a certian way
int rotate(int x, int y, int currentRotation) {
	int output;
	switch(currentRotation) {
		case 0: output = y * 4 + x; break; // 0°
		case 1: output = 12 + y - (x * 4); break; // 90°
		case 2: output = 15 - (y * 4) - x; break; // 180°
		case 3: output = 3 - y + (x * 4); break; // 270°
	}

	return output;
}

bool does_piece_fit(char *board[BOARD_WIDTH * BOARD_HEIGHT], char currentPiece[18], int currentRotation, int piecePosX, int piecePosY) {
		// The if statment is used to prevent a segfault caused by indexing over or under the board
	for(int y = 0; y < 4; ++y) 
	{ if (piecePosY + y >= 0 && piecePosY + y < BOARD_HEIGHT) 
	{
		for(int x = 0; x < 4; ++x) 
		{ if (piecePosX + x >= 0 && piecePosX + x < BOARD_WIDTH) 
		{
				// this is used to get the proper index inside the board
			int boardIndex = (piecePosY + y) * BOARD_WIDTH + (piecePosX + x);
			
				// checks wether the piece overlaps with the board
			if (currentPiece[rotate(x, y, currentRotation)] != '.' && *board[boardIndex] != '.') {
				return false; // if it does, then the doesn't fit so it returns false
			}
		}
		}
	}
	}

	return true; // if the piece doesn't overlap with the board returns true
}

	// essentially adds the piece into the board, freezing it in place
void freeze_piece(char *board[BOARD_WIDTH * BOARD_HEIGHT], char currentPiece[18], int currentRotation, int piecePosX, int piecePosY) {
	for(int y = 0; y < 4; ++y) 
	{ if (piecePosY + y >= 0 && piecePosY + y < BOARD_HEIGHT) 
	{
		for(int x = 0; x < 4; ++x) 
		{ if (piecePosX + x >= 0 && piecePosX + x < BOARD_WIDTH) 
		{
				// this is used to get the proper index inside the board
			int boardIndex = (piecePosY + y) * BOARD_WIDTH + (piecePosX + x);

				// adds the piece into the board
			if (currentPiece[rotate(x, y, currentRotation)] != '.' && *board[boardIndex] == '.') {
				*board[boardIndex] = currentPiece[16];
			}
		}
		}
	}
	}
}
