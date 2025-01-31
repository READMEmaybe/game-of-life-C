#include <SDL.h>
#include <stdbool.h>


int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow( "Test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, 0);

	SDL_Surface* surface = SDL_GetWindowSurface(window);

	SDL_Rect rect = (SDL_Rect) {30, 40, 80, 80};
	SDL_FillRect(surface, &rect, 0xffffffff);

	SDL_UpdateWindowSurface(window);

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
		}
	}
	SDL_Quit();

	return 0;
}
