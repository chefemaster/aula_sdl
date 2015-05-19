#ifndef CLSBUTTON_H
	#define CLSBUTTON_H
#endif

#pragma comment (lib, "C:/dev_game/SDL2/lib/x86/SDL2.lib")
#pragma comment (lib, "C:/dev_game/SDL2/lib/x86/SDL2main.lib")
#pragma comment (lib, "C:/dev_game/SDL2/lib/x86/SDL2_image.lib")

#include"C:/dev_game/SDL2/include/SDL.h"
#include "C:/dev_game/SDL2/include/SDL_image.h"

#include <iostream>
#include <cstdlib>

using namespace std;

SDL_Surface* LOADIMAGE(char* filename){
	SDL_Surface* img = IMG_Load(filename);
	if (img == NULL)
	{
		cout<<"Erro de Carregamento da imagem"<<filename<<" - SDL Error:"<< SDL_GetError()<<endl;
	}

	return (img != NULL)?img:NULL;
}

void DESENHA(int x, int y, SDL_Surface* origem, SDL_Surface* destino){
	SDL_Rect corte;
	corte.x = x;
	corte.y = y;

	SDL_BlitSurface(origem, NULL, destino, &corte);
}

