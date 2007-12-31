#include "GameWorld.h"


GameWorld::GameWorld()
{
	worldSpace = cpSpaceNew();
	worldSpace->gravity = cpv(0.0f, -900.0f);
	cpSpaceResizeStaticHash(worldSpace, 50.0f, 2000);
	cpSpaceResizeActiveHash(worldSpace, 50.0f, 50);
}

GameWorld::~GameWorld()
{
	//dtor
}
cpSpace* GameWorld::getSpace()
{
	return worldSpace;
}

