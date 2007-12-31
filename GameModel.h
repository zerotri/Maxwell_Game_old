#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include "chipmunk/chipmunk.h"
#include "xmlParser.h"

class GameModel
{
	public:
		GameModel(cpSpace* space);
		virtual ~GameModel();
		bool loadModel(const char* _fname);
		void DrawModel();
		cpBody* getBody();
		cpShape* getShape();
	protected:
	private:
		cpShape* modelShape;
};



#endif // GAMEMODEL_H
