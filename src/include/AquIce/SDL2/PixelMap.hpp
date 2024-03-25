#ifndef __AQUICE_SDL2_PIXELMAP_HPP__
#define __AQUICE_SDL2_PIXELMAP_HPP__

#include "Pixel.h"
#include <vector>

/**
 * @brief A struct to represent a pixel map
*/
typedef struct PixelMap
{
	/**
	 * @brief The pixels of the pixel map
	*/
	std::vector<Pixel*>* pixels;
	/**
	 * @brief The starting x position of the pixel map
	*/
	int start_x;
	/**
	 * @brief The starting y position of the pixel map
	*/
	int start_y;
} PixelRenderer;

/**
 * @brief Set the pixel map
 * @param pixel_map The pixel map
 * @param start_x The starting x position of the pixel map
 * @param start_y The starting y position of the pixel map
 * @param pixels The pixels of the pixel map
*/
void set_pixel_map(PixelMap* pixel_map, int start_x, int start_y, std::vector<Pixel*>* pixels) {
	pixel_map->start_x = start_x;
	pixel_map->start_y = start_y;
	pixel_map->pixels = pixels;
}

/**
 * @brief Set the pixel map
 * @param pixel_map The pixel map
 * @param start_x The starting x position of the pixel map
 * @param start_y The starting y position of the pixel map
 * @param pixel The pixel of the pixel map
 * @param length The length of the pixel map
*/
void set_pixel_map(PixelMap* pixel_map, int start_x, int start_y, Pixel* pixel, int length) {
	pixel_map->start_x = start_x;
	pixel_map->start_y = start_y;
	pixel_map->pixels = new std::vector<Pixel*>();
	for(int i = 0; i < length; i++) {
		pixel_map->pixels->push_back(pixel);
	}
}

/**
 * @brief Set the pixel map
 * @param pixel_map The pixel map
 * @param pixels The pixels of the pixel map
*/
void set_pixel_map(PixelMap* pixel_map, std::vector<Pixel*>* pixels) {
	pixel_map->start_x = 0;
	pixel_map->start_y = 0;
	pixel_map->pixels = pixels;
}

/**
 * @brief Set the pixel map
 * @param pixel_map The pixel map
 * @param pixel The pixel of the pixel map
 * @param length The length of the pixel map
*/
void set_pixel_map(PixelMap* pixel_map, Pixel* pixel, int length) {
	pixel_map->start_x = 0;
	pixel_map->start_y = 0;
	pixel_map->pixels = new std::vector<Pixel*>();
	for(int i = 0; i < length; i++) {
		pixel_map->pixels->push_back(pixel);
	}
}

/**
 * @brief Create a new pixel map
 * @param pixels The pixels of the pixel map
 * @param start_x The starting x position of the pixel map
 * @param start_y The starting y position of the pixel map
 * @return The new pixel map
*/
PixelMap* PixelMap_new(std::vector<Pixel*>* pixels, int start_x, int start_y) {
	PixelMap* pixel_map = (PixelMap*)malloc(sizeof(PixelMap));
	set_pixel_map(pixel_map, start_x, start_y, pixels);
	return pixel_map;
}

/**
 * @brief Create a new pixel map
 * @param pixel The pixel of the pixel map
 * @param length The length of the pixel map
 * @param start_x The starting x position of the pixel map
 * @param start_y The starting y position of the pixel map
 * @return The new pixel map
*/
PixelMap* PixelMap_new(Pixel* pixel, int length, int start_x, int start_y) {
	PixelMap* pixel_map = (PixelMap*)malloc(sizeof(PixelMap));
	set_pixel_map(pixel_map, start_x, start_y, pixel, length);
	return pixel_map;
}

/**
 * @brief Create a new pixel map
 * @param pixels The pixels of the pixel map
 * @return The new pixel map
*/
PixelMap* PixelMap_new(std::vector<Pixel*>* pixels) {
	PixelMap* pixel_map = (PixelMap*)malloc(sizeof(PixelMap));
	set_pixel_map(pixel_map, pixels);
	return pixel_map;
}

/**
 * @brief Create a new pixel map
 * @param pixel The pixel of the pixel map
 * @param length The length of the pixel map
 * @return The new pixel map
*/
PixelMap* PixelMap_new(Pixel* pixel, int length) {
	PixelMap* pixel_map = (PixelMap*)malloc(sizeof(PixelMap));
	set_pixel_map(pixel_map, pixel, length);
	return pixel_map;
}

/**
 * @brief Destroy a pixel map
 * @param pixel_map The pixel map to destroy
*/
void DestroyPixelMap(PixelMap* pixel_map) {
	for(int i = 0; i < pixel_map->pixels->size(); i++) {
		DestroyPixel((*pixel_map->pixels)[i]);
	}
	free(pixel_map);
}

/**
 * @brief Draw a pixel map
 * @param renderer The renderer to draw the pixel map on
 * @param pixel_map The pixel map to draw
*/
void draw_pixel_map(SDL_Renderer* renderer, PixelMap* pixel_map) {
	for(int i = 0; i < pixel_map->pixels->size(); i++) {
		(*pixel_map->pixels)[i]->x = pixel_map->start_x + i;
		(*pixel_map->pixels)[i]->y = pixel_map->start_y;
		draw_pixel(renderer, (*pixel_map->pixels)[i]);
	}
}

#endif