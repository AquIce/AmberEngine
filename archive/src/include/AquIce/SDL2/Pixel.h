#ifndef __AQUICE_SDL2_PIXEL_H__
#define __AQUICE_SDL2_PIXEL_H__

#include "../../SDL2/SDL.h"

/**
 * @brief Struct to represent a pixel
*/
typedef struct Pixel
{
	/**
	 * @brief Red color value
	*/
	int r;
	/**
	 * @brief Green color value
	*/
	int g;
	/**
	 * @brief Blue color value
	*/
	int b;
	/**
	 * @brief Alpha color value
	*/
	int a;
	/**
	 * @brief X position
	*/
	int x;
	/**
	 * @brief Y position
	*/
	int y;
} Pixel;

/**
 * @brief Set the pixel values 
 * @param pixel Pixel to set
 * @param r Red color value
 * @param g Green color value
 * @param b Blue color value
 * @param a Alpha color value
 * @param x X position
 * @param y Y position
*/
void set_pixel(Pixel* pixel, int r, int g, int b, int a, int x, int y) {
	pixel->r = r;
	pixel->g = g;
	pixel->b = b;
	pixel->a = a;
	pixel->x = x;
	pixel->y = y;
}

/**
 * @brief Set the pixel values 
 * @param pixel Pixel to set
 * @param r Red color value
 * @param g Green color value
 * @param b Blue color value
 * @param a Alpha color value
*/
void set_pixel(Pixel* pixel, int r, int g, int b, int a) {
	set_pixel(pixel, r, g, b, a, 255, 255);
}

/**
 * @brief Set the pixel values 
 * @param pixel Pixel to set
 * @param r Red color value
 * @param g Green color value
 * @param b Blue color value
 * @param x X position
 * @param y Y position
*/
void set_pixel(Pixel* pixel, int r, int g, int b, int x, int y) {
	set_pixel(pixel, r, g, b, 255, x, y);
}

/**
 * @brief Set the pixel values 
 * @param pixel Pixel to set
 * @param r Red color value
 * @param g Green color value
 * @param b Blue color value
*/
void set_pixel(Pixel* pixel, int r, int g, int b) {
	set_pixel(pixel, r, g, b, 255);
}

/**
 * @brief Create a new pixel
 * @param r Red color value
 * @param g Green color value
 * @param b Blue color value
 * @param a Alpha color value
 * @param x X position
 * @param y Y position
 * @return New pixel
*/
Pixel* Pixel_new(int r, int g, int b, int a, int x, int y) {
	Pixel* pixel = (Pixel*)malloc(sizeof(Pixel));
	set_pixel(pixel, r, g, b, a, x, y);
	return pixel;
}

/**
 * @brief Create a new pixel
 * @param r Red color value
 * @param g Green color value
 * @param b Blue color value
 * @param a Alpha color value
 * @return New pixel
*/
Pixel* Pixel_new(int r, int g, int b, int a) {
	Pixel* pixel = (Pixel*)malloc(sizeof(Pixel));
	set_pixel(pixel, r, g, b, a);
	return pixel;
}

/**
 * @brief Create a new pixel
 * @param r Red color value
 * @param g Green color value
 * @param b Blue color value
 * @param x X position
 * @param y Y position
 * @return New pixel
*/
Pixel* Pixel_new(int r, int g, int b, int x, int y) {
	Pixel* pixel = (Pixel*)malloc(sizeof(Pixel));
	set_pixel(pixel, r, g, b, x, y);
	return pixel;
}

/**
 * @brief Create a new pixel
 * @param r Red color value
 * @param g Green color value
 * @param b Blue color value
 * @return New pixel
*/
Pixel* Pixel_new(int r, int g, int b) {
	Pixel* pixel = (Pixel*)malloc(sizeof(Pixel));
	set_pixel(pixel, r, g, b);
	return pixel;
}

/**
 * @brief Destroy a pixel
 * @param pixel Pixel to destroy
*/
void DestroyPixel(Pixel* pixel) {
	free(pixel);
}

/**
 * @brief Draw a pixel
 * @param renderer Renderer to draw
 * @param pixel Pixel to draw
*/
void draw_pixel(SDL_Renderer* renderer, Pixel* pixel) {
	SDL_SetRenderDrawColor(renderer, pixel->r, pixel->g, pixel->b, pixel->a);
	SDL_RenderDrawPoint(renderer, pixel->x, pixel->y);
}

#endif