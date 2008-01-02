#include "GameAnimation.h"
#include "utils.h"
extern HGE* hge;

GameAnimation::GameAnimation()
{
}

GameAnimation::~GameAnimation()
{
}
void GameAnimation::update(float updateTime)
{
	if(baseAnimation == NULL)
		return;
	if(baseAnimation->lpNext != NULL)
	{
		ANIM *tAnimation = NULL;
		float tDeltaTime = updateTime;
		tDeltaTime -= fTimeLeft;
		fTimeLeft -= updateTime;
		//bool animUpd = false;
		if(fTimeLeft<0)
		{
			tAnimation = baseAnimation->lpNext;
			baseAnimation = tAnimation;
			fTimeLeft += baseAnimation->fAnimSpeed;
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
void GameAnimation::drawCurrentFrame(int x, int y, HTEXTURE drawTexture)
{
	if(baseAnimation == NULL)
		return;
	int iMaxPrims = 0;
	hgeVertex *v;
	if(drawTexture != 0)
	{
		v = hge->Gfx_StartBatch(HGEPRIM_QUADS, drawTexture, BLEND_DEFAULT, &iMaxPrims);
	}
	else
	{
		v = hge->Gfx_StartBatch(HGEPRIM_QUADS, baseAnimation->hTex, BLEND_DEFAULT, &iMaxPrims);
	}
	SET_XY(v[0],x,y);
	SET_XY(v[1],x+128,y);
	SET_XY(v[2],x+128,y+128);
	SET_XY(v[3],x,y+128);
	SET_TXY(v[0],	baseAnimation->uLeft,
					baseAnimation->uTop);
	v[0].col = 0xFFFFFFFF;
	SET_TXY(v[1],	baseAnimation->uRight,
					baseAnimation->uTop);
	v[1].col = 0xFFFFFFFF;
	SET_TXY(v[2],	baseAnimation->uRight,
					baseAnimation->uBottom);
	v[2].col = 0xFFFFFFFF;
	SET_TXY(v[3],	baseAnimation->uLeft,
					baseAnimation->uBottom);
	v[3].col = 0xFFFFFFFF;
	hge->Gfx_FinishBatch(1);
}
void GameAnimation::setAnimation(ANIM* baseAnim)
{
	baseAnimation = baseAnim;
	fTimeLeft = baseAnimation->fAnimSpeed;
}
