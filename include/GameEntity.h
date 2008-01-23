#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <vector.h>
#include <sdl.h>
#include <map>
#include <string>
#include "Graphics.h"

class GameEntity
{
	public:
		GameEntity();
		~GameEntity();
		void Draw(Graphics* _gfx);
		void SetSurface(GfxSurface _surface);
		void SetPos(int x, int y);
	protected:
	private:
		long long int entityID;
		long long int mapID;
		GfxSurface surface;
		Vector2D<int> worldPos;
};

class GameEntityContainer{
	int& operator [] (std::string name);
	GameEntity& operator [] (int id);
	void AddEntity(GameEntity ent);
	GameEntity& CreateEntity();
	public:
		std::map<int, GameEntity> entityMap;
};


#endif // GAMEENTITY_H
