#ifndef __AQUICE_SDL3_SDL_HPP__
#define __AQUICE_SDL3_SDL_HPP__ 

#include <vector>
#include <array>
#include <algorithm>

#include "../SDL2/line.hpp"
#include "../utils/iround.h"
#include "../utils/ColorCodes.h"

/**
 * @brief The constant PI
*/
#define PI 3.14159265358979323846

/**
 * @brief A struct to represent a 3D point
*/
typedef struct coords3 {
	/**
	 * @brief The x coordinate
	*/
	int x;
	/**
	 * @brief The y coordinate
	*/
	int y;
	/**
	 * @brief The z coordinate
	*/
	int z;
} coords3;

/**
 * @brief A struct to represent a 3D mesh point
*/
typedef struct MeshPoint {
	/**
	 * @brief The point
	*/
	coords3 point;
	/**
	 * @brief Whether the point is visible
	*/
	bool visible;
	/**
	 * @brief Whether the point is see-through
	*/
	bool seethrough;
} MeshPoint;

/**
 * @brief A struct to represent a 3D mesh line
*/
typedef struct MeshLine {
	/**
	 * @brief The start point of the line
	*/
	MeshPoint* start;
	/**
	 * @brief The end point of the line
	*/
	MeshPoint* end;
} MeshLine;

/**
 * @brief The configuration for the SDL3 library
*/
typedef struct SDL3_Config {
	/**
	 * @brief The size cubes
	*/
	int ref_size;
	/**
	 * @brief The vector of the camera
	*/
	coords3 cam_vec;
	/**
	 * @brief The origin of the SDL3 configuration
	*/
	coords origin;
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
SDL3_Config SDL3_Config_new(coords origin, int size, coords3 cam_vec) {
	return  SDL3_Config{
		size,
		cam_vec,
		origin
	};
}

/**
 * @brief Create a new mesh point pointer
 * @param point The point of the mesh point
 * @param visible Whether the point is visible
 * @param seethrough Whether the point is see-through
 * @return The mesh point pointer
*/
MeshPoint* MeshPoint_new_ptr(coords3 point, bool visible = true, bool seethrough = false) {
	MeshPoint* mpoint = (MeshPoint*)malloc(sizeof(MeshPoint));
	mpoint->point = point;
	mpoint->visible = visible;
	mpoint->seethrough = seethrough;
	return mpoint;
}

/**
 * @brief Create a new mesh point
 * @param point The point of the mesh point
 * @param visible Whether the point is visible
 * @param seethrough Whether the point is see-through
 * @return The mesh point
*/
MeshPoint MeshPoint_new(coords3 point, bool visible = true, bool seethrough = false) {
	return {point, visible, seethrough};
}

/**
 * @brief Create a new mesh line
 * @param start The start point of the line
 * @param end The end point of the line
 * @return The mesh line
*/
MeshLine MeshLine_new(MeshPoint* start, MeshPoint* end) {
	return {start, end};
}

/**
 * @brief Get the 2D coordinates of a 3D point
 * @param p The 3D point
 * @param config The SDL3 configuration
 * @return The 2D coordinates of the 3D point
*/
coords get_2d_coords(coords3 p, SDL3_Config* config) {
	coords p2 = {
		config->origin.x,
		config->origin.y
	};
	
	// Make modifications to p2 to get the 2D coordinates of p

	return p2;
}

/**
 * @brief Draw a mesh line
 * @param renderer The SDL renderer
 * @param config The SDL3 configuration
 * @param line The mesh line to draw
 * @note The line is only drawn if both points are visible-
*/
void draw_mesh_line(SDL_Renderer* renderer, SDL3_Config* config, MeshLine line) {
	if(line.start->visible && line.end->visible) {
		draw_line(renderer, get_2d_coords(line.start->point, config), get_2d_coords(line.end->point, config));
	}
}

#endif