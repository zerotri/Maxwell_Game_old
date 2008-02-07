#include "API_HGE.h"
#include "utils.h"
SysCallBack* _sysCB;
bool _SysFrameFunction();
bool _SysRenderFunction();

API_HGE::API_HGE()
{
	/* Initialize SDL */
	Log("Initializing API: [HGE]");
	hge = hgeCreate(HGE_VERSION);
}

API_HGE::~API_HGE()
{
	hge->Release();
}
void API_HGE::Sys_Sleep(s32 count)
{
	//hge->Timer_(count);
}
s32 API_HGE::Sys_GetTicks()
{
	return hge->Timer_GetTime();
};
s32 API_HGE::Sys_GetDelta()
{
	return (time_type)(hge->Timer_GetDelta()*1000.0f);
};
bool API_HGE::Sys_OverloadFuncs()
{
	return true;
};
void API_HGE::Sys_Run()
{
	_sysCB = _sysCallback;
	hge->System_Start();
	return;
}
void API_HGE::Gfx_Initialize()
{
	// Open a screen with the specified properties
	int width = 320;
	int height = 240;
	int bpp = 32;
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_TITLE, "MGame");
	hge->System_SetState(HGE_SCREENWIDTH, width);
	hge->System_SetState(HGE_SCREENHEIGHT, height);
	hge->System_SetState(HGE_FRAMEFUNC, _SysFrameFunction);
	hge->System_SetState(HGE_RENDERFUNC, _SysRenderFunction);

	if(!hge->System_Initiate())
	{
		Log("Error Initializing HGE: '%s'", hge->System_GetErrorMessage());
	}
}
void API_HGE::Gfx_Render()
{
	/*SDL_BlitSurface((SDL_Surface*)_gfxSurface, NULL, (SDL_Surface*)_targetScreen, NULL);
	SDL_UpdateRect((SDL_Surface*)_targetScreen, 0, 0, 0, 0);*/
};
void API_HGE::Gfx_Destroy()
{
	hge->System_Shutdown();
};
void API_HGE::Gfx_DrawString(s32 x, s32 y, c_string_p format, u32 bgcolor, u32 fgcolor)
{
	int strpos = 0;
	int strpos_s = 0;
	float cury = y;
	char _tstr[256];
	/*int strAscent = sge_TTF_FontAscent(font)/2;
	int strheight = sge_TTF_FontHeight(font)-strAscent;
	while(strpos_s<256)
	{
		_tstr[strpos] = format[strpos_s++];
		if(_tstr[strpos] == '\n')
		{
			_tstr[strpos] = '\0';
			//sge_tt_textout((SDL_Surface*)_gfxSurface, font, _tstr, (int)x, (int)cury+strheight, fgcolor, bgcolor, 255);
			cury+=(strheight);
			strpos = 0;
		}else if(_tstr[strpos] == '\0')
		{
			//sge_tt_textout((SDL_Surface*)_gfxSurface, font, _tstr, (int)x, (int)cury+strheight, fgcolor, bgcolor, 255);
			break;
		}else strpos++;
	}*/
};
void API_HGE::Gfx_DrawPoint(s32 x, s32 y, u32 color)
{
};
void API_HGE::Gfx_DrawLine(s32 x1, s32 y1, s32 x2, s32 y2, u32 color)
{
};
void API_HGE::Gfx_DrawSurface(s32 x1, s32 y1,GfxSurface surf)
{
	/*sge_Blit(	(SDL_Surface*)surf,
				(SDL_Surface*)_gfxSurface,
				0,0,x1,y1,
				Surface_GetWidth(surf),
				Surface_GetHeight(surf));*/
};
void API_HGE::Gfx_DrawSurfaceAlpha(s32 x1, s32 y1,GfxSurface surf, s32 alpha)
{
    /*sge_BlitTransparent(	(SDL_Surface*)surf,
                            (SDL_Surface*)_gfxSurface,
				            0,0,x1,y1,
                            Surface_GetWidth(surf),
                            Surface_GetHeight(surf),
                            0xFF00FF00, alpha);*/
};
void API_HGE::Gfx_DrawSurfaceRect(s32 x1, s32 y1,GfxSurface surf, Rect* rect)
{
	/*SDL_Rect srcRct = {rect->x,rect->y,((SDL_Surface*)surf)->w,((SDL_Surface*)surf)->h};
	SDL_Rect dstRct = {x1,y1,rect->w,rect->h};
	SDL_BlitSurface((SDL_Surface*)surf, &srcRct, (SDL_Surface*)_gfxSurface, &dstRct);*/
};
void API_HGE::Gfx_ClearScreen(u32 color)
{
	hge->Gfx_Clear(color);
	//sge_ClearSurface((SDL_Surface*)_gfxSurface, color);
};
u32	API_HGE::Gfx_MakeColor(u8 r, u8 g, u8 b, u8 a)
{
	//return SDL_MapRGBA(((SDL_Surface*)_gfxSurface)->format,r,g,b,a);
};
void API_HGE::Gfx_GetRGBA(u32 col, u8* r, u8* g, u8* b, u8* a)
{
	//SDL_GetRGBA(col,((SDL_Surface*)_gfxSurface)->format, r, g, b, a);
};
GfxSurface API_HGE::Surface_Create(s32 width, s32 height)
{
	return NULL;
};
GfxSurface API_HGE::Surface_Load(c_string_p fname)
{
	//return (GfxSurface)SDL_DisplayFormatAlpha(IMG_Load(fname));
};
s32 API_HGE::Surface_Free(GfxSurface surface)
{
	//SDL_FreeSurface((SDL_Surface*)surface);
	return true;
};
s32 API_HGE::Surface_GetWidth(GfxSurface surface)
{
	//return ((SDL_Surface*)surface)->w;
};
s32 API_HGE::Surface_GetHeight(GfxSurface surface)
{
	//return ((SDL_Surface*)surface)->h;
};
s32 API_HGE::Surface_GetBitsPerPixel(GfxSurface surface)
{
	//return ((SDL_Surface*)surface)->pitch;
};
s32 API_HGE::Surface_GetMemoryUsage(GfxSurface surface)
{
	//SDL_Surface* _tsurf = (SDL_Surface*)surface;
	//return (_tsurf->w*_tsurf->h*(_tsurf->pitch/8))+sizeof(SDL_Surface);
};
s32 API_HGE::Input_GetEvent(InputEvent* evt)
{
	hgeInputEvent event;
	int event_number = 0;
	event_number = hge->Input_GetEvent(&event);
	switch(event.type)
	{
		case INPUT_KEYDOWN:
			evt->type = InputEvent::Evt_KeyPress;
			evt->key.keyboard_key = event.key;
			evt->key.keyboard_flag = event.flags;
			evt->key.keyboard_char = event.chr;
		break;
		case INPUT_KEYUP:
			evt->type = InputEvent::Evt_KeyRelease;
			evt->key.keyboard_key = event.key;
			evt->key.keyboard_flag = event.flags;
			evt->key.keyboard_char = event.chr;
		break;
		case INPUT_MBUTTONDOWN:
			evt->type = InputEvent::Evt_MousePress;
			evt->mouse.button = event.key;
			evt->mouse.x = event.x;
			evt->mouse.y = event.y;
		break;
		case INPUT_MBUTTONUP:
			evt->type = InputEvent::Evt_MouseRelease;
			evt->mouse.button = event.key;
			evt->mouse.x = event.x;
			evt->mouse.y = event.y;
		break;
		case INPUT_MOUSEWHEEL:
			evt->type = InputEvent::Evt_MouseWheel;
			evt->mouse.degrees = event.wheel;
			evt->mouse.x = event.x;
			evt->mouse.y = event.y;
		break;
		case INPUT_MOUSEMOVE:
			evt->type = InputEvent::Evt_MouseMove;
			evt->mouse.x = event.x;
			evt->mouse.y = event.y;
		break;
		default:
			evt->type = InputEvent::Evt_None;
		break;
	}
	return event_number;
};
bool API_HGE::Input_GetKeyState(u8 key)
{
	return (hge->Input_GetKeyState(key) == 1);
};
bool _SysFrameFunction()
{
	if(_sysCB!=0)
		_sysCB->_FrameFunc();
}
bool _SysRenderFunction()
{
	if(_sysCB!=0)
		_sysCB->_Render();
}
