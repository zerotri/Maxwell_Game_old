#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Graphics.h"


class GameWorld
{
	public:
		GameWorld();
		~GameWorld();
		void DrawWorld(SDL_Surface* surface);
		void DrawTile(int dx, int dy, unsigned char tile, SDL_Surface* surface);
		void setGfx(Graphics* gfx);
	protected:
	private:
		Graphics* _gfx;
};



#endif // GAMEWORLD_H
