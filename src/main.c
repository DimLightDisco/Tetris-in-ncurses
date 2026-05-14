#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "../include/assets.h"
#include "../include/logic.h"

	// these functions are used to display the game
void draw_board(char *board[BOARD_WIDTH * BOARD_HEIGHT]);
void draw_current_piece(char currentPiece[18], vector2 piecePos, int currentRotation);
void draw_next_piece(char nextPiece[18]);

int main() {
		// declaring and initializing assets
	char tetrimino[7][18]; init_tetrimino(tetrimino);
	char *board[BOARD_WIDTH * BOARD_HEIGHT];
	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			board[y * BOARD_WIDTH + x] = malloc(sizeof(char));
		}
	} init_board(board);

		// piece variable
	vector2 piecePos;
	char currentPiece[18];
	char nextPiece[18];
	int currentRotation = 0;

	piecePos.x = BOARD_WIDTH / 2 - 2;
	piecePos.y = -1;
	strncpy(currentPiece, tetrimino[rand() % 7], 18);
	strncpy(nextPiece, tetrimino[rand() % 7], 18);

		// game variables
	int tick = 0;
	bool gameTickPassed = false;
	int score = 0;
	int speed = 1;

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	noecho();
	srand(time(NULL));

	bool game_over = FALSE;
	while(!game_over) {
			// TIME ---------------------------
		napms(50); tick += 1;
		switch(speed) {
			case 1:
				if (tick == 15) {
					gameTickPassed = true;
					tick = 0;
				}
				break;
			case 2:
				if (tick == 12) {
					gameTickPassed = true;
					tick = 0;
				}
				break;
			case 3:
				if (tick == 7) {
					gameTickPassed = true;
					tick = 0;
				}
				break;
			case 4:
				if (tick == 4) {
					gameTickPassed = true;
					tick = 0;
				}
				break;
			case 5:
				if (tick == 2) {
					gameTickPassed = true;
					tick = 0;
				}
				break;
		}

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

					// checks wether the next rotation is valid
				if (does_piece_fit(board, currentPiece, nextRotation, piecePos.x, piecePos.y)) {
					currentRotation = nextRotation;
				}
				break;
			case '\e': game_over = TRUE; break;
		}

			// GAME LOGIC ---------------------
			// this checks if a game tick has passed
		if (gameTickPassed) {
				// checks if the piece can be pushed down
			if (does_piece_fit(board, currentPiece, currentRotation, piecePos.x, piecePos.y + 1)) {
					// if it can, push it down
				piecePos.y++;
				gameTickPassed = false;
			} else {
					// if it can't, freeze the piece and spawn a new piece
				freeze_piece(board, currentPiece, currentRotation, piecePos.x, piecePos.y);
				
					// resets the piece to the top and cycles to the next piece
				piecePos.x = BOARD_WIDTH / 2 -2;
				piecePos.y = -1;

				strncpy(currentPiece, nextPiece, 18);
					// checks wether the new piece overlap with any of the frozen pieces
				if (!does_piece_fit(board, currentPiece, currentRotation, piecePos.x, piecePos.y)) {
					game_over = true; // if so, that means it's game over
				}
				strncpy(nextPiece, tetrimino[rand() % 7], 18);

				currentRotation = 0;

				gameTickPassed = false;
			}
		}
			// DISPLAY ------------------------
		erase();
		draw_board(board);
		draw_current_piece(currentPiece, piecePos, currentRotation);
		draw_next_piece(nextPiece);
		refresh();
	}

	free(*board);
	endwin(); return 0;
}

void draw_board(char *board[BOARD_WIDTH * BOARD_HEIGHT]) {
	for (int y = 0; y < BOARD_HEIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			if (*board[y * BOARD_WIDTH + x] != '.') {
				mvaddch(y, x, *board[y * BOARD_WIDTH + x]);
			}
		}
	}
}

void draw_current_piece(char currentPiece[18], vector2 piecePos, int currentRotation) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (currentPiece[rotate(x, y, currentRotation)] != '.') {
				mvaddch(y + piecePos.y, x + piecePos.x, 'x');
			}
		}
	}
}


void draw_next_piece(char nextPiece[18]) {
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			if (nextPiece[rotate(x, y, 0)] != '.') {
				mvaddch(y + 3, x + BOARD_WIDTH + 2, 'x');
			}
		}
	}
}
