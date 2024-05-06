#ifndef __AQUICE_SDL2_SDL_HPP__
#define __AQUICE_SDL2_SDL_HPP__

#include "../../SDL2/SDL.h"

/**
 * @brief The configuration for the SDL2 library
*/
typedef struct AquIce_SDL2_Config {
	/**
	 * @brief The window to render to
	*/
	SDL_Window* window;
	/**
	 * @brief The renderer to render with
	*/
	SDL_Renderer* renderer;
	/**
	 * @brief Whether the window is running
	*/
	bool running;
	/**
	 * @brief The scale of the window
	*/
	int scale;
} AquIce_SDL2_Config;

/**
 * @brief Set up the SDL2 library
 * @param title The title of the window
 * @param width The width of the window
 * @param height The height of the window
 * @param scale The scale of the window
 * @return The configuration for the SDL2 library
*/
AquIce_SDL2_Config AquIce_SDL2_Setup(const char* title, int width, int height, int scale) {
	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		0
	);
	// Create a renderer
	auto renderer = SDL_CreateRenderer(
		window,
		-1,
		0
	);
	return {
		window,
		renderer,
		true,
		scale
	};
}

/**
 * @brief Set the scale of the window
*/
void AquIce_SDL2_SetScale(AquIce_SDL2_Config* config) {
	SDL_RenderSetScale(
		config->renderer,
		config->scale,
		config->scale
	);
}

/**
 * @brief Clear the renderer
 * @param renderer The renderer to clear
 * @param r The red value
 * @param g The green value
 * @param b The blue value
 * @param a The alpha value
*/
void AquIce_SDL2_ClearRenderer(SDL_Renderer* renderer, int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}
/**
 * @brief Clear the renderer
 * @param renderer The renderer to clear
 * @param r The red value
 * @param g The green value
 * @param b The blue value
*/
void AquIce_SDL2_ClearRenderer(SDL_Renderer* renderer, int r, int g, int b) {
	AquIce_SDL2_ClearRenderer(renderer, r, g, b, 255);
}
/**
 * @brief Clear the renderer
 * @param renderer The renderer to clear
*/
void AquIce_SDL2_ClearRenderer(SDL_Renderer* renderer) {
	AquIce_SDL2_ClearRenderer(renderer, 0, 0, 0);
}

#endif
