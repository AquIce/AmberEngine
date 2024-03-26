#include <iostream>
#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>
#include <AquIce/SDL2/SDL.h>
#include <AquIce/SDL3/SDL.hpp>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

const int TEXTURE_WIDTH = 2000;
const int TEXTURE_HEIGHT = 2000;

int main(int argc, char* argv[]) {
	// Initialize SDL
	auto config2 = AquIce_SDL_Setup("SDL Texture", SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	auto config3 = SDL3_Config_new({200, 300}, 100);
	
	// Create an event
	SDL_Event event;

	// Create source and destination rectangles
	SDL_Rect source{0, 0, SCREEN_WIDTH / 32, SCREEN_HEIGHT / 32};
	SDL_Rect dest{10, 10, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20};

	// Create a texture
	SDL_Texture* texture = SDL_CreateTexture(
		config2.renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		TEXTURE_WIDTH,
		TEXTURE_HEIGHT
	);

	// Add cubes to the 3D config
	add_cubes(
		&config3,
		{
			{0, 0, 0},
			{-1, 0, 0},
			{0, 1, 0},
			{0, 0, 1},
			{0, 1, 1},
			{-1, 0, 1},
			{-1, 1, 0}
		},
		{0, 0, 0, 255}
	);

	// Program loop
	while(config2.running) {
		// Handle events
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT: // App Quit
					config2.running = false;
					break;
				case SDL_KEYDOWN: // Key Press
					switch(event.key.keysym.sym) {
						case SDLK_UP:
							source.y -= 3;
							break;
						case SDLK_DOWN:
							source.y += 3;
							break;
						case SDLK_LEFT:
							source.y -= 3;
							break;
						case SDLK_RIGHT:
							source.y += 3;
							break;
						case SDLK_1:
							source.w *= 2;
							source.h *= 2;
							break;
						case SDLK_2:
							source.w /= 2;
							source.h /= 2;
							break;
					}
					break;
				case SDL_MOUSEWHEEL: // Mouse Wheel
					config2.scale += event.wheel.y > 0 ? 1 : -1;
			}
		}

		// Set render scale (zoom)
		AquIce_SDL_SetScale(&config2);

		// Clear screen
		AquIce_SDL_ClearRenderer(config2.renderer);

		// Clear the texture
		SDL_SetRenderTarget(config2.renderer, texture);
		SDL_SetRenderDrawColor(config2.renderer, 255, 255, 255, 255);
		SDL_RenderClear(config2.renderer);

		// Draw all the objects from the 3D config
		draw_objects(config2.renderer, &config3);

		// Set back render target to window (nullptr -> default)
		SDL_SetRenderTarget(config2.renderer, nullptr);

		// Render texture
		SDL_RenderClear(config2.renderer);
		SDL_RenderCopy(config2.renderer, texture, &source, &dest);

		// Present renderer
		SDL_RenderPresent(config2.renderer);

		SDL_Delay(50);
	}

	return EXIT_SUCCESS;
}