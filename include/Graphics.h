#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <sdl.h>
#include "utils.h"
#include <sge.h>

class Graphics;
typedef bool (*renderCallback)(Graphics*);

class Graphics
{
	public:
		Graphics();
		~Graphics();
		void Render();
		void DrawString(int x, int y, char* format,...);
		void DrawPoint(int x, int y);
		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawSurface(int x1, int y1,SDL_Surface* surf);
		void DrawSurfacePart(int x1, int y1,SDL_Surface* surf, int srcx, int srcy, int srcw, int srch);
		void DrawSurfaceRect(int x1, int y1,SDL_Surface* surf, SDL_Rect* rect);
		void SetBGColor(int r, int g, int b, int a);
		void SetFGColor(int r, int g, int b, int a);
		void SetRenderFunc(renderCallback renderFunc);
	protected:
	private:
		unsigned int fgColor;
		unsigned int bgColor;
		unsigned int* pixBuffer;
		SDL_Surface *_targetScreen;
		SDL_Surface *_gfxSurface;
		renderCallback _renderFunc;
		sge_TTFont *font;
};



#endif // GRAPHICS_H
