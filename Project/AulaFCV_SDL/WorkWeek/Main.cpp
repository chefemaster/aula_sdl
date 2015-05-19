#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

#include "AnimateSprite.h"

using namespace std;
using namespace sprite;

SDL_Event event;

int main(int argc, char* args[]){
	bool quit = false;
	if (!Init(800, 600))
	{
		printf("Falha ao Iniciar SDL! \n");
	}
	else{
		SetBackground("D:/Faculdade/media/image/background.jpg");
		SetMusic("D:/Faculdade/media/music/pokemon.mp3");

		AnimateSprite* aSprite =
			new AnimateSprite("D:/Faculdade/media/image/sprite_sheet.png", 3, 5);
		aSprite->SetEffect("D:/Faculdade/media/effect/blastoise.wav");
		PlayMusic();

		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				switch (event.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_q:
						quit = true;
						break;
					}
					break;
				}
				aSprite->Control(event);
			}
			//Desenha o fundo
			Update();
			aSprite->Render();
			SDL_UpdateWindowSurface(gWindow);
		}
		SDL_UpdateWindowSurface(gWindow);
		aSprite->~AnimateSprite();

		StopMusic();
	}
	SDL_Delay(2000);
	Close();
	return 0;
}