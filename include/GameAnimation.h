#ifndef GAMEANIMATION_H
#define GAMEANIMATION_H
#include "main.h"

typedef struct ANIM_type
{
	GfxSurface pSurf;
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
		void update(time_type updateTime);
		void drawCurrentFrame(int x, int y, GfxSurface drawTexture = 0);
		void setAnimation(ANIM* baseAnim);
		void setGraphics(Graphics* _gfx);
	protected:
	private:
	ANIM *baseAnimation;
	time_type fTimeLeft;
	Graphics* gfx;
};



#endif // GAMEANIMATION_H
