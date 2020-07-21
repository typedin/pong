#include <SDL2/SDL.h>
#include <stdio.h>
#include "main.h"
#include "stdint.h"

int TITLE_COLOR[] = { 255, 0, 255 };

extern SDL_Window* window;	//The window we'll be rendering to
extern SDL_Renderer *renderer;	//The renderer SDL will use to draw to the screen
extern SDL_Surface *screen;
extern SDL_Texture *screen_texture;
extern SDL_Surface *title;
extern SDL_Surface *numbermap;
extern SDL_Surface *end;

void initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
	}
}

void createWindowAndRenderer(int argc, char *args[]){
    uint32_t window_flag;

    for (int i = 0; i < argc; i++) {
        if(strcmp(args[i], "-f")) {
            window_flag = SDL_WINDOW_SHOWN;
        } else {
            window_flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
    }

    if (window_flag <= 0) {
        printf("Wrong flag was passed! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_CreateWindowAndRenderer(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        window_flag,
        &window,
        &renderer
    );

	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
	}
}

SDL_Surface* createScreenSurface(int width, int height) {
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);

    if (surface == NULL) {
        printf("Could not create the surface! SDL_Error: %s\n", SDL_GetError());
       exit(0);
    }

    return surface;
}

SDL_Texture* createTextureFromSurface(SDL_Renderer *renderer, SDL_Surface *surface){

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL) {
		printf("Could not create the texture! SDL_Error: %s\n", SDL_GetError());
        exit(1);
	}

    return texture;
}

SDL_Surface* loadBMP(char *path) {
	SDL_Surface *surface = SDL_LoadBMP(path);

	if (surface == NULL) {
		printf("Could not load file at path: %s!\n SDL_Error: %s\n", path, SDL_GetError());
        exit(1);
	}

    return surface;
}

void setTitleColor(int RGB[]) {
    Uint32 colorkey = SDL_MapRGB(title->format, RGB[0], RGB[1], RGB[2]);

    if(SDL_SetColorKey(title, SDL_TRUE, colorkey) != 0) {
		printf("Could not set color key for title!\n SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if(SDL_SetColorKey(numbermap, SDL_TRUE, colorkey) != 0) {
		printf("Could not set color key for numbermap!\n SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
}

int init(int width, int height, int argc, char *args[]) {

    initSDL();

    createWindowAndRenderer(argc, args);

    screen = createScreenSurface(width, height);

    screen_texture = createTextureFromSurface(renderer, screen);

	end = loadBMP("gameover.bmp");
	numbermap = loadBMP("numbermap.bmp");
    title = loadBMP("title.bmp");

    setTitleColor(TITLE_COLOR);

	return 0;
}
