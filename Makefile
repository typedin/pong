CC=clang

pong: main.c check_score.c collision.c move_paddle.c init.c
	$(CC) -o pong main.c check_score.c collision.c move_paddle.c init.c `sdl2-config --cflags --libs`

debug: main.c check_score.c collision.c move_paddle.c
	$(CC) -g -o pong main.c check_score.c collision.c move_paddle.c init.c `sdl2-config --cflags --libs`

clean:
	rm pong
