#ifndef __AQUICE_SDL3_SDL_HPP__
#define __AQUICE_SDL3_SDL_HPP__ 

#include <vector>
#include <variant>

#include "../SDL2/line.hpp"
#include "../utils/iround.h"

#define PI 3.14159265358979323846
#define P_ANGLE 30

typedef struct Cube {
	std::vector<coords> vertices;
	int r;
	int g;
	int b;
	int a;
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

void add_cube(SDL3_Config* config, coords front_down, int r, int g, int b, int a) {
	coords back_down = {
		front_down.x,
		front_down.y - config->oppsize * 2
	};
	coords left_down = {
		front_down.x + config->adjsize,
		front_down.y - config->oppsize
	};
	coords right_down = {
		front_down.x - config->adjsize,
		front_down.y - config->oppsize
	};
	coords front_up = {
		front_down.x,
		front_down.y - config->hypsize
	};
	coords back_up = {
		front_down.x,
		front_down.y - config->hypsize - config->oppsize * 2
	};
	coords left_up = {
		front_down.x + config->adjsize,
		front_down.y - config->hypsize - config->oppsize
	};
	coords right_up = {
		front_down.x - config->adjsize,
		front_down.y - config->hypsize - config->oppsize
	};
	config->objects.push_back(
		{
			std::vector<coords>({
				front_down,
				back_down,
				left_down,
				right_down,
				front_up,
				back_up,
				left_up,
				right_up
			}),
			r,
			g,
			b,
			a		}
	);
}

void draw_objects_vertices(SDL_Renderer* renderer, SDL3_Config* config) {
	for(auto cube : config->objects) {
		for(auto v : cube.vertices) {
			SDL_SetRenderDrawColor(renderer, cube.r, cube.g, cube.b, cube.a);
			SDL_RenderDrawPoint(renderer, v.x, v.y);
		}
	}
}

void draw_objects(SDL_Renderer* renderer, SDL3_Config* config) {
	for(auto cube : config->objects) {
		// TODO: Add notion of visible lines to avoid rendering all lines
		for(auto p : cube.vertices) {
			SDL_SetRenderDrawColor(renderer, cube.r, cube.g, cube.b, cube.a);
			SDL_RenderDrawPoint(renderer, p.x, p.y);
		}
	}
}

#endif