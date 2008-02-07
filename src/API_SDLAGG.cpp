#include "API_SDLAGG.h"
#include <sdl.h>
#include <sdl_image.h>
#include "Agg2d.h"
#include "utils.h"
#define limit(a,b) (a>b)? (b) : (a)
#define pix_format agg::pixfmt_rgba32
#define COLOR_GETRED(col) ((col & 0xFF000000) >> 24)
#define COLOR_GETGREEN(col) ((col & 0x00FF0000) >> 16)
#define COLOR_GETBLUE(col) ((col & 0x0000FF00) >> 8)
#define COLOR_GETALPHA(col) (col & 0x000000FF)
#define COLOR_MAKERGBA(r,g,b,a) ((r << 24) + (g << 16) + (b << 8) + a)

typedef struct{
	SDL_Surface* sdl;
	Agg2D::Image* agg;
}SurfaceContainer;

typedef agg::pixfmt_rgba32 pixfmt_type;
typedef agg::renderer_base<pixfmt_type> renderer_base_type;

API_SDLAGG::API_SDLAGG()
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

API_SDLAGG::~API_SDLAGG()
{
	SDL_Quit();
}
void API_SDLAGG::Sys_Sleep(s32 count)
{
	SDL_Delay(count);
}
s32 API_SDLAGG::Sys_GetTicks()
{
	return SDL_GetTicks();
};
void API_SDLAGG::Gfx_Initialize()
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
	SurfaceContainer* targetCont = new SurfaceContainer;
	targetCont->sdl = SDL_SetVideoMode(width, height, bpp, SDL_HWSURFACE);
	if (targetCont->sdl == NULL) {
			Log("[Error] Unable to set %ix%i video: %s\n", width,height, SDL_GetError());
			exit(1);
	}
	_targetScreen = (GfxSurface*)targetCont;
	SurfaceContainer* gfxCont = new SurfaceContainer;
	gfxCont->sdl = SDL_DisplayFormatAlpha(SDL_CreateRGBSurface(SDL_SWSURFACE,width, height, bpp, rmask, gmask, bmask, amask));
	if (gfxCont->sdl == NULL)
		return;
	_gfxSurface = (GfxSurface*)gfxCont;
	SDL_WM_SetCaption("MGame",NULL);
	sge_TTF_Init();
	font = sge_TTF_OpenFont("arial.ttf",10);
	sge_Update_OFF();
	sge_TTF_AAOff();
	//sge_TTF_AA_Alpha();
	//void* rBuffer = ((SDL_Surface*)_gfxSurface)->sdl->pixels;
	//unsigned char* renderBuffer = (unsigned char*)rBuffer;
    //agg::rendering_buffer rbuf(renderBuffer, width, height, bpp/8);
	m_graphics.attach((unsigned char*)((SurfaceContainer*)_gfxSurface)->sdl->pixels, width, height, width*(bpp/8));//rbuf.buf()
	m_graphics.blendMode(Agg2D::BlendAlpha);
	_gfxImage.attach((unsigned char*)((SurfaceContainer*)_gfxSurface)->sdl->pixels, width, height, width*(bpp/8));
}
void API_SDLAGG::Gfx_Render()
{
	SDL_BlitSurface(((SurfaceContainer*)_gfxSurface)->sdl, NULL, ((SurfaceContainer*)_targetScreen)->sdl, NULL);
	SDL_UpdateRect(((SurfaceContainer*)_targetScreen)->sdl, 0, 0, 0, 0);
};
void API_SDLAGG::Gfx_Destroy()
{
	if (_gfxSurface == NULL)
		return;
	SDL_FreeSurface(((SurfaceContainer*)_gfxSurface)->sdl);
};
void API_SDLAGG::Gfx_DrawString(s32 x, s32 y, c_string_p format, u32 bgcolor, u32 fgcolor)
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
void API_SDLAGG::Gfx_DrawPoint(s32 x, s32 y, u32 color)
{
};
void API_SDLAGG::Gfx_DrawLine(s32 x1, s32 y1, s32 x2, s32 y2, u32 color)
{
	u8 r, g, b, a;
	Agg2D::Color tcol(	COLOR_GETRED(color),	COLOR_GETGREEN(color),
						COLOR_GETBLUE(color),	COLOR_GETALPHA(color));
	m_graphics.lineColor(tcol);
	m_graphics.line(x1,y1,x2,y2);
};
void API_SDLAGG::Gfx_DrawSurface(s32 x1, s32 y1,GfxSurface surf)
{
	SurfaceContainer* _tempSurface = ((SurfaceContainer*)surf);
	m_graphics.imageBlendMode(Agg2D::BlendAlpha);
	SDL_LockSurface(_tempSurface->sdl);
	//Log("img.bpp = %i",_tempSurface->sdl->pitch);
	/*Agg2D::Image img((unsigned char*)_tempSurface->sdl->pixels,
					 Surface_GetWidth(surf), Surface_GetHeight(surf),
					 (Surface_GetBitsPerPixel(surf)/8)*Surface_GetWidth(surf));*/
	Agg2D::Image* img = _tempSurface->agg;
	//pixfmt_type img_pixfmt(img->renBuf);
	m_graphics.blendImage((*img), 0,0, limit(x1+img->width(), _gfxImage.width()-x1),
									limit(y1+img->height(), _gfxImage.height()-y1),
									x1, y1);
	SDL_UnlockSurface(_tempSurface->sdl);
	/*sge_Blit(	(SDL_Surface*)surf,
				(SDL_Surface*)_gfxSurface,
				0,0,x1,y1,
				Surface_GetWidth(surf),
				Surface_GetHeight(surf));*/
};
void API_SDLAGG::Gfx_DrawSurfaceAlpha(s32 x1, s32 y1,GfxSurface surf, s32 alpha)
{
	m_graphics.blendImage((*img), 0,0, limit(x1+img->width(), _gfxImage.width()-x1),
									limit(y1+img->height(), _gfxImage.height()-y1),
									x1, y1);
    /*sge_BlitTransparent(	(SDL_Surface*)surf,
                            (SDL_Surface*)_gfxSurface,
				            0,0,x1,y1,
                            Surface_GetWidth(surf),
                            Surface_GetHeight(surf),
                            0xFF00FF00, alpha);*/
};
void API_SDLAGG::Gfx_DrawSurfaceRect(s32 x1, s32 y1,GfxSurface surf, Rect* rect)
{
	/*SDL_Rect srcRct = {rect->x,rect->y,((SDL_Surface*)surf)->w,((SDL_Surface*)surf)->h};
	SDL_Rect dstRct = {x1,y1,rect->w,rect->h};
	SDL_BlitSurface((SDL_Surface*)surf, &srcRct, (SDL_Surface*)_gfxSurface, &dstRct);*/
};
void API_SDLAGG::Gfx_ClearScreen(u32 color)
{
	sge_ClearSurface(((SurfaceContainer*)_gfxSurface)->sdl, color);
};
u32	API_SDLAGG::Gfx_MakeColor(u8 r, u8 g, u8 b, u8 a)
{
	//Agg2D::Color tcol(r,g,b,a);
	return COLOR_MAKERGBA(r,g,b,a);
};
void API_SDLAGG::Gfx_GetRGBA(u32 col, u8* r, u8* g, u8* b, u8* a)
{
	(*r) = COLOR_GETRED(col);
	(*g) = COLOR_GETGREEN(col);
	(*b) = COLOR_GETBLUE(col);
	(*a) = COLOR_GETALPHA(col);
};
GfxSurface API_SDLAGG::Surface_Create(s32 width, s32 height)
{
	return NULL;
};
GfxSurface API_SDLAGG::Surface_Load(c_string_p fname)
{
	SDL_Surface* _tsurf = SDL_DisplayFormatAlpha(IMG_Load(fname));
	Agg2D::Image* _timg = new Agg2D::Image((unsigned char*)_tsurf->pixels, _tsurf->w,_tsurf->h, _tsurf->pitch);
	SurfaceContainer* cont = new SurfaceContainer;
	cont->agg = _timg;
	cont->sdl = _tsurf;
	GfxSurface tsurf = (GfxSurface)cont;//(GfxSurface)SDL_DisplayFormatAlpha(IMG_Load(fname));
	Log("\ttsurf[width] = %i",((SurfaceContainer*)tsurf)->agg->width());
	Log("\ttsurf[height] = %i",((SurfaceContainer*)tsurf)->agg->height());

	return tsurf;
};
s32 API_SDLAGG::Surface_Free(GfxSurface surface)
{
	SurfaceContainer* cont = (SurfaceContainer*) surface;
	SDL_FreeSurface(cont->sdl);
	delete cont->agg;
	delete cont;
	return true;
};
s32 API_SDLAGG::Surface_GetWidth(GfxSurface surface)
{
	return ((SurfaceContainer*)surface)->agg->width();
};
s32 API_SDLAGG::Surface_GetHeight(GfxSurface surface)
{
	return ((SurfaceContainer*)surface)->agg->height();
};
s32 API_SDLAGG::Surface_GetBitsPerPixel(GfxSurface surface)
{
	return ((SurfaceContainer*)surface)->sdl->format->BitsPerPixel;
};
s32 API_SDLAGG::Surface_GetMemoryUsage(GfxSurface surface)
{
	SDL_Surface* _tsurf = ((SurfaceContainer*)surface)->sdl;
	return (_tsurf->w*_tsurf->h*(_tsurf->format->BytesPerPixel))+sizeof(SDL_Surface)+sizeof(SurfaceContainer);
};
s32 API_SDLAGG::Input_GetEvent(InputEvent* evt)
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
bool API_SDLAGG::Input_GetKeyState(u8 key)
{
	return (keys[key] == 1);
};
