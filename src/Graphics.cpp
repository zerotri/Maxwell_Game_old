#include "Graphics.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sge.h>
unsigned int blend_add(unsigned int source, unsigned int target)
{
  unsigned int sourcer = (source >>  0) & 0xff;
  unsigned int sourceg = (source >>  8) & 0xff;
  unsigned int sourceb = (source >> 16) & 0xff;
  unsigned int targetr = (target >>  0) & 0xff;
  unsigned int targetg = (target >>  8) & 0xff;
  unsigned int targetb = (target >> 16) & 0xff;

  targetr += sourcer;
  targetg += sourceg;
  targetb += sourceb;

  if (targetr > 0xff) targetr = 0xff;
  if (targetg > 0xff) targetg = 0xff;
  if (targetb > 0xff) targetb = 0xff;

  return (targetr <<  0) |
         (targetg <<  8) |
         (targetb << 16);
}
void DrawSprite_AdditiveBlend(SDL_Surface* pSrc, SDL_Surface* pDest)
{
	int32_t _x=0, _y=0;
	//uint32_t comparison_color;
	for(_x=0;_x<pSrc->w;_x++)
	{
		for(_y=0;_y<pSrc->h;_y++)
		{
			register uint32_t src_color = sge_GetPixel(pSrc,_x,_y)&0x00ffffff;
			register uint32_t dst_color = sge_GetPixel(pDest,_x,_y)&0x00ffffff;

			//SDL_PixelFormat* format = pSrc->format;
			register unsigned int tdest = blend_add(src_color,dst_color);
			/*register unsigned int t;

			t = (src_color & format->Rmask) + (dst_color & format->Rmask);
			if(t > format->Rmask) t = format->Rmask;
			tdest |= t;

			t = (src_color & format->Gmask) + (dst_color & format->Gmask);
			if(t > format->Gmask) t = format->Gmask;
			tdest |= t;

			t = (src_color & format->Bmask) + (dst_color & format->Bmask);
			if(t > format->Bmask) t = format->Bmask;
			tdest |= t;*/

			//*dest = (unsigned short)tdest;
			_PutPixel32(pDest,_x,_y,tdest);
		}
	}
}
Graphics::Graphics()
{
	// Open a screen with the specified properties
	int width = 320;
	int height = 240;
	int bpp = 32;
	// We stored our image in RGBA32 format. We have to create a mask
	// for this format to tell SDL about our data layout.
	Uint32 rmask = 0xff000000;
	Uint32 gmask = 0x00ff0000;
	Uint32 bmask = 0x0000ff00;
	Uint32 amask = 0x000000ff;
	#if SDL_BYTEORDER == SDL_LIL_ENDIAN // OpenGL RGBA masks
		rmask = 0x000000FF;
		gmask = 0x0000FF00;
		bmask = 0x00FF0000;
		amask = 0xFF000000;
	#else
		rmask = 0xFF000000;
		gmask = 0x00FF0000;
		bmask = 0x0000FF00;
		amask = 0x000000FF;
	#endif
	_targetScreen = SDL_SetVideoMode(width, height, bpp, SDL_HWSURFACE);

	if (_targetScreen == NULL) {
			Log("[Error] Unable to set %ix%i video: %s\n", width,height, SDL_GetError());
			exit(1);
	}

	_gfxSurface = SDL_DisplayFormatAlpha(SDL_CreateRGBSurface(SDL_SWSURFACE,width, height, bpp, rmask, gmask, bmask, amask));
	if (_targetScreen == NULL)
		return;
	SDL_WM_SetCaption("MGame",NULL);
	sge_TTF_Init();
	font = sge_TTF_OpenFont("arial.ttf",10);
	bgColor = SDL_MapRGBA(_gfxSurface->format,0,0,0,255);
	fgColor = SDL_MapRGBA(_gfxSurface->format,255,255,255,255);
	sge_Update_OFF();
	sge_TTF_AAOff();
	sge_Line(_gfxSurface,0,0,32,32,fgColor);
	//sge_TTF_AA_Alpha();
}
Graphics::~Graphics()
{
	SDL_FreeSurface(_gfxSurface);
}

void Graphics::Render()
{
	//Rendering Process is as follows
	//1. Call the rendering function (if it exists)
	//2. Blit the rendering surface to the screen
	//3. Update Screen
	//4. Clear the rendering surface to the backgroud color(for next render)
    //if(_renderFunc!= NULL)_renderFunc(this);
	SDL_BlitSurface(_gfxSurface, NULL, _targetScreen, NULL);
	SDL_UpdateRect(_targetScreen, 0, 0, 0, 0);
	sge_ClearSurface(_gfxSurface, bgColor);
}
void Graphics::DrawString(int x, int y, char* format,...)
{
	char _strbuf[256];
	///create va_list and load all arguments
	va_list ap;
	va_start(ap, format);
	vsprintf(_strbuf,format, ap); /// Call vprintf
	va_end(ap); /// Cleanup the va_list
	int strpos = 0;
	int strpos_s = 0;
	float cury = y;
	char _tstr[256];
	int strAscent = sge_TTF_FontAscent(font)/2;
	int strheight = sge_TTF_FontHeight(font)-strAscent;
	while(strpos_s<256)
	{
		_tstr[strpos] = _strbuf[strpos_s++];
		if(_tstr[strpos] == '\n')
		{
			_tstr[strpos] = '\0';
			sge_tt_textout(_gfxSurface, font, _tstr, (int)x, (int)cury+strheight, fgColor, bgColor, 255);
			cury+=(strheight);
			strpos = 0;
		}else if(_tstr[strpos] == '\0')
		{
			sge_tt_textout(_gfxSurface, font, _tstr, (int)x, (int)cury+strheight, fgColor, bgColor, 255);
			break;
		}else strpos++;
	}
};
void Graphics::DrawPoint(int x, int y)
{
}
void Graphics::DrawLine(int x1, int y1, int x2, int y2)
{
}
void Graphics::DrawSurface(int x1, int y1,SDL_Surface* surf)
{
	sge_Blit(surf,_gfxSurface,0,0,x1,y1,surf->w,surf->h);
}
void Graphics::DrawSurfacePart(int x1, int y1,SDL_Surface* surf, int srcx, int srcy, int srcw, int srch)
{
	sge_Blit(surf,_gfxSurface,srcx,srcy,(int)x1,(int)y1,srcw,srch);
}
void Graphics::DrawSurfaceRect(int x1, int y1,SDL_Surface* surf, SDL_Rect* rect)
{
	//sge_Blit(surf,_gfxSurface,srcx,srcy,(int)x1,(int)y1,srcw,srch);
	SDL_Rect dstRct = {x1,y1,rect->w,rect->w};
	SDL_BlitSurface(surf, rect, _gfxSurface, &dstRct);
	//DrawSprite_AdditiveBlend(surf, _gfxSurface);
}

void Graphics::SetBGColor(int r, int g, int b, int a)
{
	bgColor = SDL_MapRGBA(_gfxSurface->format,r,g,b,a);
}
void Graphics::SetFGColor(int r, int g, int b, int a)
{
	fgColor = SDL_MapRGBA(_gfxSurface->format,r,g,b,a);
}
void Graphics::SetRenderFunc(renderCallback renderFunc)
{
	_renderFunc = renderFunc;
}
