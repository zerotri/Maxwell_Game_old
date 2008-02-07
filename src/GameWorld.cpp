#include "GameWorld.h"
#include <math.h>
#include "utils.h"
#define MAP_W 8
#define MAP_H 8
typedef struct TileStruct_Type{
	unsigned int x;
	unsigned int y;
	unsigned int w;
	unsigned int h;
}TileStruct;
unsigned char tilemap[MAP_W*MAP_H] = {
	3,	4,	4,	4,	4,	4,	4,	5,
	6,	7,	7,	7,	7,	7,	7,	8,
	6,	7,	7,	7,	7,	7,	7,	8,
	6,	7,	7,	7,	7,	7,	7,	8,
	6,	7,	7,	7,	7,	7,	7,	8,
	6,	7,	7,	7,	7,	7,	7,	8,
	6,	7,	7,	7,	7,	7,	7,	8,
	9,	10,	10,	10,	10,	10,	10,	11};
TileStruct tileset[] = {
	{0,		0,	32,	32},
	{32,	0,	32,	32},
	{64,	0,	32,	32},
	{0,		32,	32,	32},
	{32,	32,	32,	32},
	{64,	32,	32,	32},
	{0,		64,	32,	32},
	{32,	64,	32,	32},
	{64,	64,	32,	32},
	{0,		96,	32,	32},
	{32,	96,	32,	32},
	{64,	96,	32,	32},
};
GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
	//dtor
}
void GameWorld::setGfx(Graphics* gfx)
{
	_gfx = gfx;
}
void GameWorld::DrawWorld(GfxSurface surface)
{
	unsigned int _x, _y;
	unsigned int surface_w = _gfx->Surface_GetWidth(surface);
	unsigned int tile_x, tile_y, tile;
	Rect tileRect = {0,0,32,32};
	//Log("Drawing Tileset");
	for(_x=0;_x<MAP_W;_x++)
	{
		for(_y=0;_y<MAP_H;_y++)
		{
			tile = tilemap[(_y*MAP_W) + _x];
			tile_x = (tile<<5) % surface_w;
			tile_y = 0;
			if(tile!=0)
			{
				 tile_y = ((tile<<5)/surface_w)<<5;
			}
			tileRect.x = tile_x;
			tileRect.y = tile_y;
			_gfx->DrawSurfaceRect(_x<<5, _y<<5,surface, &tileRect);
		}
	}
	//Log("Tiles Drawn [%i,%i]",_x, _y);
}
void GameWorld::DrawTile(int dx, int dy, unsigned char tile, GfxSurface surface)
{
	unsigned int surface_w = (_gfx->Surface_GetWidth(surface))>>5;
	unsigned int tile_x = tile % surface_w;
	unsigned int tile_y = 0;
	if(tile!=0)
	{
		 tile_y = (tile<<5)/(surface_w<<5);
	}
	_gfx->DrawSurfacePart(dx, dy,surface, tile_x, tile_y<<5, 32, 32);
}


