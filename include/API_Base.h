#ifndef API_BASE_H
#define API_BASE_H
#define INCLUDE_LIBS_ONLY
#define INCLUDE_NO_LIBS
#include "main.h"

class API_Base
{
	public:
		API_Base();
		virtual ~API_Base();
		//---System Functions---//
		virtual void Sys_Sleep(int count);
		virtual int Sys_GetTicks();
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
		virtual int Surface_Free(GfxSurface surface);
		virtual int Surface_GetWidth(GfxSurface surface);
		virtual int Surface_GetHeight(GfxSurface surface);
		virtual int Surface_GetBitsPerPixel(GfxSurface surface);
	protected:
		GfxSurface _targetScreen;
		GfxSurface _gfxSurface;
	private:
};



#endif // API_BASE_H