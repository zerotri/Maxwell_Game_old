#ifndef GAMEANIMATION_H
#define GAMEANIMATION_H
#include <sdl.h>
#include "Graphics.h"

typedef struct ANIM_type
{
	SDL_Surface* pSurf;
	float uTop;
	float uLeft;
	float uBottom;
	float uRight;
	float fAnimSpeed;
	ANIM_type *lpNext;  // next frame of animation
}ANIM;

class GameAnimation
{
	public:
		GameAnimation();
		~GameAnimation();
		void update(float updateTime);
		void drawCurrentFrame(int x, int y, SDL_Surface* drawTexture = 0);
		void setAnimation(ANIM* baseAnim);
		void setGraphics(Graphics* _gfx);
	protected:
	private:
	ANIM *baseAnimation;
	Graphics* gfx;
	float fTimeLeft;
};



#endif // GAMEANIMATION_H
