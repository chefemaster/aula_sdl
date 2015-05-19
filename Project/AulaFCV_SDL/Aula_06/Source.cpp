#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Map.h"

using namespace maps;

int main(int argc, char* args[]){
	if (!Init()){
		printf("Erro ao iniciar SDL!\n");
	}
	else
	{
		MyMap* map = new MyMap();

		bool quit = false;
		SDL_Event ev;

		while (!quit)
		{
			while (SDL_PollEvent(&ev) != 0)
			{
				switch (ev.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					break;
				default:
					break;
				}
			}
			map->RenderMap(gSurface);
			SDL_UpdateWindowSurface(gWindow);
		}
		SDL_UpdateWindowSurface(gWindow);
	}

	Close();
	return 0;
}