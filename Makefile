main: src/main.c
	gcc 'src/main.c' 'src/assets.c' 'src/logic.c' -lncurses -o tetris
