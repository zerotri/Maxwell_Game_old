#include "GameAnimation.h"
#include "utils.h"
Graphics* globalGraphics = 0;

GameAnimation::GameAnimation()
{
}

GameAnimation::~GameAnimation()
{
}
void GameAnimation::update(time_type updateTime)
{
	if(baseAnimation == NULL)
		return;
	if(baseAnimation->lpNext != NULL)
	{
		ANIM *tAnimation = NULL;
		time_type tDeltaTime = updateTime;
		tDeltaTime -= fTimeLeft;
		fTimeLeft -= updateTime;
		//bool animUpd = false;
		if(fTimeLeft<0)
		{
			tAnimation = baseAnimation->lpNext;
			baseAnimation = tAnimation;
			fTimeLeft += (time_type)(baseAnimation->fAnimSpeed*1000.0f);
		}
		/*if(fTimeLeft<0)
			animUpd = true;
		while(animUpd)
		{
			tAnimation = baseAnimation->lpNext;
			baseAnimation = tAnimation;
			fTimeLeft = baseAnimation->fAnimSpeed;
			if(tDeltaTime>0)
			{
				tDeltaTime -= fTimeLeft;
				fTimeLeft -= tDeltaTime;
				animUpd = true;
			}
			else animUpd = false;
		}*/
	}
}
void GameAnimation::drawCurrentFrame(int x, int y, GfxSurface drawTexture)
{
	if(baseAnimation == NULL)
		return;
	if(drawTexture != 0)
	{
		gfx->DrawSurface(x,y,drawTexture);
	}
	else
	{
		gfx->DrawSurface(x,y,baseAnimation->pSurf);
	}
}
void GameAnimation::setAnimation(ANIM* baseAnim)
{
	baseAnimation = baseAnim;
	fTimeLeft = (time_type)(baseAnimation->fAnimSpeed*1000.0f);
}
void GameAnimation::setGraphics(Graphics* _gfx)
{
	gfx = _gfx;
}
