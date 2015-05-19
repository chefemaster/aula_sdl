#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include "FuncGeral.h"
#include "cpButton.h"

using namespace std;
using namespace game;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWord = NULL;
bool quit = false;

void close(){
	SDL_FreeSurface(gHelloWord);
	gHelloWord = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

int main(int argc, char* args[]){
	gWindow = initSDL(gWindow, 800, 600, "Teste Botões");
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	gHelloWord = carrega_imagem("D:/Faculdade/media/image/background.jpg");
	Button* btn = new Button(256, 256,
		"D:/Faculdade/media/image/button_up.png",
		"D:/Faculdade/media/image/button_down.png");
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			btn->handle_events(e);
			if (btn->getStatus() == 2){
				SDL_Delay(2000);
				quit = true;
			}
			SDL_BlitSurface(gHelloWord, NULL, gScreenSurface, NULL);
			btn->Show(gScreenSurface);			
			SDL_UpdateWindowSurface(gWindow);
		}
		SDL_UpdateWindowSurface(gWindow);
	}
	btn->~Button();
	close();
	return 0;
}

