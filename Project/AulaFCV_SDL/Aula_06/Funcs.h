#ifndef FUNCS_H
#define FUNCS_H
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gSurface = NULL;

void ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, clip, destination, &offset);
}

SDL_Surface* LoadImage(char* path){
	SDL_Surface* loadImage = NULL;
	loadImage = IMG_Load(path);
	if (loadImage == NULL){
		printf("Não foi possivel carregar imagem: %s ! SDL_Error: %s \n", path, IMG_GetError());
	}
	return loadImage;
}

bool Init(){
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		printf("Erro ao inicia a SDL! SDL_Error: %s \n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("SDL Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Não foi possivel criar a janela! SDL_Error: %s \n", SDL_GetError());
			success = false;
		}
		else
		{
			gSurface = SDL_GetWindowSurface(gWindow);
			if (gSurface == NULL)
			{
				printf("Não foi possivel criar a visualização! SDL_Error: %s \n", SDL_GetError());
				success = false;
			}
			else
			{
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("Erro na lib SDL_image.dll! SDL_Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

void Close(){
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	IMG_Quit();
	SDL_Quit();
}