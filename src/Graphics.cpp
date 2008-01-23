#include "Graphics.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
Graphics::Graphics()
{
}
Graphics::~Graphics()
{
}

void Graphics::Render()
{
	//Rendering Process is as follows
	//1. Call the rendering function (if it exists)
	//2. Blit the rendering surface to the screen
	//3. Update Screen
	//4. Clear the rendering surface to the backgroud color(for next render)
	if(_renderFunc!= NULL)_renderFunc->_Render();
	api->Gfx_Render();
	api->Gfx_ClearScreen(bgColor);
}
void Graphics::DrawString(int x, int y, char* format,...)
{
	char _strbuf[256];
	///create va_list and load all arguments
	va_list ap;
	va_start(ap, format);
	vsprintf(_strbuf,format, ap); /// Call vprintf
	va_end(ap); /// Cleanup the va_list
	api->Gfx_DrawString(x,y,_strbuf,bgColor,fgColor);
};
void Graphics::DrawPoint(int x, int y)
{
}
void Graphics::DrawLine(int x1, int y1, int x2, int y2)
{
}
void Graphics::DrawSurface(int x1, int y1,GfxSurface surf)
{
	api->Gfx_DrawSurface(x1,y1,surf);
}
void Graphics::DrawSurfacePart(int x1, int y1,GfxSurface surf, int srcx, int srcy, int srcw, int srch)
{
	Rect dstRct = {x1,y1,srcw,srch};
	api->Gfx_DrawSurfaceRect(x1,y1,surf,&dstRct);
	//sge_Blit(surf,_gfxSurface,srcx,srcy,(int)x1,(int)y1,srcw,srch);
}
void Graphics::DrawSurfaceRect(int x1, int y1,GfxSurface surf, Rect* rect)
{
	//sge_Blit(surf,_gfxSurface,srcx,srcy,(int)x1,(int)y1,srcw,srch);
	Rect dstRct = {x1,y1,rect->w,rect->h};
	//SDL_BlitSurface(surf, rect, _gfxSurface, &dstRct);
	api->Gfx_DrawSurfaceRect(x1,y1,surf,&dstRct);
	//DrawSprite_AdditiveBlend(surf, _gfxSurface);
}
/*void Graphics::DrawAnimation(int x, int y, GameAnimation* anim)
{
	if(anim == NULL)
		return;
	if(anim->baseAnimation == NULL)
		return;
	DrawSurface(x,y,anim->baseAnimation->pSurf);
}*/

void Graphics::SetBGColor(int r, int g, int b, int a)
{
	bgColor = api->Gfx_MakeColor(r,g,b,a);
}
void Graphics::SetFGColor(int r, int g, int b, int a)
{
	fgColor = api->Gfx_MakeColor(r,g,b,a);
}
void Graphics::SetAPI(API_Base* _api)
{
	api = _api;
	api->Gfx_Initialize();
	bgColor = api->Gfx_MakeColor(0,0,0,255);
	fgColor = api->Gfx_MakeColor(255,255,255,255);
}
void Graphics::SetRenderFunc(RenderCallback* renderFunc)
{
	_renderFunc = renderFunc;
}
int Graphics::Surface_GetWidth(GfxSurface surface)
{
	return api->Surface_GetWidth(surface);
}
int Graphics::Surface_GetHeight(GfxSurface surface)
{
	return api->Surface_GetHeight(surface);
}
int Graphics::Surface_GetBitsPerPixel(GfxSurface surface)
{
	return api->Surface_GetBitsPerPixel(surface);
}
