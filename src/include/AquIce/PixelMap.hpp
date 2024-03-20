#ifndef __AQUICE_PIXELMAP_H__
#define __AQUICE_PIXELMAP_H__

#include "Pixel.h"
#include <vector>

typedef struct PixelMap
{
	std::vector<Pixel> pixels;
	int start_x;
	int start_y;
} PixelRenderer;

void set_pixel_map(PixelMap* pixel_map, int start_x, int start_y, std::vector<Pixel> pixels) {
	pixel_map->start_x = start_x;
	pixel_map->start_y = start_y;
	pixel_map->pixels = pixels;
}

void set_pixel_map(PixelMap* pixel_map, std::vector<Pixel> pixels) {
	pixel_map->start_x = 0;
	pixel_map->start_y = 0;
	pixel_map->pixels = pixels;
}

void draw_pixel_map(SDL_Renderer* renderer, PixelMap* pixel_map) {
	for(int i = 0; i < pixel_map->pixels.size(); i++) {
		pixel_map->pixels[i].x = pixel_map->start_x + i;
		pixel_map->pixels[i].y = pixel_map->start_y;
		draw_pixel(renderer, &pixel_map->pixels[i]);
	}
}

#endif