#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/assets.h"

typedef struct {
	int x, y;
} vector2;

void draw_board(char *board[BOARD_WIDTH * BOARD_HEIGHT]);
void draw_piece(char currentPiece[18], vector2 pos, int rotation);

int rotate(int px, int py, int rotation) {
	int output;
	switch(rotation) {
		case 0: output = py * 4 + px; break;         // 0 degrees
		case 1: output = 12 + py - (px * 4); break; // 90 degrees
		case 2: output = 15 - (py * 4) - px; break; // 180 degrees
		case 3: output = 3 - py + (px * 4); break;  // 270 degrees
	}
	return output;
}

int main() {
	int currentRotation = 0;
	char currentPiece[18];
	vector2 piecePos;

		// assets
	char tetrimino[7][18]; init_tetrimino(tetrimino);
	char *board[BOARD_WIDTH * BOARD_HEIGHT];
	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			board[y * BOARD_WIDTH + x] = malloc(sizeof(char));
		}
	} init_board(board);

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	noecho();
	srand(time(NULL));

	piecePos.x = 0; piecePos.y = 0;
	strcpy(currentPiece, tetrimino[rand() % 7]);

	bool game_over = FALSE;
	while(!game_over) {
			// TIME ---------------------------
		napms(50);

			// GAME LOGIC ---------------------
		switch(getch()) {
			case '\e': game_over = TRUE; break;
			case ' ': if (currentRotation == 3) currentRotation = 0; else ++currentRotation; break;
			case KEY_UP: piecePos.y--; break;
			case KEY_DOWN: piecePos.y++; break;
			case KEY_LEFT: piecePos.x--; break;
			case KEY_RIGHT: piecePos.x++; break;
		}

			// DRAWING ------------------------
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

void draw_piece(char currentPiece[17], vector2 pos, int rotation) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (currentPiece[rotate(x, y, rotation)] == 'x') {
				mvaddch(y + pos.y, x + pos.x, 'x');
			}
		}
	}
}


