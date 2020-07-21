CC=clang
CFLAGS = -Wall
pong: main.c check_score.c collision.c move_paddle.c init.c
	$(CC) $(CFLAGS) -o pong main.c check_score.c collision.c move_paddle.c init.c `sdl2-config --cflags --libs`

debug: main.c check_score.c collision.c move_paddle.c
	$(CC) $(CFLAGS) -g -o pong main.c check_score.c collision.c move_paddle.c init.c `sdl2-config --cflags --libs`

clean:
	rm pong
