#ifndef __AQUICE_PIXELMAP2D_H__
#define __AQUICE_PIXELMAP2D_H__

#include "PixelMap.hpp"

typedef struct PixelMap2d
{
	std::vector<PixelMap*>* pixel_maps;
	int start_x;
	int start_y;
} PixelMap2d;

void set_pixel_map_2d(PixelMap2d* pixel_map_2d, int start_x, int start_y, std::vector<PixelMap*>* pixel_maps) {
	pixel_map_2d->start_x = start_x;
	pixel_map_2d->start_y = start_y;
	pixel_map_2d->pixel_maps = pixel_maps;
}

void set_pixel_map_2d(PixelMap2d* pixel_map_2d, int start_x, int start_y, PixelMap* pixel_map, int length) {
	pixel_map_2d->start_x = start_x;
	pixel_map_2d->start_y = start_y;
	pixel_map_2d->pixel_maps = new std::vector<PixelMap*>();
	for(int i = 0; i < length; i++) {
		pixel_map_2d->pixel_maps->push_back(pixel_map);
	}
}

void set_pixel_map_2d(PixelMap2d* pixel_map_2d, std::vector<PixelMap*>* pixel_maps) {
	pixel_map_2d->start_x = 0;
	pixel_map_2d->start_y = 0;
	pixel_map_2d->pixel_maps = pixel_maps;
}

void set_pixel_map_2d(PixelMap2d* pixel_map_2d, PixelMap* pixel_map, int length) {
	pixel_map_2d->start_x = 0;
	pixel_map_2d->start_y = 0;
	pixel_map_2d->pixel_maps = new std::vector<PixelMap*>();
	for(int i = 0; i < length; i++) {
		pixel_map_2d->pixel_maps->push_back(pixel_map);
	}
}

PixelMap2d* PixelMap2d_new(std::vector<PixelMap*>* pixel_maps, int start_x, int start_y) {
	PixelMap2d* pixel_map_2d = (PixelMap2d*)malloc(sizeof(PixelMap2d));
	set_pixel_map_2d(pixel_map_2d, start_x, start_y, pixel_maps);
	return pixel_map_2d;
}

PixelMap2d* PixelMap2d_new(PixelMap* pixel_map, int length, int start_x, int start_y) {
	PixelMap2d* pixel_map_2d = (PixelMap2d*)malloc(sizeof(PixelMap2d));
	set_pixel_map_2d(pixel_map_2d, start_x, start_y, pixel_map, length);
	return pixel_map_2d;
}

PixelMap2d* PixelMap2d_new(std::vector<PixelMap*>* pixel_maps) {
	PixelMap2d* pixel_map_2d = (PixelMap2d*)malloc(sizeof(PixelMap2d));
	set_pixel_map_2d(pixel_map_2d, pixel_maps);
	return pixel_map_2d;
}

PixelMap2d* PixelMap2d_new(PixelMap* pixel_map, int length) {
	PixelMap2d* pixel_map_2d = (PixelMap2d*)malloc(sizeof(PixelMap2d));
	set_pixel_map_2d(pixel_map_2d, pixel_map, length);
	return pixel_map_2d;
}

void DestroyPixelMap2d(PixelMap2d* pixel_map_2d) {
	for(int i = 0; i < pixel_map_2d->pixel_maps->size(); i++) {
		DestroyPixelMap((*pixel_map_2d->pixel_maps)[i]);
	}
	free(pixel_map_2d);
}

void draw_pixel_map_2d(SDL_Renderer* renderer, PixelMap2d* pixel_map_2d) {
	for(int i = 0; i < pixel_map_2d->pixel_maps->size(); i++) {
		(*pixel_map_2d->pixel_maps)[i]->start_x = pixel_map_2d->start_x;
		(*pixel_map_2d->pixel_maps)[i]->start_y = pixel_map_2d->start_y + i;
		draw_pixel_map(renderer, (*pixel_map_2d->pixel_maps)[i]);
	}
}

#endif