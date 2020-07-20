#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 640
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 480
#endif

#ifndef MAIN_H
#define MAIN_H

typedef struct ball_s {
	int x, y;
	int w,h; // ball width and height
	int dx, dy; /* movement vector */
} ball_t;

typedef struct paddle {
	int x,y;
	int w,h;
} paddle_t;

#endif
