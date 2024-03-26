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
 * @brief A struct to represent a 2D point
*/
typedef struct Cube {
	/**
	 * @brief The vertices of the cube
	*/
	std::vector<coords> vertices;
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

typedef struct MeshPoint {
	coords3 point;
	bool visible;
} MeshPoint;

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
 * @brief Add a cube to the SDL3 configuration
 * @param config The SDL3 configuration
 * @param position The position of the cube
 * @param r The red color of the cube
 * @param g The green color of the cube
 * @param b The blue color of the cube
 * @param a The alpha color of the cube
*/
void add_cube(SDL3_Config* config, coords3 position, int r, int g, int b, int a) {
	coords front_down = get_2d_coords(position, config);
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
			position,
			r,
			g,
			b,
			a
		}
	);
}

MeshPoint MeshPoint_new(coords3 point, bool visible) {
	return {point, visible};
}

MeshPoint MeshPoint_new(coords3 point) {
	return MeshPoint_new(point, true);
}

/**
 * @brief Get the mesh points of a cube
 * @param cube The cube
 * @return The mesh points of the cube
*/
std::vector<MeshPoint> get_cube_mesh_points(Cube cube) {
	return {{
		MeshPoint_new(cube.pos),
		MeshPoint_new({cube.pos.x, cube.pos.y, cube.pos.z + 1}),
		MeshPoint_new({cube.pos.x, cube.pos.y - 1, cube.pos.z}),
		MeshPoint_new({cube.pos.x, cube.pos.y - 1, cube.pos.z + 1}),
		MeshPoint_new({cube.pos.x + 1, cube.pos.y, cube.pos.z}),
		MeshPoint_new({cube.pos.x + 1, cube.pos.y, cube.pos.z + 1}),
		MeshPoint_new({cube.pos.x + 1, cube.pos.y - 1, cube.pos.z}),
		MeshPoint_new({cube.pos.x + 1, cube.pos.y - 1, cube.pos.z + 1})
	}};
}

std::vector<MeshPoint> get_objects_mesh_points(SDL3_Config* config) {
	std::vector<MeshPoint> mesh_points = std::vector<MeshPoint>();
	for(auto cube : config->objects) {
		std::vector<MeshPoint> cube_mesh_points = get_cube_mesh_points(cube);
		mesh_points.insert(mesh_points.end(), cube_mesh_points.begin(), cube_mesh_points.end());
	}
	return mesh_points;
}

double vector_multiplicity(coords3 reference, coords3 comparee, bool* is_multiple) {
	double x = (double)(comparee.x - reference.x) / SCENE_TO_CAM_VEC[0];
	double y = (double)(comparee.y - reference.y) / SCENE_TO_CAM_VEC[1];
	double z = (double)(comparee.z - reference.z) / SCENE_TO_CAM_VEC[2];
	*is_multiple = x == y && y == z;
	return x;
}

void define_mesh_points_visibility(std::vector<MeshPoint> mesh_points) {
	std::vector<MeshPoint> mesh_points_sorted = std::vector<MeshPoint>();
	mesh_points_sorted.push_back({mesh_points[0]});
	for(auto mpoint : mesh_points) {
		bool is_inserted = false;
		for(int i = 0; i < mesh_points_sorted.size(); i++) {
			MeshPoint ref_mpoint = mesh_points_sorted[i];
			bool is_multiple;
			double vmultiple = vector_multiplicity(ref_mpoint.point, mpoint.point, &is_multiple);
			if(is_multiple) {
				if(vector_multiplicity(ref_mpoint.point, mpoint.point, &is_multiple) < 0) {
					mpoint.visible = false;
				} else {
					mpoint.visible = true;
					ref_mpoint.visible = false;
					mesh_points_sorted[i] = mpoint;
				}

			}
		}
		if(!is_inserted) {
			mesh_points_sorted.push_back(mpoint);
		}
	}
	for(auto mpoints : mesh_points_sorted) {
		std::cout << mpoints.point.x << ", " << mpoints.point.y << ", " << mpoints.point.z << " - " << mpoints.visible << std::endl;
	}
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
		std::vector<line> lines = {
			{cube.vertices[0], cube.vertices[2]},
			{cube.vertices[0], cube.vertices[3]},
			{cube.vertices[1], cube.vertices[2]},
			{cube.vertices[1], cube.vertices[3]},

			{cube.vertices[0], cube.vertices[4]},
			{cube.vertices[1], cube.vertices[5]},
			{cube.vertices[2], cube.vertices[6]},
			{cube.vertices[3], cube.vertices[7]},

			{cube.vertices[4], cube.vertices[6]},
			{cube.vertices[4], cube.vertices[7]},
			{cube.vertices[5], cube.vertices[6]},
			{cube.vertices[5], cube.vertices[7]},
			
		};
		for(auto line : lines) {
			draw_line(renderer, line.start, line.end);
		}
	}
}

#endif