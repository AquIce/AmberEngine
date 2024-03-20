#ifndef __AQUICE_PIXEL_H__
#define __AQUICE_PIXEL_H__

#include "../SDL2/SDL.h"

typedef struct Pixel
{
	int r;
	int g;
	int b;
	int a;
	int x;
	int y;
} Pixel;

void set_pixel(Pixel* pixel, int r, int g, int b, int a, int x, int y) {
	pixel->r = r;
	pixel->g = g;
	pixel->b = b;
	pixel->a = a;
	pixel->x = x;
	pixel->y = y;
}

void set_pixel(Pixel* pixel, int r, int g, int b, int a) {
	pixel->r = r;
	pixel->g = g;
	pixel->b = b;
	pixel->a = a;
	pixel->x = 0;
	pixel->y = 0;
}

void set_pixel(Pixel* pixel, int r, int g, int b, int x, int y) {
	pixel->r = r;
	pixel->g = g;
	pixel->b = b;
	pixel->a = 255;
	pixel->x = x;
	pixel->y = y;
}

void set_pixel(Pixel* pixel, int r, int g, int b) {
	pixel->r = r;
	pixel->g = g;
	pixel->b = b;
	pixel->a = 255;
	pixel->x = 0;
	pixel->y = 0;
}

void draw_pixel(SDL_Renderer* renderer, Pixel* pixel) {
	SDL_SetRenderDrawColor(renderer, pixel->r, pixel->g, pixel->b, pixel->a);
	SDL_RenderDrawPoint(renderer, pixel->x, pixel->y);
}

#endif