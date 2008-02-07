#include "API_SDL.h"
#include <sdl.h>
#include <sdl_image.h>
#include "utils.h"

API_SDL::API_SDL()
{
	/* Initialize SDL */
	putenv("SDL_VIDEODRIVER=directx");
	Log("Initializing API: [SDL]");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
			fprintf(stderr, "Unable to init SDL: %s\n",
					SDL_GetError());
			exit(1);
	}
	keys = SDL_GetKeyState(NULL);
}

API_SDL::~API_SDL()
{
	SDL_Quit();
}
void API_SDL::Sys_Sleep(s32 count)
{
	SDL_Delay(count);
}
s32 API_SDL::Sys_GetTicks()
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
void API_SDL::Gfx_DrawString(s32 x, s32 y, c_string_p format, u32 bgcolor, u32 fgcolor)
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
void API_SDL::Gfx_DrawPoint(s32 x, s32 y, u32 color)
{
};
void API_SDL::Gfx_DrawLine(s32 x1, s32 y1, s32 x2, s32 y2, u32 color)
{
};
void API_SDL::Gfx_DrawSurface(s32 x1, s32 y1,GfxSurface surf)
{
	/*SDL_Surface* _tsurf = (SDL_Surface*) surf;
	SDL_Surface* _Gsurf = (SDL_Surface*) _gfxSurface;
	Rect clipRect = {
		(x1>0) ? x1 : 0,
		(y1>0) ? y1 : 0,
		(_tsurf->w>_Gsurf->w) ? _tsurf->w : _Gsurf->w,
		(_tsurf->h>_Gsurf->h) ? _tsurf->h : _Gsurf->h};
	for()
	for()
	{
		int ialpha = 256 - *alpha; //inverse alpha
*dest = (RMask & (((*source & RMask) * *alpha +
           (*dest & RMask) * ialpha) >>8)) |
        (GMask & (((*source & GMask) * *alpha +
           (*dest & GMask) * ialpha) >>8)) |
        (BMask & (((*source & BMask) * *alpha +
           (*dest & BMask) * ialpha) >>8));
	}*/
	sge_Blit(	(SDL_Surface*)surf,
				(SDL_Surface*)_gfxSurface,
				0,0,x1,y1,
				Surface_GetWidth(surf),
				Surface_GetHeight(surf));
};
void API_SDL::Gfx_DrawSurfaceAlpha(s32 x1, s32 y1,GfxSurface surf, s32 alpha)
{
    sge_BlitTransparent(	(SDL_Surface*)surf,
                            (SDL_Surface*)_gfxSurface,
				            0,0,x1,y1,
                            Surface_GetWidth(surf),
                            Surface_GetHeight(surf),
                            0xFF00FF00, alpha);
};
void API_SDL::Gfx_DrawSurfaceRect(s32 x1, s32 y1,GfxSurface surf, Rect* rect)
{
	//sge_Blit(surf,_gfxSurface,srcx,srcy,(int)x1,(int)y1,srcw,srch);
	SDL_Rect srcRct = {rect->x,rect->y,((SDL_Surface*)surf)->w,((SDL_Surface*)surf)->h};
	SDL_Rect dstRct = {x1,y1,rect->w,rect->h};
	SDL_BlitSurface((SDL_Surface*)surf, &srcRct, (SDL_Surface*)_gfxSurface, &dstRct);
};
void API_SDL::Gfx_ClearScreen(u32 color)
{
	sge_ClearSurface((SDL_Surface*)_gfxSurface, color);
};
u32	API_SDL::Gfx_MakeColor(u8 r, u8 g, u8 b, u8 a)
{
	return SDL_MapRGBA(((SDL_Surface*)_gfxSurface)->format,r,g,b,a);
};
void API_SDL::Gfx_GetRGBA(u32 col, u8* r, u8* g, u8* b, u8* a)
{
	SDL_GetRGBA(col,((SDL_Surface*)_gfxSurface)->format, r, g, b, a);
};
GfxSurface API_SDL::Surface_Create(s32 width, s32 height)
{
	return NULL;
};
GfxSurface API_SDL::Surface_Load(c_string_p fname)
{
	return (GfxSurface)SDL_DisplayFormatAlpha(IMG_Load(fname));
};
s32 API_SDL::Surface_Free(GfxSurface surface)
{
	SDL_FreeSurface((SDL_Surface*)surface);
	return true;
};
s32 API_SDL::Surface_GetWidth(GfxSurface surface)
{
	return ((SDL_Surface*)surface)->w;
};
s32 API_SDL::Surface_GetHeight(GfxSurface surface)
{
	return ((SDL_Surface*)surface)->h;
};
s32 API_SDL::Surface_GetBitsPerPixel(GfxSurface surface)
{
	return ((SDL_Surface*)surface)->pitch;
};
s32 API_SDL::Surface_GetMemoryUsage(GfxSurface surface)
{
	SDL_Surface* _tsurf = (SDL_Surface*)surface;
	return (_tsurf->w*_tsurf->h*(_tsurf->pitch/8))+sizeof(SDL_Surface);
};
s32 API_SDL::Input_GetEvent(InputEvent* evt)
{
	SDL_Event event;
	int event_number = SDL_PollEvent(&event);
	if(event_number==0)
		return false;
	switch(event.type)
	{
		case SDL_KEYDOWN:
			evt->type = InputEvent::Evt_KeyPress;
			evt->key.keyboard_key = event.key.keysym.sym;
			evt->key.keyboard_flag = event.key.keysym.mod;
			evt->key.keyboard_char = event.key.keysym.scancode;
		break;
		case SDL_KEYUP:
			evt->type = InputEvent::Evt_KeyRelease;
			evt->key.keyboard_key = event.key.keysym.sym;
			evt->key.keyboard_flag = event.key.keysym.mod;
			evt->key.keyboard_char = event.key.keysym.scancode;
		break;
		case SDL_MOUSEBUTTONDOWN:
			evt->type = InputEvent::Evt_MousePress;
			evt->mouse.button = event.button.button;
			evt->mouse.x = event.button.x;
			evt->mouse.y = event.button.y;
		break;
		case SDL_MOUSEBUTTONUP:
			if(event.button.button == SDL_BUTTON_WHEELUP)
			{
				evt->type = InputEvent::Evt_MouseWheel;
				evt->mouse.degrees = 1;
				evt->mouse.x = event.button.x;
				evt->mouse.y = event.button.y;
			}
			else if(event.button.button == SDL_BUTTON_WHEELDOWN)
			{
				evt->type = InputEvent::Evt_MouseWheel;
				evt->mouse.degrees = -1;
				evt->mouse.x = event.button.x;
				evt->mouse.y = event.button.y;
			}
			else
			{
				evt->type = InputEvent::Evt_MouseRelease;
				evt->mouse.button = event.button.button;
				evt->mouse.x = event.button.x;
				evt->mouse.y = event.button.y;
			}
		break;
		case SDL_MOUSEMOTION:
				evt->type = InputEvent::Evt_MouseMove;
				evt->mouse.x = event.motion.x;
				evt->mouse.y = event.motion.y;
		break;
	}
	return event_number;
};
bool API_SDL::Input_GetKeyState(u8 key)
{
	return (keys[key] == 1);
};
