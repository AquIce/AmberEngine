#ifndef __AQUICE_SDL2_PIXELMAP2D_HPP__
#define __AQUICE_SDL2_PIXELMAP2D_HPP__

#include "PixelMap.hpp"

/**
 * @brief A struct to represent a 2D pixel map
*/
typedef struct PixelMap2d
{
	/**
	 * @brief The pixel maps of the 2D pixel map
	*/
	std::vector<PixelMap*>* pixel_maps;
	/**
	 * @brief The starting x position of the 2D pixel map
	*/
	int start_x;
	/**
	 * @brief The starting y position of the 2D pixel map
	*/
	int start_y;
} PixelMap2d;

/**
 * @brief Set the pixel map 2D
 * @param pixel_map_2d The 2D pixel map
 * @param start_x The starting x position of the 2D pixel map
 * @param start_y The starting y position of the 2D pixel map
 * @param pixel_maps The pixel maps of the 2D pixel map
*/
void set_pixel_map_2d(PixelMap2d* pixel_map_2d, int start_x, int start_y, std::vector<PixelMap*>* pixel_maps) {
	pixel_map_2d->start_x = start_x;
	pixel_map_2d->start_y = start_y;
	pixel_map_2d->pixel_maps = pixel_maps;
}

/**
 * @brief Set the pixel map 2D
 * @param pixel_map_2d The 2D pixel map
 * @param start_x The starting x position of the 2D pixel map
 * @param start_y The starting y position of the 2D pixel map
 * @param pixel_map The pixel map of the 2D pixel map
 * @param length The length of the pixel map
*/
void set_pixel_map_2d(PixelMap2d* pixel_map_2d, int start_x, int start_y, PixelMap* pixel_map, int length) {
	pixel_map_2d->start_x = start_x;
	pixel_map_2d->start_y = start_y;
	pixel_map_2d->pixel_maps = new std::vector<PixelMap*>();
	for(int i = 0; i < length; i++) {
		pixel_map_2d->pixel_maps->push_back(pixel_map);
	}
}

/**
 * @brief Set the pixel map 2D
 * @param pixel_map_2d The 2D pixel map
 * @param pixel_maps The pixel maps of the 2D pixel map
*/
void set_pixel_map_2d(PixelMap2d* pixel_map_2d, std::vector<PixelMap*>* pixel_maps) {
	pixel_map_2d->start_x = 0;
	pixel_map_2d->start_y = 0;
	pixel_map_2d->pixel_maps = pixel_maps;
}

/**
 * @brief Set the pixel map 2D
 * @param pixel_map_2d The 2D pixel map
 * @param pixel_map The pixel map of the 2D pixel map
 * @param length The length of the pixel map
*/
void set_pixel_map_2d(PixelMap2d* pixel_map_2d, PixelMap* pixel_map, int length) {
	pixel_map_2d->start_x = 0;
	pixel_map_2d->start_y = 0;
	pixel_map_2d->pixel_maps = new std::vector<PixelMap*>();
	for(int i = 0; i < length; i++) {
		pixel_map_2d->pixel_maps->push_back(pixel_map);
	}
}

/**
 * @brief Set the pixel map 2D
 * @param pixel_map_2d The 2D pixel map
 * @param start_x The starting x position of the 2D pixel map
 * @param start_y The starting y position of the 2D pixel map
*/
void set_pixel_map_2d(PixelMap2d* pixel_map_2d, int start_x, int start_y) {
	pixel_map_2d->start_x = start_x;
	pixel_map_2d->start_y = start_y;
}

/**
 * @brief Create a new 2D pixel map
 * @param pixel_maps The pixel maps of the 2D pixel map
 * @param start_x The starting x position of the 2D pixel map
 * @param start_y The starting y position of the 2D pixel map
 * @return The 2D pixel map
*/
PixelMap2d* PixelMap2d_new(std::vector<PixelMap*>* pixel_maps, int start_x, int start_y) {
	PixelMap2d* pixel_map_2d = (PixelMap2d*)malloc(sizeof(PixelMap2d));
	set_pixel_map_2d(pixel_map_2d, start_x, start_y, pixel_maps);
	return pixel_map_2d;
}

/**
 * @brief Create a new 2D pixel map
 * @param pixel_map The pixel map of the 2D pixel map
 * @param length The length of the pixel map
 * @param start_x The starting x position of the 2D pixel map
 * @param start_y The starting y position of the 2D pixel map
 * @return The 2D pixel map
*/
PixelMap2d* PixelMap2d_new(PixelMap* pixel_map, int length, int start_x, int start_y) {
	PixelMap2d* pixel_map_2d = (PixelMap2d*)malloc(sizeof(PixelMap2d));
	set_pixel_map_2d(pixel_map_2d, start_x, start_y, pixel_map, length);
	return pixel_map_2d;
}

/**
 * @brief Create a new 2D pixel map
 * @param pixel_maps The pixel maps of the 2D pixel map
 * @return The 2D pixel map
*/
PixelMap2d* PixelMap2d_new(std::vector<PixelMap*>* pixel_maps) {
	PixelMap2d* pixel_map_2d = (PixelMap2d*)malloc(sizeof(PixelMap2d));
	set_pixel_map_2d(pixel_map_2d, pixel_maps);
	return pixel_map_2d;
}

/**
 * @brief Create a new 2D pixel map
 * @param pixel_map The pixel map of the 2D pixel map
 * @param length The length of the pixel map
 * @return The 2D pixel map
*/
PixelMap2d* PixelMap2d_new(PixelMap* pixel_map, int length) {
	PixelMap2d* pixel_map_2d = (PixelMap2d*)malloc(sizeof(PixelMap2d));
	set_pixel_map_2d(pixel_map_2d, pixel_map, length);
	return pixel_map_2d;
}

/**
 * @brief Destroy a 2D pixel map
 * @param pixel_map_2d The 2D pixel map to destroy
*/
void DestroyPixelMap2d(PixelMap2d* pixel_map_2d) {
	for(int i = 0; i < pixel_map_2d->pixel_maps->size(); i++) {
		DestroyPixelMap((*pixel_map_2d->pixel_maps)[i]);
	}
	free(pixel_map_2d);
}

/**
 * @brief Draw a 2D pixel map
 * @param renderer The renderer to draw the 2D pixel map
 * @param pixel_map_2d The 2D pixel map to draw
*/
void draw_pixel_map_2d(SDL_Renderer* renderer, PixelMap2d* pixel_map_2d) {
	for(int i = 0; i < pixel_map_2d->pixel_maps->size(); i++) {
		(*pixel_map_2d->pixel_maps)[i]->start_x = pixel_map_2d->start_x;
		(*pixel_map_2d->pixel_maps)[i]->start_y = pixel_map_2d->start_y + i;
		draw_pixel_map(renderer, (*pixel_map_2d->pixel_maps)[i]);
	}
}

#endif