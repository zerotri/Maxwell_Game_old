#include "GameEntity.h"
#include "utils.h"
#include "mgame_config.h"

GameEntity::GameEntity()
{
	//ctor
}

GameEntity::~GameEntity()
{
	//dtor
}
void GameEntity::Draw(Graphics* _gfx)
{
	#if(DEBUG_MODE == DEBUG_OUTPUT_STANDARD)
		Log("Drawing Sprite at (%i, %i)",worldPos.x(), worldPos.y());
	#endif
	_gfx->DrawSurface(worldPos.x(), worldPos.y(), surface);

}
void GameEntity::SetSurface(GfxSurface _surface)
{
	surface = _surface;
}
void GameEntity::SetPos(int x, int y)
{
	worldPos.SetPoints(x,y);
}

int& GameEntityContainer::operator [] (std::string name)
{
}

GameEntity& GameEntityContainer::operator [] (int id)
{

}

void GameEntityContainer::AddEntity(GameEntity ent)
{

}

GameEntity& GameEntityContainer::CreateEntity()
{

}
