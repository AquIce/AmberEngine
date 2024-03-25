#ifndef __AQUICE_SDL3_SDL_HPP__
#define __AQUICE_SDL3_SDL_HPP__ 

#include <vector>
#include <variant>

#include "../SDL2/line.hpp"
#include "../utils/iround.h"

#define PI 3.14159265358979323846
#define P_ANGLE 30

typedef struct Cube {
	std::vector<line> lines;
	int r;
	int g;
	int b;
	int a;
	coords base_coords;
} Cube;

typedef struct SDL3_Config {
	int hypsize;
	int oppsize;
	int adjsize;
	std::vector<Cube> objects;
} SDL3_Config;

double radToDeg(double radangle) {
	return radangle * PI / 180;
}

double dtrig(double (*trig_fn)(double), double radangle) {
	return trig_fn(radToDeg(radangle));
}

SDL3_Config SDL3_Config_new(int size) {
	return {
		size,
		iround(size * dtrig(cos, 90 - P_ANGLE)),
		iround(size * dtrig(sin, 90 - P_ANGLE))
	};
}

void add_cube(SDL3_Config* config, coords base_coords, int r, int g, int b, int a) {
	coords center_middle = {
		base_coords.x,
		base_coords.y - config->hypsize
	};
	coords top_middle = {
		base_coords.x,
		base_coords.y - config->hypsize - config->oppsize * 2
	};
	coords top_left = {
		base_coords.x + config->adjsize,
		base_coords.y - config->hypsize - config->oppsize
	};
	coords top_right = {
		base_coords.x - config->adjsize,
		base_coords.y - config->hypsize - config->oppsize
	};
	coords bottom_left = {
		base_coords.x + config->adjsize,
		base_coords.y - config->oppsize
	};
	coords bottom_right = {
		base_coords.x - config->adjsize,
		base_coords.y - config->oppsize
	};
	config->objects.push_back(
		{
			std::vector<line>({
				linegen(base_coords, center_middle),
				linegen(base_coords, bottom_left),
				linegen(base_coords, bottom_right),
				linegen(bottom_left, top_left),
				linegen(bottom_right, top_right),
				linegen(center_middle, top_left),
				linegen(center_middle, top_right),
				linegen(top_left, top_middle),
				linegen(top_right, top_middle)
			}),
			r,
			g,
			b,
			a,
			base_coords
		}
	);
}

void draw_objects(SDL_Renderer* renderer, SDL3_Config* config) {
	for(auto cube : config->objects) {
		for (auto ln : cube.lines) {
			draw_line(renderer, ln.start, ln.end, cube.r, cube.g, cube.b, cube.a);
		}
	}
}

#endif