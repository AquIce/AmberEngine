#include <iostream>
#include <SDL2/SDL.h>
#include <AquIce/PixelMap2d.hpp>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

int main(int argc, char* argv[]) {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	Pixel pixel;
	set_pixel(&pixel, 255, 255, 255, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	draw_pixel(renderer, &pixel);

	SDL_RenderPresent(renderer);

	while(true) {
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				break;
			}
		}
	}

	return EXIT_SUCCESS;
}