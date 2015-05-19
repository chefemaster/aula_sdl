#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>
#include <stdio.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Event event;

SDL_Window* tela = NULL;
SDL_Surface* surface = NULL;
SDL_Surface* imgFundo = NULL;

//The sound effects that will used
Mix_Chunk* scratch = NULL;
Mix_Chunk* high = NULL;
Mix_Chunk* med = NULL;
Mix_Chunk* low = NULL;

//The music that will played
Mix_Music* music = NULL;

bool load_files()
{
	music = Mix_LoadMUS("D:/Faculdade/media/music/hep_cats.mp3");
	if (music == NULL){
		return false;
	}

	scratch = Mix_LoadWAV("D:/Faculdade/media/effect/slap.wav");
	high = Mix_LoadWAV("D:/Faculdade/media/effect/jab.wav");
	med = Mix_LoadWAV("D:/Faculdade/media/effect/kick.wav");
	low = Mix_LoadWAV("D:/Faculdade/media/effect/bite.wav");
	if ((scratch == NULL) || (high == NULL) || (med == NULL) || (low == NULL)){
		return false;
	}

	return true;
}

SDL_Surface* load_image(string path)
{
	SDL_Surface* imagem = IMG_Load(path.c_str());
	if (imagem == NULL){
		printf("Não foi possível carregar imagem: %s ! SDL_imagem Error: %s \n", path.c_str(), IMG_GetError());
	}
	return imagem;
}

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		printf("Erro de ligar o vídeo! SDL_Erro %s \n", SDL_GetError());
		success = false;
	}
	else{
		tela = SDL_CreateWindow("SDL 2.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (tela == NULL){
			printf("Interface gráfica não pode ser criada! SDL_error: %s \n", SDL_GetError());
			success = true;
		}
		else{
			surface = SDL_GetWindowSurface(tela);
		}
	}
	//Inicializa o SDL_mixer
	(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) ? success = false : success = true;

	return success;
}

void close()
{
	SDL_FreeSurface(imgFundo);
	SDL_DestroyWindow(tela);
	Mix_FreeChunk(scratch);
	Mix_FreeChunk(high);
	Mix_FreeChunk(med);
	Mix_FreeChunk(low);
	Mix_FreeMusic(music);
	SDL_Quit();
}

bool quit = false;
int main(int argc, char* arg[]){
	if (!init()){
		printf("Falha ao iniciar SDL!\n");
	}
	else
	{
		!load_files() ? quit = true : Mix_PlayMusic(music, -1);
		imgFundo = load_image("D:/Faculdade/media/image/background.jpg");
		while (!quit)
		{
			//Pegando o evendo do dispositivo
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				if (event.type == SDL_KEYUP)
				{
					if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;
					switch (event.key.keysym.sym)
					{
					case SDLK_1: quit = (Mix_PlayChannel(-1, scratch, 0) == -1) ? true : false; break;
					case SDLK_2: quit = (Mix_PlayChannel(-1, high, 0) == -1) ? true : false; break;
					case SDLK_3: quit = (Mix_PlayChannel(-1, med, 0) == -1) ? true : false; break;
					case SDLK_4: quit = (Mix_PlayChannel(-1, low, 0) == -1) ? true : false; break;
					case SDLK_9: quit = (Mix_PlayingMusic() == 0)? (Mix_PlayMusic(music, -1)):true; break;
					case SDLK_0: Mix_HaltMusic(); break;
					default:
						break;
					}
				}
			}
			SDL_Rect rsDest;
			rsDest.w = SCREEN_WIDTH;
			rsDest.h = SCREEN_HEIGHT;
			SDL_Rect rcSorc = imgFundo->clip_rect;
			SDL_BlitSurface(imgFundo, &rcSorc, surface, &rsDest);
			SDL_UpdateWindowSurface(tela);
		}
		SDL_UpdateWindowSurface(tela);
	}
	close();
	SDL_Delay(2000);
	return 0;
}