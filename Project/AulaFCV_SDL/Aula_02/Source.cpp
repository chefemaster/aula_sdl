#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();
SDL_Surface* load_image(string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWord = NULL;

void messageError(const char* msg, const char* error)
{
	printf("%s! SDL_Error %s \n", msg, error);
	SDL_Delay(1000);
}


bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		messageError("Erro de ligar o vídeo", SDL_GetError());
		//printf("Erro de ligar o vídeo! SDL %s \n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("SDL 2.0",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL){
			messageError("Interface gráfica não pode ser criada", SDL_GetError());
			//printf("Interface gráfica não pode ser criada! SDL_Erro: %s \n", SDL_GetError());
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;
	gHelloWord = SDL_LoadBMP("c:/img/logo_google.bmp");
	if (gHelloWord == NULL)
	{
		messageError("Erro ao carregar imagem BMP", SDL_GetError());
		//printf("Erro ao carregar imagem BMP %s| SDL_Error: %s \n", SDL_GetError());
		success = false;
	}

	return success;
}

SDL_Surface* load_image(string path){
	SDL_Surface* imagem = IMG_Load(path.c_str());
	if (imagem == NULL)
	{
		messageError("Não foi possível carregar imagem: ", IMG_GetError());
	}
	return imagem;
}

void close()
{
	SDL_FreeSurface(gHelloWord);
	gHelloWord = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

int main(int argc, char* args[]){
	if (!init())
	{
		messageError("Falha ao iniciar DSL! \n", "");
		//printf("Falha ao iniciar DSL! \n");
	}
	else
	{
		gHelloWord = load_image("c:/img/logo_google.jpg");
		SDL_BlitSurface(gHelloWord, NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);
		SDL_Delay(2000);
		/*
		if (!loadMedia())
		{
			messageError("Falha ao carregar arquivo!\n", "");
			//printf("Falha ao carregar arquivo!\n");
		}
		else
		{
			SDL_BlitSurface(gHelloWord, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
			SDL_Delay(2000);
		}*/
	}
	close();
	return 0;
}