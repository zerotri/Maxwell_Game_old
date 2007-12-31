#ifndef GAMEANIMATION_H
#define GAMEANIMATION_H
#include <hge.h>

typedef struct ANIM_type
{
	HTEXTURE hTex;
	float uTop;
	float uLeft;
	float uBottom;
	float uRight;
	float fAnimSpeed;
	ANIM_type *lpNext;  // next frame of animation
}ANIM, FAR* LPANIM;

class GameAnimation
{
	public:
		GameAnimation();
		~GameAnimation();
		void update(float updateTime);
		void drawCurrentFrame(int x, int y, HTEXTURE drawTexture = 0);
		void setAnimation(ANIM* baseAnim);
	protected:
	private:
	ANIM *baseAnimation;
	float fTimeLeft;
};



#endif // GAMEANIMATION_H
