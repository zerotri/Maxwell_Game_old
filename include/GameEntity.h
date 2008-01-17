#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <vector.h>
#include <sdl.h>

class GameEntity
{
	public:
		GameEntity();
		~GameEntity();
	protected:
	private:
		SDL_Surface* _surface;
		Vector2D _vec;
};



#endif // GAMEENTITY_H
