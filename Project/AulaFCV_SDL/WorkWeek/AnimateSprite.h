#ifndef ANIMATESPRITE_H
#define ANIMATESPRITE_H
#endif

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <iostream>

#include "GameFunc.h";

namespace sprite{
	using namespace std;

	class AnimateSprite
	{
	public:
		AnimateSprite(
			string pathImg,
			int framesLimitX, int framesLimitY);
		~AnimateSprite();
		bool SetEffect(char* pathEffectAudio);
		void Control(SDL_Event event);
		void Render();
	private:
		Mix_Chunk* effectAttack;
		SDL_Surface* spriteSheet;
		bool modeAttack = false;
		int posX = 0, posY = 0;
		int frameX = 0, frameY = 0;
		int frameLimitX = 0, frameLimitY = 0;
		int frameW = 0, frameH = 0;
		Uint32 lastTimeMove = 0, deltaTime = 70;
	};

	AnimateSprite::AnimateSprite(
		string pathImg,
		int fLimitX, int fLimitY)
	{

		spriteSheet = LoadImage(pathImg);

		if (spriteSheet != NULL){
			if (fLimitX > 0 && fLimitY > 0)
			{
				this->frameLimitX = fLimitX;
				this->frameLimitY = fLimitY;

				SDL_Rect rc = spriteSheet->clip_rect;
				frameW = rc.w / fLimitX;
				frameH = rc.h / fLimitY;
			}
		}
	};

	AnimateSprite::~AnimateSprite()
	{
		Mix_FreeChunk(effectAttack);
		SDL_FreeSurface(spriteSheet);
	};

	void AnimateSprite::Control(SDL_Event event){
		Uint32 now = SDL_GetTicks();
		int posXtemp = posX, posYtemp = posY;
		bool action = false;

		if (now - lastTimeMove > deltaTime){
			lastTimeMove = now;
			action = true;
		}

		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				posYtemp -= 10;
				frameY = 1;
				if (action)
					frameX++;
				break;
			case SDLK_DOWN:
				posYtemp += 10;
				frameY = 0;
				if (action)
					frameX++;
				break;
			case SDLK_LEFT:
				posXtemp -= 10;
				frameY = 2;
				if (action)
					frameX++;
				break;
			case SDLK_RIGHT:
				posXtemp += 10;
				frameY = 3;
				if (action)
					frameX++;
				break;
			case SDLK_a:
				frameY = 4;
				if (action)
					frameX++;
				if (!modeAttack){
					Mix_PlayChannel(-1, effectAttack, 0);
					modeAttack = true;
				}
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
				case SDLK_UP:
					frameX = 0;
					break;
				case SDLK_DOWN:
					frameX = 0;
					break;
				case SDLK_LEFT:
					frameX = 0;
					break;
				case SDLK_RIGHT:
					frameX = 0;
					break;
				case SDLK_a:
					frameX = 0;
					frameY = 0;
					modeAttack = false;
					break;
				default:
					break;
				}
			break;
		default:
			break;
		}

		if (frameX >= frameLimitX)
		{
			frameX = 0;
		}

		// Limita o personagem a ficar dentro da tela
		if ((posXtemp < sWidth - frameW) &&
			posXtemp > 0)
		{
			posX = posXtemp;
		}

		if ((posYtemp < sHeight - frameH) &&
			posYtemp > 0)
		{
			posY = posYtemp;
		}
	};

	void AnimateSprite::Render(){
		SDL_Rect rcSprite;
		SDL_Rect rcSrc;
		rcSprite.w = frameW;
		rcSprite.h = frameH;
		rcSprite.x = frameX * frameW;
		rcSprite.y = frameY * frameW;

		rcSrc.x = this->posX;
		rcSrc.y = this->posY;

		SDL_BlitSurface(this->spriteSheet,
			&rcSprite,
			gSurface,
			&rcSrc);
	}

	bool AnimateSprite::SetEffect(char* pathEffectAudio){
		effectAttack = LoadEffect(pathEffectAudio);
		if (effectAttack == NULL)
			return false;
		return true;
	}
}

