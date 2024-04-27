#ifndef __AQUICE_SDL2_LINE_HPP__
#define __AQUICE_SDL2_LINE_HPP__

#include "../../SDL2/SDL.h"
#include "../utils/linegen.hpp"
#include "../utils/ColorCodes.h"

/**
 * @brief Draw a line
 * @param renderer The renderer
 * @param l The line
 * @param rgbas The vector of RGBA values
 * @note The size of the vector should be equal to the number of points in the line
*/
void draw_line(SDL_Renderer* renderer, line l, std::vector<RGBA> rgbas) {
	for(int i = 0; i < l.line_vec.size(); i++) {
		SDL_SetRenderDrawColor(renderer, rgbas[i].r, rgbas[i].g, rgbas[i].b, rgbas[i].a);
		SDL_RenderDrawPoint(renderer, l.line_vec[i].x, l.line_vec[i].y);
	}
}

/**
 * @brief Draw a line
 * @param renderer The renderer
 * @param from The starting point
 * @param to The ending point
 * @param rgbas The vector of RGBA values
 * @note The size of the vector should be equal to the number of points in the line
*/
void draw_line(SDL_Renderer* renderer, coords from, coords to, std::vector<RGBA> rgbas) {
	draw_line(renderer, linegen(from, to), rgbas);
}

/**
 * @brief Draw a line
 * @param renderer The renderer
 * @param from The starting point
 * @param to The ending point
 * @param r The red value
 * @param g The green value
 * @param b The blue value
 * @param a The alpha value
*/
void draw_line(SDL_Renderer* renderer, coords from, coords to, RGBA rgba) {
	draw_line(renderer, from, to, std::vector<RGBA>(linegen(from, to).line_vec.size(), rgba));
}
/**
 * @brief Draw a line
 * @param renderer The renderer
 * @param from The starting point
 * @param to The ending point
 * @param r The red value
 * @param g The green value
 * @param b The blue value
*/
void draw_line(SDL_Renderer* renderer, coords from, coords to, RGB rgb) {
	draw_line(renderer, from, to, {rgb.r, rgb.g, rgb.b, 255});
}
/**
 * @brief Draw a line
 * @param renderer The renderer
 * @param from The starting point
 * @param to The ending point
*/
void draw_line(SDL_Renderer* renderer, coords from, coords to) {
	draw_line(renderer, from, to, RGB{0, 0, 0});
}

#endif