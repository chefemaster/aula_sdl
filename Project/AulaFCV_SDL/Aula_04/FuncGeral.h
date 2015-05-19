#ifndef FUNCGERAL_H
	#define FUNCGERAL_H
#endif

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <cstdlib>

using namespace std;

SDL_Surface* carrega_imagem(string filename){
	SDL_Surface* img = IMG_Load(filename.c_str());
	if (img == NULL)
	{
		printf("Erro de Carregamento da imagem %s! SDL Error: %s \n", filename, SDL_GetError());
	}
	return img;
}

void desenha(int x, int y, SDL_Surface* origem, SDL_Surface* destino)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(origem, NULL, destino, &offset);
}

SDL_Window* initSDL(SDL_Window* window, int w, int h, string titulo)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Erro de Ligar o Vídeo! SDL Error: %S \n", SDL_GetError());
	}
	else{
		window = SDL_CreateWindow(titulo.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			w, h,
			SDL_WINDOW_SHOWN);
		if (window == NULL){
			printf("Interface gráfica não pode ser criada! SDL Error: %s, \n", SDL_GetError());
		}
	}
	return window;
}
