#ifndef API_SDL_H
#define API_SDL_H
#include "API_Base.h"
#include <sdl.h>
#include <sdl_image.h>
#include <sge.h>

class API_SDL : public API_Base
{
	public:
		API_SDL();
		virtual ~API_SDL();
		//---System Functions---//
		virtual void 		Sys_Sleep(s32 count);
		virtual s32 		Sys_GetTicks();
		//---Graphics Functions---//
		virtual void 		Gfx_Initialize();
		virtual void 		Gfx_Render();
		virtual void 		Gfx_Destroy();
		virtual void 		Gfx_DrawString	(s32 x,
											 s32 y,
											 c_string_p format,
											 u32 bgcolor,
											 u32 fgcolor);
		virtual void 		Gfx_DrawPoint	(s32 x,
											 s32 y,
											 u32 color);
		virtual void 		Gfx_DrawLine	(s32 x1,
											 s32 y1,
											 s32 x2,
											 s32 y2,
											 u32 color);
		/*virtual void Gfx_DrawRect(int x1, int y1, int x2, int y2);
		virtual void Gfx_DrawCircle(int x1, int y1, int radius);*/
		virtual void 		Gfx_DrawSurface	(s32 x1,
											 s32 y1,
											 GfxSurface surf);
		virtual void 		Gfx_DrawSurfaceAlpha(s32 x1,
												 s32 y1,
												 GfxSurface surf,
												 s32 alpha);
		virtual void 		Gfx_DrawSurfaceRect	(s32 x1,
												 s32 y1,
												 GfxSurface surf,
												 Rect* rect);
		virtual void 		Gfx_ClearScreen	(u32 color);
		virtual u32	 		Gfx_MakeColor	(u8 r,
											 u8 g,
											 u8 b,
											 u8 a);
		virtual void 		Gfx_GetRGBA		(u32 col,
											 u8* r,
											 u8* g,
											 u8* b,
											 u8* a);

		virtual GfxSurface 	Surface_Create	(s32 width,
											 s32 height);
		virtual GfxSurface 	Surface_Load(c_string_p fname);
		virtual s32			Surface_Free(GfxSurface surface);
		virtual s32 		Surface_GetWidth(GfxSurface surface);
		virtual s32 		Surface_GetHeight(GfxSurface surface);
		virtual s32 		Surface_GetBitsPerPixel(GfxSurface surface);
		virtual s32 		Surface_GetMemoryUsage(GfxSurface surface);

		virtual s32 		Input_GetEvent(InputEvent* evt);
		virtual bool 		Input_GetKeyState(u8 key);
		/*
		virtual void Sys_Sleep(int count);
		virtual int  Sys_GetTicks();
		//---Graphics Functions---//
		virtual void Gfx_Initialize();
		virtual void Gfx_Render();
		virtual void Gfx_Destroy();
		virtual void Gfx_DrawString(int x, int y, char* format, unsigned int bgcolor, unsigned int fgcolor);
		virtual void Gfx_DrawPoint(int x, int y);
		virtual void Gfx_DrawLine(int x1, int y1, int x2, int y2);
		virtual void Gfx_DrawSurface(int x1, int y1,GfxSurface surf);
		virtual void Gfx_DrawSurfaceRect(int x1, int y1,GfxSurface surf, Rect* rect);
		virtual void Gfx_ClearScreen(unsigned int color);
		virtual unsigned int Gfx_MakeColor(int r, int g, int b, int a);
		virtual void Gfx_GetRGBA(unsigned int col, int* r, int* g, int* b, int* a);
		virtual GfxSurface Surface_Create(int width, int height);
		virtual GfxSurface Surface_Load(char* fname);
		virtual int  Surface_Free(GfxSurface surface);
		virtual int  Surface_GetWidth(GfxSurface surface);
		virtual int  Surface_GetHeight(GfxSurface surface);
		virtual int  Surface_GetBitsPerPixel(GfxSurface surface);
		virtual int  Surface_GetMemoryUsage(GfxSurface surface);
		virtual int  Input_GetEvent(InputEvent* evt);
		virtual bool Input_GetKeyState(unsigned char key);*/
	protected:
	private:
		u8* keys;
		sge_TTFont *font;
};



#endif // API_SDL_H
