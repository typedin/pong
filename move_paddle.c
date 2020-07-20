#include <stdio.h>
#include <SDL2/SDL.h>
#include "main.h"

#ifndef DOWN
#define DOWN 0
#endif

#ifndef UP
#define UP 1
#endif

extern paddle_t paddle[2];
extern ball_t ball;
extern SDL_Surface *screen;

void updateVerticalPosition(paddle_t *ptr, int amount) {
    ptr->y += amount;
}

int paddleAtTop(paddle_t paddle) {
    return paddle.y <= 0;
}

int paddleAtBottom(paddle_t paddle) {
    return paddle.y >= screen->h - paddle.h;
}

void move_paddle(int arrowKey) {
    if (arrowKey == UP && ! paddleAtTop(paddle[1])) {
        updateVerticalPosition(&paddle[1], -5);
    }
    if (arrowKey == DOWN && ! paddleAtBottom(paddle[1])) {
        updateVerticalPosition(&paddle[1], 5);
    }
}

int ballIsMovingRight() {
    return ball.dx > 0;
}

int ballMovingStraightAccross() {
    return ball.dy == 0;
}

void move_paddle_ai() {
    int center = paddle[0].y + 25;
    int screen_center = screen->h / 2 - 25;
    int ball_speed = abs(ball.dy);

    int amount = 0;
    if (ballIsMovingRight()) {
        //return to center position
        if (center < screen_center) {
            amount = ball_speed;
        }
        if (center > screen_center){
            amount = -ball_speed;
        }
    }

    //ball moving stright across
    if (ballMovingStraightAccross() && ! ballIsMovingRight()) {
        if (ball.y > center) {
            amount = 5;
        }
        if (ball.y < center){
            amount = -5;
        }
    }

    if (! ballMovingStraightAccross() && ! ballIsMovingRight()) {
        if (ball.y > center) {
            amount = ball_speed;
        }
        if (ball.y < center){
            amount = -ball_speed;
        }
    }

    updateVerticalPosition(&paddle[0], amount);
}
