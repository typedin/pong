#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "check_score.h"
#include "collision.h"
#include "init.h"
#include "main.h"
#include "move_paddle.h"

// Program globals
ball_t ball;
paddle_t paddle[2];
int width, height; // used if fullscreen

SDL_Window *window = NULL; // The window we'll be rendering to
SDL_Renderer *renderer;    // The renderer SDL will use to draw to the screen

// surfaces
SDL_Surface *screen;
SDL_Surface *title;
SDL_Surface *numbermap;
SDL_Surface *end;

// textures
SDL_Texture *screen_texture;

// Initialize starting position and sizes of game elemements
static void init_game() {

  ball.x = screen->w / 2;
  ball.y = screen->h / 2;
  ball.w = 10;
  ball.h = 10;
  ball.dy = 1;
  ball.dx = 1;

  paddle[0].x = 20;
  paddle[0].y = screen->h / 2 - 50;
  paddle[0].w = 10;
  paddle[0].h = 50;

  paddle[1].x = screen->w - 20 - 10;
  paddle[1].y = screen->h / 2 - 50;
  paddle[1].w = 10;
  paddle[1].h = 50;
}

/* This routine moves each ball by its motion vector. */
static void move_ball() {

  /* Move the ball by its motion vector. */
  ball.x += ball.dx;
  ball.y += ball.dy;

  /* Turn the ball around if it hits the edge of the screen. */
  if (ball.x < 0) {
    increment_score(1);
    init_game();
  }

  if (ball.x > screen->w - 10) {
    increment_score(0);
    init_game();
  }

  if (ball.y < 0 || ball.y > screen->h - 10) {
    ball.dy = -ball.dy;
  }

  // check for collision with the paddle
  for (int i = 0; i < 2; i++) {

    // collision detected
    if (hasCollision(ball, paddle[i])) {

      // ball moving left
      if (ball.dx < 0) {

        ball.dx -= 1;

        // ball moving right
      } else {

        ball.dx += 1;
      }

      // change ball direction
      ball.dx = -ball.dx;

      // change ball angle based on where on the paddle it hit
      int hit_pos = (paddle[i].y + paddle[i].h) - ball.y;

      if (hit_pos >= 0 && hit_pos < 7) {
        ball.dy = 4;
      }

      if (hit_pos >= 7 && hit_pos < 14) {
        ball.dy = 3;
      }

      if (hit_pos >= 14 && hit_pos < 21) {
        ball.dy = 2;
      }

      if (hit_pos >= 21 && hit_pos < 28) {
        ball.dy = 1;
      }

      if (hit_pos >= 28 && hit_pos < 32) {
        ball.dy = 0;
      }

      if (hit_pos >= 32 && hit_pos < 39) {
        ball.dy = -1;
      }

      if (hit_pos >= 39 && hit_pos < 46) {
        ball.dy = -2;
      }

      if (hit_pos >= 46 && hit_pos < 53) {
        ball.dy = -3;
      }

      if (hit_pos >= 53 && hit_pos <= 60) {
        ball.dy = -4;
      }

      // ball moving right
      if (ball.dx > 0) {

        // teleport ball to avoid mutli collision glitch
        if (ball.x < 30) {

          ball.x = 30;
        }
        // ball moving left
      } else {

        // teleport ball to avoid mutli collision glitch
        if (ball.x > 600) {

          ball.x = 600;
        }
      }
    }
  }
}

static void draw_game_over(int p) {

  SDL_Rect p1;
  SDL_Rect p2;
  SDL_Rect cpu;
  SDL_Rect dest;

  p1.x = 0;
  p1.y = 0;
  p1.w = end->w;
  p1.h = 75;

  p2.x = 0;
  p2.y = 75;
  p2.w = end->w;
  p2.h = 75;

  cpu.x = 0;
  cpu.y = 150;
  cpu.w = end->w;
  cpu.h = 75;

  dest.x = (screen->w / 2) - (end->w / 2);
  dest.y = (screen->h / 2) - (75 / 2);
  dest.w = end->w;
  dest.h = 75;

  switch (p) {
  case 1:
    SDL_BlitSurface(end, &p1, screen, &dest);
    break;
  case 2:
    SDL_BlitSurface(end, &p2, screen, &dest);
    break;
  default:
    SDL_BlitSurface(end, &cpu, screen, &dest);
  }
}

static void draw_menu() {

  SDL_Rect src;
  SDL_Rect dest;

  src.x = 0;
  src.y = 0;
  src.w = title->w;
  src.h = title->h;

  dest.x = (screen->w / 2) - (src.w / 2);
  dest.y = (screen->h / 2) - (src.h / 2);
  dest.w = title->w;
  dest.h = title->h;

  SDL_BlitSurface(title, &src, screen, &dest);
}

