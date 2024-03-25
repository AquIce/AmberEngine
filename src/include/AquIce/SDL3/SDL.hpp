#ifndef __AQUICE_SDL3_SDL_HPP__
#define __AQUICE_SDL3_SDL_HPP__ 

#include <vector>
#include <variant>

#include "../SDL2/line.hpp"
#include "../utils/iround.h"

/**
 * @brief The constant PI
*/
#define PI 3.14159265358979323846
/**
 * @brief The angle for the perspective
*/
#define P_ANGLE 30

/**
 * @brief A struct to represent a 2D point
*/
typedef struct Cube {
	/**
	 * @brief The vertices of the cube
	*/
	std::vector<coords> vertices;
	/**
	 * @brief The red color of the cube
	*/
	int r;
	/**
	 * @brief The green color of the cube
	*/
	int g;
	/**
	 * @brief The blue color of the cube
	*/
	int b;
	/**
	 * @brief The alpha color of the cube
	*/
	int a;
} Cube;

/**
 * @brief The configuration for the SDL3 library
*/
typedef struct SDL3_Config {
	/**
	 * @brief The size of the cube's hypotenuse
	*/
	int hypsize;
	/**
	 * @brief The size of the cube's opposite side
	*/
	int oppsize;
	/**
	 * @brief The size of the cube's adjacent side
	*/
	int adjsize;
	/**
	 * @brief The objects to render
	*/
	std::vector<Cube> objects;
} SDL3_Config;

/**
 * @brief Convert degrees to radians
 * @param degangle The angle in degrees
 * @return The angle in radians
*/
double radToDeg(double radangle) {
	return radangle * PI / 180;
}

/**
 * @brief Return the result of the trigonometric function of an angle in degrees
 * @param trig_fn The trigonometric function to use
 * @param radangle The angle in radians
 * @return The result of the trigonometric function of the angle
*/
double dtrig(double (*trig_fn)(double), double radangle) {
	return trig_fn(radToDeg(radangle));
}

/**
 * @brief Create a new SDL3 configuration
 * @param size The size of the cube
 * @return The SDL3 configuration
*/
SDL3_Config SDL3_Config_new(int size) {
	return {
		size,
		iround(size * dtrig(cos, 90 - P_ANGLE)),
		iround(size * dtrig(sin, 90 - P_ANGLE))
	};
}

/**
 * @brief Add a cube to the SDL3 configuration
 * @param config The SDL3 configuration
 * @param front_down The front down point of the cube
 * @param r The red color of the cube
 * @param g The green color of the cube
 * @param b The blue color of the cube
 * @param a The alpha color of the cube
*/
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

/**
 * @brief Draw the vertices of the cubes
 * @param renderer The SDL renderer
 * @param config The SDL3 configuration
*/
void draw_objects_vertices(SDL_Renderer* renderer, SDL3_Config* config) {
	for(auto cube : config->objects) {
		for(auto v : cube.vertices) {
			SDL_SetRenderDrawColor(renderer, cube.r, cube.g, cube.b, cube.a);
			SDL_RenderDrawPoint(renderer, v.x, v.y);
		}
	}
}

/**
 * @brief Draw the lines of the cubes
 * @param renderer The SDL renderer
 * @param config The SDL3 configuration
*/
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