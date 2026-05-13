#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/assets.h"
#include "../include/logic.h"

void draw_board(char *board[BOARD_WIDTH * BOARD_HEIGHT]);
void draw_piece(char currentPiece[18], vector2 piecePos, int rotation);

int main() {
		// assets
	char tetrimino[7][18]; init_tetrimino(tetrimino);
	char *board[BOARD_WIDTH * BOARD_HEIGHT];
	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			board[y * BOARD_WIDTH + x] = malloc(sizeof(char));
		}
	} init_board(board);

	vector2 piecePos; piecePos.x = BOARD_WIDTH / 2 - 2; piecePos.y = -2;
	char currentPiece[18]; srand(time(NULL)); strcpy(currentPiece, tetrimino[rand() % 7]);
	int currentRotation = 0;

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	noecho();

	bool game_over = FALSE;
	while(!game_over) {
			// TIME ---------------------------
		napms(50);

			// INPUTS -------------------------
		switch(getch()) {
			case KEY_UP: 
				if (does_piece_fit(board, currentPiece, currentRotation, piecePos.x, piecePos.y - 1))
					piecePos.y--; 
				break;
			case KEY_DOWN: 
				if (does_piece_fit(board, currentPiece, currentRotation, piecePos.x, piecePos.y + 1))
					piecePos.y++; 
				break;
			case KEY_LEFT: 
				if (does_piece_fit(board, currentPiece, currentRotation, piecePos.x - 1, piecePos.y))
					piecePos.x--; 
				break;
			case KEY_RIGHT:
				if (does_piece_fit(board, currentPiece, currentRotation, piecePos.x + 1, piecePos.y))
					piecePos.x++; 
				break;

			case ' ':
					// nextRotation is used so it doesn't break the rotate function in does_piece_fit
				int nextRotation;
				if (currentRotation == 3) {
					nextRotation = 0;
				}
				else {
					nextRotation = currentRotation + 1;
				}

				if (does_piece_fit(board, currentPiece, nextRotation, piecePos.x, piecePos.y)) {
					currentRotation = nextRotation;
				}
				break;
			case '\e': game_over = TRUE; break;
		}

			// GAME LOGIC ---------------------
			// DISPLAY ------------------------
		erase();
		draw_board(board);
		draw_piece(currentPiece, piecePos, currentRotation);
		refresh();
	}

	free(*board);
	endwin(); return 0;
}

void draw_board(char *board[BOARD_WIDTH * BOARD_HEIGHT]) {
	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			if (x == 0 || x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1) {
				mvaddch(y, x, *board[y * BOARD_WIDTH + x]);
			}
		}
	}
}

void draw_piece(char currentPiece[17], vector2 piecePos, int currentRotation) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (currentPiece[rotate(x, y, currentRotation)] == 'x') {
				mvaddch(y + piecePos.y, x + piecePos.x, 'x');
			}
		}
	}
}


