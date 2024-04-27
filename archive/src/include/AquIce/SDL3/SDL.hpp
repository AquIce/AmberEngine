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
 * @brief A struct to represent a 2D texture
*/
typedef struct Texture {
	/**
	 * @brief The size of the texture
	*/
	coords size;
	/**
	 * @brief The pixels of the texture
	*/
	std::vector<std::vector<RGBA>> pixels;
} Texture;

/**
 * @brief A struct to represent a 2D point
*/
typedef struct Cube {
	/**
	 * @brief The mesh points of the cube
	 * @note The mesh points are in the following order:
	 * @note front_down [0]
	 * @note back_down [1]
	 * @note left_down [2]
	 * @note right_down [3]
	 * @note front_up [4]
	 * @note back_up [5]
	 * @note left_up [6]
	 * @note right_up [7]
	*/
	std::array<MeshPoint*, 8> mesh_points;
	/**
	 * @brief The textures of the cube
	 * @note The textures are in the following order:
	 * @note top [0]
	 * @note bottom [1]
	 * @note front_left [2]
	 * @note front_right [3]
	 * @note back_left [4]
	 * @note back_right [5]
	*/
	std::array<Texture*, 6> textures;
	/**
	 * @brief The position of the cube
	*/
	coords3 pos;
	/**
	 * @brief The RGBA color of the cube
	*/
	RGBA rgba;
	/**
	 * @brief Whether the cube is see-through
	*/
	bool is_seethrough;
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
 * @brief Get the default texture size of the configuration
 * @param config The SDL3 configuration
 * @return The default texture size
*/
coords SDL3_Config_texture_size(SDL3_Config* config) {
	return {
		config->adjsize + 1,
		config->hypsize + 1
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
 * @brief Create a new texture using the default texture size
 * @param config The SDL3 configuration
 * @param pixels The pixels of the texure
 * @return The new texture
*/
Texture Texture_new(SDL3_Config* config, std::vector<std::vector<RGBA>> pixels) {
	return {SDL3_Config_texture_size(config), pixels};
}

/**
 * @brief Create a new texture
 * @param config The SDL3 configuration
 * @param size The size of the texture (in 2D)
 * @param pixels The pixels of the texure
 * @return The new texture
*/
Texture Texture_new(SDL3_Config* config, coords size, std::vector<std::vector<RGBA>> pixels) {
	if(pixels.size() == size.y && pixels[0].size() == size.x) {
		return {size, pixels};
	} else {
		return Texture_new(config, pixels);
	}
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
		std::array<MeshPoint*, 8> cube_mesh_points = cube.mesh_points;
		mesh_points.insert(mesh_points.end(), cube_mesh_points.begin(), cube_mesh_points.end());
	}
	return mesh_points;
}

/**
 * @brief Get the mesh lines of a cube
 * @param cube The cube
 * @return The mesh lines of the cube
 * @note The mesh is in the following order:
 * @note front_down -> right_down [0]
 * @note front_down -> left_down [1]
 * @note back_down -> right_down [2]
 * @note back_down -> left_do [3]
 * @note front_down -> front_up [4]
 * @note back_down -> back_up [5]
 * @note right_down -> right_up [6]
 * @note left_down -> left_up [7]
 * @note front_up -> right_up [8]
 * @note front_up -> left_up [9]
 * @note back_up -> right_up [10]
 * @note back_up -> left_up [11]
*/
std::vector<MeshLine> get_object_mesh_lines(Cube cube) {
	return std::vector<MeshLine>({
		MeshLine_new(cube.mesh_points[0], cube.mesh_points[3]),
		MeshLine_new(cube.mesh_points[0], cube.mesh_points[2]),
		MeshLine_new(cube.mesh_points[1], cube.mesh_points[3]),
		MeshLine_new(cube.mesh_points[1], cube.mesh_points[2]),

		MeshLine_new(cube.mesh_points[0], cube.mesh_points[4]),
		MeshLine_new(cube.mesh_points[1], cube.mesh_points[5]),
		MeshLine_new(cube.mesh_points[2], cube.mesh_points[6]),
		MeshLine_new(cube.mesh_points[3], cube.mesh_points[7]),

		MeshLine_new(cube.mesh_points[4], cube.mesh_points[6]),
		MeshLine_new(cube.mesh_points[4], cube.mesh_points[7]),
		MeshLine_new(cube.mesh_points[5], cube.mesh_points[6]),
		MeshLine_new(cube.mesh_points[5], cube.mesh_points[7]),
	});
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
	set_mesh_points_visibility(get_objects_mesh_points(config));
}

/**
 * @brief Add a cube to the SDL3 configuration
 * @param config The SDL3 configuration
 * @param position The position of the cube
 * @param rbga The RGBA color of the cube
 * @param run_visibility Whether to run the visibility algorithm
*/
void add_cube(SDL3_Config* config, coords3 position, std::array<Texture*, 6> textures, RGBA rgba, bool seethrough = false, bool run_visibility = true) {
	MeshPoint* front_down = MeshPoint_new_ptr(position, true, seethrough);
	MeshPoint* back_down = MeshPoint_new_ptr({position.x + 1, position.y - 1, position.z}, true, seethrough);
	MeshPoint* left_down = MeshPoint_new_ptr({position.x, position.y - 1, position.z}, true, seethrough);
	MeshPoint* right_down = MeshPoint_new_ptr({position.x + 1, position.y, position.z}, true, seethrough);
	MeshPoint* front_up = MeshPoint_new_ptr({position.x, position.y, position.z + 1}, true, seethrough);
	MeshPoint* back_up = MeshPoint_new_ptr({position.x + 1, position.y - 1, position.z + 1}, true, seethrough);
	MeshPoint* left_up = MeshPoint_new_ptr({position.x, position.y - 1, position.z + 1}, true, seethrough);
	MeshPoint* right_up = MeshPoint_new_ptr({position.x + 1, position.y, position.z + 1}, true, seethrough);

	config->objects.push_back(
		{
			std::array<MeshPoint*, 8>({
				front_down,
				back_down,
				left_down,
				right_down,
				front_up,
				back_up,
				left_up,
				right_up
			}),
			textures,
			position,
			rgba
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
 * @param rgba The RGBA color of the cubes
 * @note This function is a wrapper for the add_cube function but adds a layer of optimization by running the visibility algorithm only once.
*/
void add_cubes(SDL3_Config* config, std::vector<coords3> positions, std::vector<std::array<Texture*, 6>> cubes_textures, std::vector<RGBA> rgbas, std::vector<bool> seethroughs){
	for(int i = 0; i < positions.size(); i++) {
		add_cube(config, positions[i], cubes_textures[i], rgbas[i], seethroughs[i], false);
	}
	set_mesh_points_visibility(config);
}

/**
 * @brief Add cubes to the SDL3 configuration
 * @param config The SDL3 configuration
 * @param positions The positions of the cubes
 * @param rgba The RGBA color of the cubes
 * @note This function is a wrapper for the add_cube function but adds a layer of optimization by running the visibility algorithm only once.
*/
void add_cubes(SDL3_Config* config, std::vector<coords3> positions, std::vector<std::array<Texture*, 6>> cubes_textures, RGBA rgba, bool seethrough = false) {
	add_cubes(config, positions, cubes_textures, std::vector<RGBA>(positions.size(), rgba), std::vector<bool>(positions.size(), seethrough));
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
 * @brief Draw the mesh lines of an object
 * @param renderer The SDL renderer
 * @param config The SDL3 configuration
 * @param cube The cube to render the mesh lines of
*/
void draw_object_mesh_lines(SDL_Renderer* renderer, SDL3_Config* config, Cube cube) {
	for(auto mesh_line : get_object_mesh_lines(cube)) {
		draw_mesh_line(renderer, config, mesh_line);
	}
}

void draw_simple_descending_face(SDL_Renderer* renderer, SDL3_Config* config, Texture* texture, coords start, coords end) {
	for(int i = 0; i < texture->pixels.size(); i++) {
		draw_line(
			renderer,
			start,
			end,
			texture->pixels[i]
		);
		start.y++;
		end.y++;
	}
}

void draw_simple_ascending_face(SDL_Renderer* renderer, SDL3_Config* config, Texture* texture, coords start, coords end) {
	for(int i = texture->pixels.size() - 1; i >= 0; i--) {
		draw_line(
			renderer,
			start,
			end,
			texture->pixels[i]
		);
		start.y++;
		end.y++;
	}
}

void draw_complex_face(SDL_Renderer* renderer, SDL3_Config* config, Texture* texture, coords top, coords left, coords right, coords bottom) {
	/*
		You cannot actually draw a face with a texture using diagonal lines.
		The lines will only fill the space if you stack them on top of each other following an axis.
		Else the lines will not fill the space.

		Possible solution:
			Draw a line under the last (using a new alg) but need to determine the x offset of the new line (y just being ++)
	*/
	auto slider = linegen(left, bottom).line_vec;
	auto slider_opposite = linegen(top, right).line_vec;

	for(int i = 0; i < slider.size(); i++) {
		auto ln = linegen(slider[i], slider_opposite[i]);
		std::cout << slider[i].x - slider_opposite[i].x << "; " << slider[i].y - slider_opposite[i].y << "\n";

		draw_line(renderer, ln, texture->pixels[i]);	
	}
	std::cout << std::endl;
}

/**
 * @brief Draw the faces of an object
 * @param renderer The SDL renderer
 * @param config The SDL3 configuration
 * @param cube The cube to render the faces of
*/
void draw_object_faces(SDL_Renderer* renderer, SDL3_Config* config, Cube cube) {
	/*// Front left face
	draw_simple_descending_face(
		renderer,
		config,
		cube.textures[2],
		get_2d_coords(cube.mesh_points[4]->point, config),
		get_2d_coords(cube.mesh_points[6]->point, config)
	);
	// Back right face
	draw_simple_descending_face(
		renderer,
		config,
		cube.textures[5],
		get_2d_coords(cube.mesh_points[7]->point, config),
		get_2d_coords(cube.mesh_points[5]->point, config)
	);
	// Back left face
	draw_simple_ascending_face(
		renderer,
		config,
		cube.textures[4],
		get_2d_coords(cube.mesh_points[6]->point, config),
		get_2d_coords(cube.mesh_points[5]->point, config)
	);
	// Front right face
	draw_simple_ascending_face(
		renderer,
		config,
		cube.textures[3],
		get_2d_coords(cube.mesh_points[4]->point, config),
		get_2d_coords(cube.mesh_points[7]->point, config)
	);
	// Top face
	draw_complex_face(
		renderer,
		config,
		cube.textures[0],
		get_2d_coords(cube.mesh_points[5]->point, config),
		get_2d_coords(cube.mesh_points[6]->point, config),
		get_2d_coords(cube.mesh_points[7]->point, config),
		get_2d_coords(cube.mesh_points[4]->point, config)
	);*/
	// Bottom face
	draw_complex_face(
		renderer,
		config,
		cube.textures[1],
		get_2d_coords(cube.mesh_points[1]->point, config),
		get_2d_coords(cube.mesh_points[2]->point, config),
		get_2d_coords(cube.mesh_points[3]->point, config),
		get_2d_coords(cube.mesh_points[0]->point, config)
	);
}

/**
 * @brief Draw the lines of the cubes
 * @param renderer The SDL renderer
 * @param config The SDL3 configuration
*/
void draw_objects(SDL_Renderer* renderer, SDL3_Config* config) {
	for(auto cube : config->objects) {
		draw_object_mesh_lines(renderer, config, cube);
	}
}

#endif