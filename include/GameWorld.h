#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Graphics.h"
typedef struct gameTile_TYPE{
}gameTile;
class GameWorld
{
	public:
		GameWorld();
		~GameWorld();
		void DrawWorld(GfxSurface surface);
		void DrawTile(int dx, int dy, unsigned char tile, GfxSurface surface);
		void setGfx(Graphics* gfx);
	protected:
	private:
		Graphics* _gfx;
};



#endif // GAMEWORLD_H
