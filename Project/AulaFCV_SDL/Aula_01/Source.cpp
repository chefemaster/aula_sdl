#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
const int SCREEN_WIDTH = 640;
const int SCRREN_HEIGHT = 480;

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Erro de ligar o vídeo! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("SDL2.0 Prof. Eduardo Damasceno",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCRREN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Interface gráfica não podeser criada!SDL_Error: %s \n", SDL_GetError());
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL,
				SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}
}