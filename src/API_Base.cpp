#include "API_Base.h"

API_Base::API_Base()
{
	//ctor
}

API_Base::~API_Base()
{
	//dtor
}
void 			API_Base::Sys_Sleep(s32 count){};
s32 			API_Base::Sys_GetTicks(){return 0;};
s32 			API_Base::Sys_GetDelta(){return 0;};
bool			API_Base::Sys_OverloadFuncs(){return false;};
void			API_Base::Sys_SetCallBack(SysCallBack* callback){_sysCallback = callback;};
void			API_Base::Sys_Run(){return;};

void			API_Base::Gfx_Initialize(){};
void			API_Base::Gfx_Render(){};
void			API_Base::Gfx_Destroy(){};
void			API_Base::Gfx_DrawString(s32 x, s32 y, c_string_p format, u32 bgcolor, u32 fgcolor){};
void			API_Base::Gfx_DrawPoint(s32 x, s32 y, u32 color){};
void			API_Base::Gfx_DrawLine(s32 x1, s32 y1, s32 x2, s32 y2, u32 color){};
void			API_Base::Gfx_DrawSurface(s32 x1, s32 y1,GfxSurface surf){};
void			API_Base::Gfx_DrawSurfaceAlpha(s32 x1, s32 y1,GfxSurface surf, s32 alpha){};
void 			API_Base::Gfx_DrawSurfaceRect(s32 x1, s32 y1,GfxSurface surf, Rect* rect){};
void 			API_Base::Gfx_ClearScreen(u32 color){};
u32				API_Base::Gfx_MakeColor(u8 r, u8 g, u8 b, u8 a){return 0;};
void			API_Base::Gfx_GetRGBA(u32 col, u8* r, u8* g, u8* b, u8* a){};

GfxSurface		API_Base::Surface_Create(s32 width, s32 height){return NULL;};
GfxSurface 		API_Base::Surface_Load(c_string_p fname){return NULL;};
s32				API_Base::Surface_Free(GfxSurface surface){return 0;};
s32				API_Base::Surface_GetWidth(GfxSurface surface){return 0;};
s32				API_Base::Surface_GetHeight(GfxSurface surface){return 0;};
s32				API_Base::Surface_GetBitsPerPixel(GfxSurface surface){return 0;};
s32				API_Base::Surface_GetMemoryUsage(GfxSurface surface){return 0;};

s32				API_Base::Input_GetEvent(InputEvent* evt){return 0;};
bool			API_Base::Input_GetKeyState(u8 key){return 0;};