static void draw_net() {

  SDL_Rect net;

  net.x = screen->w / 2;
  net.y = 20;
  net.w = 5;
  net.h = 15;

  // draw the net
  int i, r;

  for (i = 0; i < 15; i++) {

    r = SDL_FillRect(screen, &net, 0xffffffff);

    if (r != 0) {

      printf("fill rectangle failled in func draw_net()");
    }

    net.y = net.y + 30;
  }
}

static void draw_ball() {

  SDL_Rect src;

  src.x = ball.x;
  src.y = ball.y;
  src.w = ball.w;
  src.h = ball.h;

  if (SDL_FillRect(screen, &src, 0xffffffff) != 0) {
    printf("fill rectangle failled in func drawball()");
  }
}

static void draw_paddle() {

  SDL_Rect src;
  int i;

  for (i = 0; i < 2; i++) {

    src.x = paddle[i].x;
    src.y = paddle[i].y;
    src.w = paddle[i].w;
    src.h = paddle[i].h;

    if (SDL_FillRect(screen, &src, 0xffffffff) != 0) {
      printf("fill rectangle failled in func draw_paddle()");
    }
  }
}

static void draw_player_0_score() {

  SDL_Rect src;
  SDL_Rect dest;

  src.x = 0;
  src.y = 0;
  src.w = 64;
  src.h = 64;

  dest.x = (screen->w / 2) - src.w - 12; // 12 is just padding spacing
  dest.y = 0;
  dest.w = 64;
  dest.h = 64;

  if (getScore(0) > 0 && getScore(0) < 10) {
    src.x += src.w * getScore(0);
  }

  SDL_BlitSurface(numbermap, &src, screen, &dest);
}

static void draw_player_1_score() {

  SDL_Rect src;
  SDL_Rect dest;

  src.x = 0;
  src.y = 0;
  src.w = 64;
  src.h = 64;

  dest.x = (screen->w / 2) + 12;
  dest.y = 0;
  dest.w = 64;
  dest.h = 64;

  if (getScore(1) > 0 && getScore(1) < 10) {

    src.x += src.w * getScore(1);
  }

  SDL_BlitSurface(numbermap, &src, screen, &dest);
}

int main(int argc, char *args[]) {

  // SDL Window setup
  if (init(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args) == 1) {
    return 0;
  }

  SDL_GetWindowSize(window, &width, &height);

  int sleep = 0;
  int quit = 0;
  int state = 0;
  int r = 0;
  Uint32 next_game_tick = SDL_GetTicks();

  // Initialize the ball position data.
  init_game();

  // render loop
  while (quit == 0) {

    // check for new events every frame
    SDL_PumpEvents();

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_ESCAPE]) {
      quit = 1;
    }

    if (keystate[SDL_SCANCODE_DOWN]) {
      move_paddle(0);
    }

    if (keystate[SDL_SCANCODE_UP]) {
      move_paddle(1);
    }

    // draw background
    SDL_RenderClear(renderer);
    SDL_FillRect(screen, NULL, 0x000000ff);

    // display main menu
    if (state == 0) {

      if (keystate[SDL_SCANCODE_SPACE]) {
        state = 1;
      }

      // draw menu
      draw_menu();

      // display gameover
    } else if (state == 2) {

      if (keystate[SDL_SCANCODE_SPACE]) {
        state = 0;
        // delay for a little bit so the space bar press dosnt get triggered
        // twice while the main menu is showing
        SDL_Delay(500);
      }

      if (r == 1) {

        // if player 1 is AI if player 1 was human display the return value of r
        // not 3
        draw_game_over(3);

      } else {

        // display gameover
        draw_game_over(r);
      }

      // display the game
    } else if (state == 1) {

      // check score
      r = check_score();

      // if either player wins, change to game over state
      if (r == 1) {
        state = 2;

      } else if (r == 2) {
        state = 2;
      }

      // paddle ai movement
      move_paddle_ai();

      //* Move the balls for the next frame.
      move_ball();

      // draw net
      draw_net();

      // draw paddles
      draw_paddle();

      //* Put the ball on the screen.
      draw_ball();

      // draw the score
      draw_player_0_score();

      // draw the score
      draw_player_1_score();
    }

    SDL_UpdateTexture(screen_texture, NULL, screen->pixels,
                      screen->w * sizeof(Uint32));
    SDL_RenderCopy(renderer, screen_texture, NULL, NULL);

    // draw to the display
    SDL_RenderPresent(renderer);

    // time it takes to render  frame in milliseconds
    next_game_tick += 1000 / 60;
    sleep = next_game_tick - SDL_GetTicks();

    if (sleep >= 0) {
      SDL_Delay(sleep);
    }
  }

  SDL_Surface *ptr[] = {screen, title, numbermap, end, NULL};

  cleanUp(renderer, window, ptr);
  return 0;
}
