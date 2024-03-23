#ifndef __AQUICE_SDL2_PIXEL_H__
#define __AQUICE_SDL2_PIXEL_H__

#include "../../SDL2/SDL.h"

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

Pixel* Pixel_new(int r, int g, int b, int a, int x, int y) {
	Pixel* pixel = (Pixel*)malloc(sizeof(Pixel));
	set_pixel(pixel, r, g, b, a, x, y);
	return pixel;
}

Pixel* Pixel_new(int r, int g, int b, int a) {
	Pixel* pixel = (Pixel*)malloc(sizeof(Pixel));
	set_pixel(pixel, r, g, b, a);
	return pixel;
}

Pixel* Pixel_new(int r, int g, int b, int x, int y) {
	Pixel* pixel = (Pixel*)malloc(sizeof(Pixel));
	set_pixel(pixel, r, g, b, x, y);
	return pixel;
}

Pixel* Pixel_new(int r, int g, int b) {
	Pixel* pixel = (Pixel*)malloc(sizeof(Pixel));
	set_pixel(pixel, r, g, b);
	return pixel;
}

void DestroyPixel(Pixel* pixel) {
	free(pixel);
}

void draw_pixel(SDL_Renderer* renderer, Pixel* pixel) {
	SDL_SetRenderDrawColor(renderer, pixel->r, pixel->g, pixel->b, pixel->a);
	SDL_RenderDrawPoint(renderer, pixel->x, pixel->y);
}

#endif