#ifndef __AQUICE_PIXELMAP2D_H__
#define __AQUICE_PIXELMAP2D_H__

#include "PixelMap.hpp"

typedef struct PixelMap2d
{
	std::vector<PixelMap> pixel_maps;
	int start_x;
	int start_y;
} PixelMap2d;

void set_pixel_map_2d(PixelMap2d* pixel_map_2d, int start_x, int start_y, std::vector<PixelMap> pixel_maps) {
	pixel_map_2d->start_x = start_x;
	pixel_map_2d->start_y = start_y;
	pixel_map_2d->pixel_maps = pixel_maps;
}

void set_pixel_map_2d(PixelMap2d* pixel_map_2d, std::vector<PixelMap> pixel_maps) {
	pixel_map_2d->start_x = 0;
	pixel_map_2d->start_y = 0;
	pixel_map_2d->pixel_maps = pixel_maps;
}

void draw_pixel_map_2d(SDL_Renderer* renderer, PixelMap2d* pixel_map_2d) {
	for(int i = 0; i < pixel_map_2d->pixel_maps.size(); i++) {
		pixel_map_2d->pixel_maps[i].start_x = pixel_map_2d->start_x;
		pixel_map_2d->pixel_maps[i].start_y = pixel_map_2d->start_y + i;
		draw_pixel_map(renderer, &pixel_map_2d->pixel_maps[i]);
	}
}

#endif