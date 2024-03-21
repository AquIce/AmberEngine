#ifndef __AQUICE_PIXELMAP_H__
#define __AQUICE_PIXELMAP_H__

#include "Pixel.h"
#include <vector>

typedef struct PixelMap
{
	std::vector<Pixel*>* pixels;
	int start_x;
	int start_y;
} PixelRenderer;

void set_pixel_map(PixelMap* pixel_map, int start_x, int start_y, std::vector<Pixel*>* pixels) {
	pixel_map->start_x = start_x;
	pixel_map->start_y = start_y;
	pixel_map->pixels = pixels;
}

void set_pixel_map(PixelMap* pixel_map, int start_x, int start_y, Pixel* pixel, int length) {
	pixel_map->start_x = start_x;
	pixel_map->start_y = start_y;
	pixel_map->pixels = new std::vector<Pixel*>();
	for(int i = 0; i < length; i++) {
		pixel_map->pixels->push_back(pixel);
	}
}

void set_pixel_map(PixelMap* pixel_map, std::vector<Pixel*>* pixels) {
	pixel_map->start_x = 0;
	pixel_map->start_y = 0;
	pixel_map->pixels = pixels;
}

void set_pixel_map(PixelMap* pixel_map, Pixel* pixel, int length) {
	pixel_map->start_x = 0;
	pixel_map->start_y = 0;
	pixel_map->pixels = new std::vector<Pixel*>();
	for(int i = 0; i < length; i++) {
		pixel_map->pixels->push_back(pixel);
	}
}

PixelMap* PixelMap_new(std::vector<Pixel*>* pixels, int start_x, int start_y) {
	PixelMap* pixel_map = (PixelMap*)malloc(sizeof(PixelMap));
	set_pixel_map(pixel_map, start_x, start_y, pixels);
	return pixel_map;
}

PixelMap* PixelMap_new(Pixel* pixel, int length, int start_x, int start_y) {
	PixelMap* pixel_map = (PixelMap*)malloc(sizeof(PixelMap));
	set_pixel_map(pixel_map, start_x, start_y, pixel, length);
	return pixel_map;
}

PixelMap* PixelMap_new(std::vector<Pixel*>* pixels) {
	PixelMap* pixel_map = (PixelMap*)malloc(sizeof(PixelMap));
	set_pixel_map(pixel_map, pixels);
	return pixel_map;
}

PixelMap* PixelMap_new(Pixel* pixel, int length) {
	PixelMap* pixel_map = (PixelMap*)malloc(sizeof(PixelMap));
	set_pixel_map(pixel_map, pixel, length);
	return pixel_map;
}

void DestroyPixelMap(PixelMap* pixel_map) {
	for(int i = 0; i < pixel_map->pixels->size(); i++) {
		DestroyPixel((*pixel_map->pixels)[i]);
	}
	free(pixel_map);
}

void draw_pixel_map(SDL_Renderer* renderer, PixelMap* pixel_map) {
	for(int i = 0; i < pixel_map->pixels->size(); i++) {
		(*pixel_map->pixels)[i]->x = pixel_map->start_x + i;
		(*pixel_map->pixels)[i]->y = pixel_map->start_y;
		draw_pixel(renderer, (*pixel_map->pixels)[i]);
	}
}

#endif