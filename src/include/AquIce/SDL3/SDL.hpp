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
 * @brief The vector from the scene to the camera (to calculate hidden mesh points)
*/
#define SCENE_TO_CAM_VEC std::vector<int>({-1, 1, 1})

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
 * @brief A struct to represent a 2D point
*/
typedef struct Cube {
	/**
	 * @brief The mesh of the cube
	*/
	std::vector<MeshLine> mesh;
	/**
	 * @brief The mesh points of the cube
	*/
	std::vector<MeshPoint*> mesh_points;
	/**
	 * @brief The position of the cube
	*/
	coords3 pos;
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
SDL3_Config SDL3_Config_new(coords origin, int size) {
	return {
		size,
		iround(size * dtrig(cos, 90 - P_ANGLE)),
		iround(size * dtrig(sin, 90 - P_ANGLE)),
		std::vector<Cube>(),
		origin
	};
}

/**
 * @brief Create a new mesh point pointer
 * @param point The point of the mesh point
 * @param visible Whether the point is visible
 * @return The mesh point pointer
*/
MeshPoint* MeshPoint_new_ptr(coords3 point, bool visible) {
	MeshPoint* mpoint = (MeshPoint*)malloc(sizeof(MeshPoint));
	mpoint->point = point;
	mpoint->visible = visible;
	return mpoint;
}
/**
 * @brief Create a new mesh point pointer
 * @param point The point of the mesh point
 * @return The mesh point pointer
*/
MeshPoint* MeshPoint_new_ptr(coords3 point) {
	return MeshPoint_new_ptr(point, true);
}

/**
 * @brief Create a new mesh point
 * @param point The point of the mesh point
 * @param visible Whether the point is visible
 * @return The mesh point
*/
MeshPoint MeshPoint_new(coords3 point, bool visible) {
	return {point, visible};
}
/**
 * @brief Create a new mesh point
 * @param point The point of the mesh point
 * @return The mesh point
*/
MeshPoint MeshPoint_new(coords3 point) {
	return MeshPoint_new(point, true);
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
	// z axis
	p2.y -= p.z * config->hypsize;
	// x axis
	p2.x += p.x * config->adjsize;
	p2.y -= p.x * config->oppsize;
	// y axis
	p2.x += p.y * config->adjsize;
	p2.y += p.y * config->oppsize;

	return p2;
}

/**
 * @brief Get all the mesh points of the objects in the SDL3 configuration
 * @param config The SDL3 configuration
 * @return The mesh points of the objects in the SDL3 configuration
*/
std::vector<MeshPoint*> get_objects_mesh_points(SDL3_Config* config) {
	std::vector<MeshPoint*> mesh_points = std::vector<MeshPoint*>();
	for(auto cube : config->objects) {
		std::vector<MeshPoint*> cube_mesh_points = cube.mesh_points;
		mesh_points.insert(mesh_points.end(), cube_mesh_points.begin(), cube_mesh_points.end());
	}
	return mesh_points;
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
			double vmultiple = vector_multiplicity(visible_mesh_points[j].back()->point, mesh_points[i]->point, &is_multiple);
			if(is_multiple) {
				has_multiple = true;
				if(vmultiple < 0) {
					mesh_points[i]->visible = false;
				} else if(vmultiple == 0) {
					mesh_points[i]->visible = true;
					visible_mesh_points[j].push_back(mesh_points[i]);
				} else {
					mesh_points[i]->visible = true;
					for(auto point : visible_mesh_points[j]) {
						point->visible = false;
					}
					visible_mesh_points[j] = std::vector<MeshPoint*>({mesh_points[i]});
				}
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
	set_mesh_points_visibility(get_objects_mesh_points(config));
}

/**
 * @brief Add a cube to the SDL3 configuration
 * @param config The SDL3 configuration
 * @param position The position of the cube
 * @param r The red color of the cube
 * @param g The green color of the cube
 * @param b The blue color of the cube
 * @param a The alpha color of the cube
 * @param run_visibility Whether to run the visibility algorithm
*/
void add_cube(SDL3_Config* config, coords3 position, int r, int g, int b, int a, bool run_visibility = true) {
	MeshPoint* front_down = MeshPoint_new_ptr(position);
	MeshPoint* back_down = MeshPoint_new_ptr({position.x + 1, position.y - 1, position.z});
	MeshPoint* left_down = MeshPoint_new_ptr({position.x, position.y - 1, position.z});
	MeshPoint* right_down = MeshPoint_new_ptr({position.x + 1, position.y, position.z});
	MeshPoint* front_up = MeshPoint_new_ptr({position.x, position.y, position.z + 1});
	MeshPoint* back_up = MeshPoint_new_ptr({position.x + 1, position.y - 1, position.z + 1});
	MeshPoint* left_up = MeshPoint_new_ptr({position.x, position.y - 1, position.z + 1});
	MeshPoint* right_up = MeshPoint_new_ptr({position.x + 1, position.y, position.z + 1});

	config->objects.push_back(
		{
			std::vector<MeshLine>({
				MeshLine_new(front_down, right_down),
				MeshLine_new(front_down, left_down),
				MeshLine_new(back_down, right_down),
				MeshLine_new(back_down, left_down),

				MeshLine_new(front_down, front_up),
				MeshLine_new(back_down, back_up),
				MeshLine_new(right_down, right_up),
				MeshLine_new(left_down, left_up),

				MeshLine_new(front_up, right_up),
				MeshLine_new(front_up, left_up),
				MeshLine_new(back_up, right_up),
				MeshLine_new(back_up, left_up),
			}),
			std::vector<MeshPoint*>({
				front_down,
				back_down,
				left_down,
				right_down,
				front_up,
				back_up,
				left_up,
				right_up
			}),
			position,
			r,
			g,
			b,
			a
		}
	);

	if(run_visibility) {
		set_mesh_points_visibility(config);
	}
}

/**
 * @brief Add cubes to the SDL3 configuration
 * @param config The SDL3 configuration
 * @param positions The positions of the cubes
 * @param r The red color of the cubes
 * @param g The green color of the cubes
 * @param b The blue color of the cubes
 * @param a The alpha color of the cubes
 * @note This function is a wrapper for the add_cube function but adds a layer of optimization by running the visibility algorithm only once.
*/
void add_cubes(SDL3_Config* config, std::vector<coords3> positions, int r, int g, int b, int a) {
	for(auto position : positions) {
		add_cube(config, position, r, g, b, a, false);
	}
	set_mesh_points_visibility(config);
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

/**
 * @brief Draw the lines of the cubes
 * @param renderer The SDL renderer
 * @param config The SDL3 configuration
*/
void draw_objects(SDL_Renderer* renderer, SDL3_Config* config) {
	for(auto cube : config->objects) {
		for(auto mesh_line : cube.mesh) {
			draw_mesh_line(renderer, config, mesh_line);
		}
	}
}

#endif