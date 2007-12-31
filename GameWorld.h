#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "GameModel.h"
#include "chipmunk/chipmunk.h"


class GameWorld
{
	public:
		GameWorld();
		virtual ~GameWorld();
		cpSpace* getSpace();
	protected:
	private:
		cpSpace *worldSpace;
};



#endif // GAMEWORLD_H
