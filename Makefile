CC=clang

pong: main.c check_score.c collision.c move_paddle.c
	$(CC) -o pong main.c check_score.c collision.c move_paddle.c `sdl2-config --cflags --libs`

debug: main.c check_score.c collision.c move_paddle.c
	$(CC) -g -o pong main.c check_score.c collision.c move_paddle.c `sdl2-config --cflags --libs`

clean:
	rm pong
