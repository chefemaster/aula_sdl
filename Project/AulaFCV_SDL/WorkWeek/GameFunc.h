#ifndef GAMEFUNC_H
#define GAMEFUNC_H
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

using namespace std;

//Window e image
int sWidth = 0;
int sHeight = 0;

SDL_Window* gWindow = NULL;
SDL_Surface* gSurface = NULL; 
SDL_Surface* imgBackground = NULL;

//The music that will played
Mix_Music* music = NULL;

void ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, clip, destination, &offset);
}

bool Init(int screenWidth, int screenHeight){
	sWidth = screenWidth;
	sHeight = screenHeight;

	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		printf("Erro ao inicia a SDL! SDL_Error: %s \n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("SDL Sprite", 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			screenWidth, screenHeight, SDL_WINDOW_SHOWN);
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
				//Inicializar Imagens
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("Erro na lib SDL_image.dll! SDL_Error: %s\n", IMG_GetError());
					success = false;
				}

				//Inicializa o SDL_mixer
				(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) ? success = false : success = true;
			}
		}
	}
	return success;
}

void Close(){
	SDL_FreeSurface(imgBackground);	

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	IMG_Quit();
	SDL_Quit();
}

void Update(){
	if (gSurface != NULL){
		ApplySurface(0, 0, imgBackground, gSurface, NULL);
	}
}

bool SetBackground(string path){
	imgBackground = IMG_Load(path.c_str());
	if (imgBackground == NULL){
		printf("Erro ao carregar imagem: %s ! SDL_Error: %s \n",
			path.c_str(), IMG_GetError());
		return false;
	}
	return true;
}

bool SetMusic(string path){
	music = Mix_LoadMUS(path.c_str());
	if (music == NULL){
		printf("Erro ao carregar musica: %s ! SDL_Error: %s /n",
			path.c_str(), SDL_GetError());
		return false;
	}
	return true;
}

void PlayMusic()
{
	if (music != NULL){
		if (Mix_PlayingMusic() == 0) 
			Mix_PlayMusic(music, -1);
	}
}

void StopMusic()
{
	if (music != NULL){
		Mix_HaltMusic();
	}
}

SDL_Surface* LoadImage(string path){
	SDL_Surface* texture = NULL;
	texture = IMG_Load(path.c_str());
	if (texture == NULL){
		printf("Não foi possivel carregar imagem: %s ! SDL_Error: %s \n",
			path.c_str(), IMG_GetError());
	}
	return texture;
}

Mix_Chunk* LoadEffect(char* path){	 
	Mix_Chunk* effect = Mix_LoadWAV(path);
	if (effect == NULL){
		printf("Não foi possivel carregar efeito sonoro: %s ! SDL_Error: %s \n",path, IMG_GetError());
	}

	return effect;
}
