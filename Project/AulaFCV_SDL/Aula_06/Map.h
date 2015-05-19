#ifndef MAP_H
#define MAP_H
#endif

#include <SDL.h>
#include <SDL_image.h>

#include "Funcs.h"

using namespace std;

namespace maps
{
	int gMap[15][20] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 2, 2, 2, 2, 1, 0, 0, 0, 0, 1, 2, 2, 2, 2, 1, 0, 0 },
		{ 0, 0, 1, 2, 2, 2, 2, 1, 0, 0, 0, 0, 1, 2, 2, 2, 2, 1, 0, 0 },
		{ 0, 0, 1, 1, 1, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 0, 0 },
		{ 0, 0, 0, 1, 1, 2, 2, 2, 0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 0, 0 },
		{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	class MyMap
	{
	public:
		MyMap();
		~MyMap();
		void RenderMap(SDL_Surface* _surface);
		void SetMap();

	private:
		SDL_Surface* img[3];

	};

	MyMap::MyMap()
	{
		img[0] = LoadImage("D:/Faculdade/media/image/tile/ground.png");
		img[1] = LoadImage("D:/Faculdade/media/image/tile/grass.png");
		img[2] = LoadImage("D:/Faculdade/media/image/tile/water.png");
	}

	MyMap::~MyMap()
	{
	}

	void MyMap::RenderMap(SDL_Surface* _surface){
		SDL_Rect tile;
		int k = -1;
		tile.h = 32;
		tile.w = 32;
		for (int i = 0; i < SCREEN_WIDTH; i+=tile.w)
		{
			for (int j = 0; j < SCREEN_HEIGHT; j+=tile.h)
			{
				k = gMap[j / tile.h][i / tile.w];
				tile.x = i;
				tile.y = j;
				SDL_BlitSurface(img[k], 0, _surface, &tile);
			}

		}
	}
}

