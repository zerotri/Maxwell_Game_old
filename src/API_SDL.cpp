#include "API_SDL.h"
#include <sdl.h>
#include <sdl_image.h>
#include "utils.h"

API_SDL::API_SDL()
{
	/* Initialize SDL */
	Log("Initializing API: [SDL]");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
			fprintf(stderr, "Unable to init SDL: %s\n",
					SDL_GetError());
			exit(1);
	}
}

API_SDL::~API_SDL()
{
	SDL_Quit();
}
void API_SDL::Sys_Sleep(int count)
{
	SDL_Delay(count);
}
int API_SDL::Sys_GetTicks()
{
	return SDL_GetTicks();
};
void API_SDL::Gfx_Initialize()
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
	if (_gfxSurface == NULL)
		return;
	SDL_WM_SetCaption("MGame",NULL);
	sge_TTF_Init();
	font = sge_TTF_OpenFont("arial.ttf",10);
	sge_Update_OFF();
	sge_TTF_AAOff();
	//sge_TTF_AA_Alpha();
}
void API_SDL::Gfx_Render()
{
	SDL_BlitSurface((SDL_Surface*)_gfxSurface, NULL, (SDL_Surface*)_targetScreen, NULL);
	SDL_UpdateRect((SDL_Surface*)_targetScreen, 0, 0, 0, 0);
};
void API_SDL::Gfx_Destroy()
{
	if (_gfxSurface == NULL)
		return;
	SDL_FreeSurface((SDL_Surface*)_gfxSurface);
};
void API_SDL::Gfx_DrawString(int x, int y, char* format, unsigned int bgcolor, unsigned int fgcolor)
{
	int strpos = 0;
	int strpos_s = 0;
	float cury = y;
	char _tstr[256];
	int strAscent = sge_TTF_FontAscent(font)/2;
	int strheight = sge_TTF_FontHeight(font)-strAscent;
	while(strpos_s<256)
	{
		_tstr[strpos] = format[strpos_s++];
		if(_tstr[strpos] == '\n')
		{
			_tstr[strpos] = '\0';
			sge_tt_textout((SDL_Surface*)_gfxSurface, font, _tstr, (int)x, (int)cury+strheight, fgcolor, bgcolor, 255);
			cury+=(strheight);
			strpos = 0;
		}else if(_tstr[strpos] == '\0')
		{
			sge_tt_textout((SDL_Surface*)_gfxSurface, font, _tstr, (int)x, (int)cury+strheight, fgcolor, bgcolor, 255);
			break;
		}else strpos++;
	}
};
void API_SDL::Gfx_DrawPoint(int x, int y)
{
};
void API_SDL::Gfx_DrawLine(int x1, int y1, int x2, int y2)
{
};
void API_SDL::Gfx_DrawSurface(int x1, int y1,GfxSurface surf)
{
	sge_Blit(	(SDL_Surface*)surf,
				(SDL_Surface*)_gfxSurface,
				0,0,x1,y1,
				Surface_GetWidth(surf),
				Surface_GetHeight(surf));
};
void API_SDL::Gfx_DrawSurfaceRect(int x1, int y1,GfxSurface surf, Rect* rect)
{
	//sge_Blit(surf,_gfxSurface,srcx,srcy,(int)x1,(int)y1,srcw,srch);
	SDL_Rect srcRct = {rect->x,rect->y,((SDL_Surface*)surf)->w,((SDL_Surface*)surf)->h};
	SDL_Rect dstRct = {x1,y1,rect->w,rect->h};
	SDL_BlitSurface((SDL_Surface*)surf, &srcRct, (SDL_Surface*)_gfxSurface, &dstRct);
};
void API_SDL::Gfx_ClearScreen(unsigned int color)
{
	sge_ClearSurface((SDL_Surface*)_gfxSurface, color);
};
unsigned int API_SDL::Gfx_MakeColor(int r, int g, int b, int a)
{
	return SDL_MapRGBA(((SDL_Surface*)_gfxSurface)->format,r,g,b,a);
};
void API_SDL::Gfx_GetRGBA(unsigned int col, int* r, int* g, int* b, int* a)
{
	SDL_GetRGBA(col,((SDL_Surface*)_gfxSurface)->format,
				(unsigned char*)r,
				(unsigned char*)g,
				(unsigned char*)b,
				(unsigned char*)a);
};
GfxSurface API_SDL::Surface_Create(int width, int height)
{
	return NULL;
};
GfxSurface API_SDL::Surface_Load(char* fname)
{
	return (GfxSurface)SDL_DisplayFormatAlpha(IMG_Load(fname));
};
int API_SDL::Surface_Free(GfxSurface surface)
{
	SDL_FreeSurface((SDL_Surface*)surface);
	return true;
};
int API_SDL::Surface_GetWidth(GfxSurface surface)
{
	return ((SDL_Surface*)surface)->w;
};
int API_SDL::Surface_GetHeight(GfxSurface surface)
{
	return ((SDL_Surface*)surface)->h;
};
int API_SDL::Surface_GetBitsPerPixel(GfxSurface surface)
{
	return ((SDL_Surface*)surface)->pitch;
};
