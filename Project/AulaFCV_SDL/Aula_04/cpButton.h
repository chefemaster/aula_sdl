#ifndef CPBUTTON_H
#define CPBUTTON_H
#endif

#include <iostream>
#include <cstdlib>
//#include "FuncGeral.h"

using namespace std;

namespace game{
	class Button{
	private:
		SDL_Rect box;
		SDL_Surface* imgButtonUp;
		SDL_Surface* imgButtonDown;
		SDL_Surface* imgButton;
		int status;
	public:
		Button(int w, int h, char* _filename1, char* _filename2);
		~Button();
		void handle_events(SDL_Event _evt);
		void Show(SDL_Surface* screen);
		void SetPosition(int x, int y);		
		int getStatus(){ return status; }
	};

	Button::Button(int x, int y, char* _filename1, char* _filename2){
		this->imgButtonUp = carrega_imagem(_filename1);
		this->imgButtonDown = carrega_imagem(_filename2);
		this->imgButton = imgButtonUp;

		this->box = this->imgButton->clip_rect;
		this->box.x = x;
		this->box.y = y;

		status = 0;
	};

	void Button::Show(SDL_Surface* screen){
		desenha(box.x, box.y, this->imgButton, screen);
	};

	void Button::handle_events(SDL_Event _evt)
	{
		int x = 0, y = 0;
		if (_evt.type == SDL_MOUSEMOTION){
			x = _evt.motion.x;
			y = _evt.motion.y;
			if ((x > box.x) && (x < box.x + box.w) &&
				(y > box.y) && (y < box.y + box.h))
			{
				this->imgButton = this->imgButtonDown;
				this->status = 1;
			}
			else
			{
				this->imgButton = this->imgButtonUp;
				this->status = 0;
			}
		}
		if (_evt.type == SDL_MOUSEBUTTONDOWN)
		{
			if (_evt.button.button == SDL_BUTTON_LEFT){
				x = _evt.button.x;
				y = _evt.button.y;
				if ((x > box.x) &&
					(x <box.x + box.w) &&
					(y > box.y) &&
					(y < box.y + box.h)){
					this->imgButton = this->imgButtonDown;
					this->status = 2;
				}
			}
		}

		if (_evt.type == SDL_MOUSEBUTTONUP){
			if (_evt.button.button == SDL_BUTTON_LEFT){
				x = _evt.button.x;
				y = _evt.button.y;
				if ((x > box.x) &&
					(x <box.x + box.w) &&
					(y > box.y) &&
					(y < box.y + box.h)){
					this->imgButton = this->imgButtonUp;
					this->status = 0;
				}
			}
		}
	};

	Button::~Button(){
		SDL_FreeSurface(imgButton);
		SDL_FreeSurface(imgButtonDown);
		SDL_FreeSurface(imgButton);
	};
}