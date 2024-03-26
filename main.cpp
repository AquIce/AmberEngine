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
	auto config3 = SDL3_Config_new({500, 500}, 100);
	
	// Create an event
	SDL_Event event;

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

	std::vector<SDL_Point> points;
	for(int i = 0; i < 10000; i++) {
		points.push_back({
			rand() % TEXTURE_HEIGHT,
			rand() % TEXTURE_WIDTH
		});
	}

	add_cube(&config3, {0, 0, 0}, 0, 0, 0, 255);
	add_cube(&config3, {-1, 0, 0}, 0, 0, 0, 255);
	add_cube(&config3, {0, 1, 0}, 0, 0, 0, 255);
	add_cube(&config3, {0, 0, 1}, 0, 0, 0, 255);

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

		// Move position of dots
		std::for_each(points.begin(), points.end(), [](auto& item) {
			item.x += rand() % 3 - 1;
			item.y += rand() % 3 - 1;
		});

		// Draw dots to texture
		//SDL_SetRenderDrawColor(config.renderer, 0, 0, 0, 255);
		//SDL_RenderDrawPoints(config.renderer, points.data(), points.size());
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