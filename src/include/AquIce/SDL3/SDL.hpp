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
 * @brief The angle for the perspective
*/
#define P_ANGLE 30
/**
 * @brief The vector from the scene to the camera (to calculate hidden mesh points)
*/
#define SCENE_TO_CAM_VEC std::array<int, 3>({-1, 1, 1})

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
 * @brief Get the multiplicity of a vector
 * @param reference The reference vector
 * @param comparee The vector to compare
 * @param is_multiple Whether the vectors are multiples
 * @return The multiplicity of the vector
 * @note multiplicity * SCENE_TO_CAM_VEC + reference = comparee
*/
double vector_multiplicity(coords3 reference, coords3 comparee, bool* is_multiple) {
	double x = (double)(comparee.x - reference.x) / SCENE_TO_CAM_VEC[0];
	double y = (double)(comparee.y - reference.y) / SCENE_TO_CAM_VEC[1];
	double z = (double)(comparee.z - reference.z) / SCENE_TO_CAM_VEC[2];
	*is_multiple = x == y && y == z;
	return x;
}

/**
 * @brief Get the closest non-see-through MeshPoint from a vector
 * @param mesh_points The vector of MeshPoints
 * @return The closest non-see-through MeshPoint
*/
MeshPoint* closest_non_seethrough(std::vector<MeshPoint*> mesh_points) {
	for(int i = mesh_points.size() - 1; i >= 0; i--) {
		if(!mesh_points[i]->seethrough) {
			return mesh_points[i];
		}
	}
	return nullptr;
}

/**
 * @brief Set the visibility of the mesh points
 * @param mesh_points The mesh points
 * @note The algorithm is based on the fact that you can use the vector_multiplicity function to determine if a point aligned with another in relation to the camera.
 * @note If the multiplicity is negative, the point is hidden by the other point.
 * @note If the multiplicity is zero, the point is visible and the other point is also visible (they are the same point).
 * @note If the multiplicity is positive, the point is visible and the other point is hidden.
*/
void set_mesh_points_visibility(std::vector<MeshPoint*> mesh_points) {
	std::vector<std::vector<MeshPoint*>> visible_mesh_points = std::vector<std::vector<MeshPoint*>>({
		std::vector<MeshPoint*>({mesh_points[0]})
	});
	for(int i = 1; i < mesh_points.size(); i++) {
		bool has_multiple = false;
		for(int j = 0; j < visible_mesh_points.size(); j++) {
			bool is_multiple;
			double vmultiple = vector_multiplicity(closest_non_seethrough(visible_mesh_points[j])->point, mesh_points[i]->point, &is_multiple);
			if(is_multiple) {
				has_multiple = true;
				if(vmultiple < 0) {
					mesh_points[i]->visible = false;
				} else if(vmultiple == 0) {
					mesh_points[i]->visible = true;
					visible_mesh_points[j].push_back(mesh_points[i]);
				} else {
					mesh_points[i]->visible = true;
					if(!mesh_points[i]->seethrough) {
							for(auto point : visible_mesh_points[j]) {
							point->visible = false;
							if(point == closest_non_seethrough(visible_mesh_points[j])) {
								break;
							}
						}
						visible_mesh_points[j] = std::vector<MeshPoint*>({mesh_points[i]});
					} else {
						visible_mesh_points[j].push_back(mesh_points[i]);
					}
				}
				break;
			}
		}
		if(!has_multiple) {
			visible_mesh_points.push_back(std::vector<MeshPoint*>({mesh_points[i]}));
		}
	}
}

/**
 * @brief Set the visibility of the mesh points in the SDL3 configuration
 * @param config The SDL3 configuration
*/
void set_mesh_points_visibility(SDL3_Config* config) {
	// Replace with the actual mesh points
	set_mesh_points_visibility(std::vector<MeshPoint*>());
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