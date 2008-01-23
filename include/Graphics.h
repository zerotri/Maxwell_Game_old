#ifndef GRAPHICS_H
#define GRAPHICS_H
#define INCLUDE_LIBS_ONLY
#include "main.h"
#include "API_Base.h"
class RenderCallback
{
	public:
		virtual bool _Render(){return false;};
};

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
		void DrawSurfacePart(int x1, int y1,GfxSurface surf, int srcx, int srcy, int srcw, int srch);
		void DrawSurfaceRect(int x1, int y1,GfxSurface surf, Rect* rect);
		void SetAPI(API_Base* _api);
		void SetBGColor(int r, int g, int b, int a);
		void SetFGColor(int r, int g, int b, int a);
		void SetRenderFunc(RenderCallback* renderFunc);
		int Surface_GetWidth(GfxSurface surface);
		int Surface_GetHeight(GfxSurface surface);
		int Surface_GetBitsPerPixel(GfxSurface surface);
	protected:
	private:
		unsigned int fgColor;
		unsigned int bgColor;
		RenderCallback* _renderFunc;
		API_Base* api;
};



#endif // GRAPHICS_H
