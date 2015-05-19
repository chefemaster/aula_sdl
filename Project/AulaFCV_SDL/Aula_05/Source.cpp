#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <iostream>

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SPRITE_SIZE_WIDTH 64
#define SPRITE_SIZE_HEIGHT 128
#define SPRITE_SIZE_FRAME 20

SDL_Window* tela = NULL;
SDL_Surface* surface = NULL;
SDL_Surface* imgFundo = NULL;
SDL_Surface* sprite = NULL;

Uint32 last = 0, deltaTime = 70;

SDL_Rect rcSrc, rcSprite[SPRITE_SIZE_FRAME];
SDL_Event event;

int quit;
int key = 0, posX = 0, posY = 0;

SDL_Surface* Load_image(string path){
	SDL_Surface* imagem = IMG_Load(path.c_str());
	if (imagem == NULL)
	{
		printf("Não foi possível carregar imagem: %s! SDL_Error: %s \n", path.c_str(), IMG_GetError());
	}

	return imagem;
}

void Close(){
	SDL_FreeSurface(imgFundo);
	SDL_FreeSurface(sprite);
	SDL_DestroyWindow(tela);
	SDL_Quit();
}

bool init(){
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Erro de ligar vídeo! SDL_Error: %s \n", SDL_GetError());
		success = false;
	}
	else{
		tela = SDL_CreateWindow("SDL Sprite", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (tela == NULL){
			printf("Interface gráfica não pode ser criada! SDL_Error: %s \n", SDL_GetError());
			success = false;
		}
		else{
			surface = SDL_GetWindowSurface(tela);
			imgFundo = Load_image("D:/Faculdade/media/image/background.jpg");
			sprite = Load_image("D:/Faculdade/media/image/walk.png");
			rcSrc.w = SPRITE_SIZE_WIDTH;
			rcSrc.h = SPRITE_SIZE_HEIGHT;
			for (size_t i = 0; i < SPRITE_SIZE_FRAME; i++)
			{
				(i < (SPRITE_SIZE_FRAME / 2)) ? (rcSprite[i].x = i * SPRITE_SIZE_WIDTH) : (rcSprite[i].x = (i - (SPRITE_SIZE_FRAME / 2)) * SPRITE_SIZE_WIDTH);
				(i < (SPRITE_SIZE_FRAME / 2)) ? (rcSprite[i].y = 0) : (rcSprite[i].y = SPRITE_SIZE_HEIGHT);
				rcSprite[i].w = SPRITE_SIZE_WIDTH;
				rcSprite[i].h = SPRITE_SIZE_HEIGHT;
			}
		}
	}
	return success;
}

void HandleEvent(SDL_Event event){

	Uint32 now = SDL_GetTicks();
	bool action = false;
	if (now - last > deltaTime){
		last = now;
		action = true;
	}	

	switch (event.type)
	{
		case SDL_QUIT:
			quit = 1;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				case SDLK_q:
					quit = 1;
					break;
				case SDLK_RIGHT:
					if (action){
						key++;
						if (key > ((SPRITE_SIZE_FRAME / 2) - 1))
							key = 0;
					}
					posX += 10;
					break;
				case SDLK_LEFT:
					if (action){
						key++;
						if (key < ((SPRITE_SIZE_FRAME / 2) - 2))
							key = (SPRITE_SIZE_FRAME / 2);
						if (key > SPRITE_SIZE_FRAME - 1)
							key = (SPRITE_SIZE_FRAME / 2);
					}
					posX -= 10;
				default:
					break;
			}
			break;
		default:
			break;
	}

	if (posX >= (SCREEN_WIDTH - SPRITE_SIZE_WIDTH))
		posX = (SCREEN_WIDTH - SPRITE_SIZE_WIDTH);
	if (posX < 0)
		posX = 0;

	posY = 10;
}

int main(int argc, char* args[]){
	if (!init())
	{
		printf("Falha ao Iniciar SDL! \n");
	}
	else{
		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				HandleEvent(event);
			}
			SDL_BlitSurface(imgFundo, NULL, surface, NULL);

			rcSrc.x = posX;
			rcSrc.y = posY;			
			SDL_BlitSurface(sprite, &rcSprite[key], surface, &rcSrc);

			SDL_UpdateWindowSurface(tela);
		}
		SDL_UpdateWindowSurface(tela);
	}

	Close();
	return 0;
}