#ifndef __AQUICE_SDL2_LINE_HPP__
#define __AQUICE_SDL2_LINE_HPP__

#include "../../SDL2/SDL.h"
#include "../utils/linegen.hpp"

void draw_line(SDL_Renderer* renderer, coords from, coords to, int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	for(auto dot : linegen(from, to).line_vec) {
		SDL_RenderDrawPoint(renderer, dot.x, dot.y);
	}
}
void draw_line(SDL_Renderer* renderer, coords from, coords to, int r, int g, int b) {
	draw_line(renderer, from, to, r, g, b, 255);
}
void draw_line(SDL_Renderer* renderer, coords from, coords to) {
	draw_line(renderer, from, to, 0, 0, 0, 255);
}

#endif