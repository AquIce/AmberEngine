#include <iostream>
#include <SDL2/SDL.h>
#include <AquIce/SDL/PixelMap2d.hpp>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

int main(int argc, char* argv[]) {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, 0, &window, &renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderSetScale(renderer, 50, 50);

	PixelMap2d* pixel_map_2d = PixelMap2d_new(
		new std::vector<PixelMap*>(
			{
				PixelMap_new(
					new std::vector<Pixel*>(
						{
							Pixel_new(255, 0, 0, 255, 0, 0),
							Pixel_new(0, 255, 0, 255, 1, 0),
							Pixel_new(0, 0, 255, 255, 2, 0),
							Pixel_new(255, 255, 0, 255, 3, 0),
							Pixel_new(255, 0, 255, 255, 4, 0),
							Pixel_new(0, 255, 255, 255, 5, 0),
							Pixel_new(0, 0, 0, 255, 7, 0),
							Pixel_new(255, 255, 255, 255, 6, 0),
						}
					)
				),
				PixelMap_new(
					new std::vector<Pixel*>(
						{
							Pixel_new(0, 0, 0, 255, 7, 1),
							Pixel_new(255, 0, 0, 255, 0, 1),
							Pixel_new(255, 255, 0, 255, 3, 1),
							Pixel_new(0, 0, 255, 255, 2, 1),
							Pixel_new(0, 255, 255, 255, 5, 1),
							Pixel_new(255, 0, 255, 255, 4, 1),
							Pixel_new(0, 255, 0, 255, 1, 1),
							Pixel_new(255, 255, 255, 255, 6, 1),
						}
					)
				),
				PixelMap_new(
					new std::vector<Pixel*>(
						{
							Pixel_new(255, 255, 0, 255, 3, 2),
							Pixel_new(255, 255, 255, 255, 6, 2),
							Pixel_new(0, 255, 0, 255, 1, 2),
							Pixel_new(255, 0, 255, 255, 4, 2),
							Pixel_new(0, 0, 255, 255, 2, 2),
							Pixel_new(0, 0, 0, 255, 7, 2),
							Pixel_new(0, 255, 255, 255, 5, 2),
							Pixel_new(255, 0, 0, 255, 0, 2),
						}
					)
				),
			}
		)
	);
	
	draw_pixel_map_2d(renderer, pixel_map_2d);

	SDL_RenderPresent(renderer);

	while(true) {
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				break;
			}
		}
	}

	DestroyPixelMap2d(pixel_map_2d);

	return EXIT_SUCCESS;
}