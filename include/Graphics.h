#ifndef GRAPHICS_H
#define GRAPHICS_H
#define INCLUDE_LIBS_ONLY
#include "main.h"
#include "API_Base.h"

class Graphics
{
	public:
		Graphics();
		~Graphics();
		void Render();
		void DrawString(int x, int y, char* format,...);
		void DrawPoint(int x, int y);
		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawSurface(int x1, int y1,GfxSurface surf);
		void DrawSurfaceAlpha(int x1, int y1,GfxSurface surf, s32 alpha);
		void DrawSurfacePart(int x1, int y1,GfxSurface surf, int srcx, int srcy, int srcw, int srch);
		void DrawSurfaceRect(int x1, int y1,GfxSurface surf, Rect* rect);
		void SetAPI(API_Base* _api);
		void SetBGColor(int r, int g, int b, int a);
		void SetFGColor(int r, int g, int b, int a);
		void SetRenderFunc(SysCallBack* renderFunc);
		int Surface_GetWidth(GfxSurface surface);
		int Surface_GetHeight(GfxSurface surface);
		int Surface_GetBitsPerPixel(GfxSurface surface);
	protected:
	private:
		unsigned int fgColor;
		unsigned int bgColor;
		SysCallBack* _renderFunc;
		API_Base* api;
};



#endif // GRAPHICS_H
