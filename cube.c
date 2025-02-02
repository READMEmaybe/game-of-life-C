#include <SDL.h>
#include <stdbool.h>

#define WIDTH 500
#define HEIGHT 500
#define WHITE 0xffffffff

void drawGrid(SDL_Surface* surface, int cellWidth) {
	for(int i = 0; i < (HEIGHT / cellWidth); i++) {
		SDL_Rect rect = (SDL_Rect) {0,i*cellWidth, WIDTH, 1};
		SDL_FillRect(surface, &rect, WHITE);
	}
	for(int i = 0; i < (WIDTH / cellWidth); i++) {
		SDL_Rect rect = (SDL_Rect) {i*cellWidth,0, 1, HEIGHT};
		SDL_FillRect(surface, &rect, WHITE);
	}
}

int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow( "Test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

	SDL_Surface* surface = SDL_GetWindowSurface(window);

	SDL_Rect rect = (SDL_Rect) {1*10, 2*10, 10, 10};
	SDL_FillRect(surface, &rect, 0xffffffff);

	drawGrid(surface, 10);
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
