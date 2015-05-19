#ifndef CLSBUTTON_H
	#define CLSBUTTON_H
#endif

#include <iostream>
#include <cstdlib>
#include "Function.h"

using namespace std;

namespace game{
	class Button{
		private:
			SDL_Rect box;
			SDL_Surface* back_image;
			SDL_Surface* front_image;
			SDL_Surface* image;
			int status;
			int H;
			int W;
		public:
			Button(int w, int h, char* _filename1, char* _filename2);
			~Button();
			void Show(SDL_Surface* screen);
			void SetPosition(int x, int y);
			void SetHandle(SDL_Event _evt);
			int getStatus(){ return status; }
	};

	Button::Button(int x, int y, char* _filename1, char* _filename2){
		back_image = LOADIMAGE(_filename1);
		front_image = LOADIMAGE(_filename2);
		image = back_image;

		H = back_image->h;
		W = back_image->w;

		box = back_image->clip_rect;
		box.x = x;
		box.y = y;

		status = 0;
	};

	void Button::Show(SDL_Surface* screen){
		DESENHA(box.x, box.y, image, screen);
	};

	void Button::SetHandle(SDL_Event _evt)
	{
		int x = 0, y = 0;
		if (_evt.type == SDL_MOUSEMOTION){
			x = _evt.motion.x;
			y = _evt.motion.y;
			if ((x > box.x) && (x < box.x + box.w) &&
				(y > box.y) && (y < box.y + box.h))
			{
				this->image = this->front_image;
				this->status = 1;
			}
			else
			{
				this->image = this->back_image;
				this->status = 0;
			}
		}
	};
}