#include "API_Base.h"


API_Base::API_Base()
{
	//ctor
}

API_Base::~API_Base()
{
	//dtor
}
void API_Base::Sys_Sleep(int count){};
int API_Base::Sys_GetTicks(){return 0;};

void			API_Base::Gfx_Initialize(){};
void			API_Base::Gfx_Render(){};
void			API_Base::Gfx_Destroy(){};
void			API_Base::Gfx_DrawString(int x, int y, char* format, unsigned int bgcolor, unsigned int fgcolor){};
void			API_Base::Gfx_DrawPoint(int x, int y){};
void			API_Base::Gfx_DrawLine(int x1, int y1, int x2, int y2){};
void			API_Base::Gfx_DrawSurface(int x1, int y1,GfxSurface surf){};
void 			API_Base::Gfx_DrawSurfaceRect(int x1, int y1,GfxSurface surf, Rect* rect){};
void 			API_Base::Gfx_ClearScreen(unsigned int color){};
unsigned int	API_Base::Gfx_MakeColor(int r, int g, int b, int a){return 0;};
void			API_Base::Gfx_GetRGBA(unsigned int col, int* r, int* g, int* b, int* a){};
GfxSurface		API_Base::Surface_Create(int width, int height){return NULL;};
GfxSurface 		API_Base::Surface_Load(char* fname){return NULL;};
int				API_Base::Surface_Free(GfxSurface surface){return 0;};
int				API_Base::Surface_GetWidth(GfxSurface surface){return 0;};
int				API_Base::Surface_GetHeight(GfxSurface surface){return 0;};
int				API_Base::Surface_GetBitsPerPixel(GfxSurface surface){return 0;};
