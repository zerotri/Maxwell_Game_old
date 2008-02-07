#ifndef API_BASE_H
#define API_BASE_H
#define INCLUDE_LIBS_ONLY
#define INCLUDE_NO_LIBS
#define INCLUDE_LIBS_ONLY
#include "main.h"
typedef struct InputEvent_TYPE
{
	enum{
		Evt_None,
		Evt_KeyPress,
		Evt_KeyRelease,
		Evt_MousePress,
		Evt_MouseWheel,
		Evt_MouseRelease,
		Evt_MouseMove
	}type;
	struct{
		s8 degrees;
		u8 button;
		s32 x;
		s32 y;
	}mouse;
	struct{
		u16 keyboard_key;
		u8 	keyboard_flag;
		u8 	keyboard_char;
	}key;
}InputEvent;

class API_Base
{
	public:
		API_Base();
		virtual ~API_Base();
		//---System Functions---//
		//virtual s32			Sys_RunConstant();
		virtual void 		Sys_Sleep(s32 count);
		virtual s32 		Sys_GetDelta();
		virtual s32 		Sys_GetTicks();
		virtual bool		Sys_OverloadFuncs();
		virtual void		Sys_SetCallBack(SysCallBack* callback);
		virtual void		Sys_Run();
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
		virtual void 		Gfx_DrawSurface	(s32 x1, s32 y1,GfxSurface surf);
		virtual void 		Gfx_DrawSurfaceAlpha(s32 x1, s32 y1,GfxSurface surf, s32 alpha);
		virtual void 		Gfx_DrawSurfaceRect(s32 x1, s32 y1,GfxSurface surf, Rect* rect);
		virtual void 		Gfx_ClearScreen(u32 color);
		virtual u32	 		Gfx_MakeColor(u8 r, u8 g, u8 b, u8 a);
		virtual void 		Gfx_GetRGBA(u32 col, u8* r, u8* g, u8* b, u8* a);
		virtual GfxSurface 	Surface_Create(s32 width, s32 height);
		virtual GfxSurface 	Surface_Load(c_string_p fname);
		virtual s32			Surface_Free(GfxSurface surface);
		virtual s32 		Surface_GetWidth(GfxSurface surface);
		virtual s32 		Surface_GetHeight(GfxSurface surface);
		virtual s32 		Surface_GetBitsPerPixel(GfxSurface surface);
		virtual s32 		Surface_GetMemoryUsage(GfxSurface surface);
		virtual s32 		Input_GetEvent(InputEvent* evt);
		virtual bool 		Input_GetKeyState(u8 key);
	protected:
		GfxSurface _targetScreen;
		GfxSurface _gfxSurface;
		SysCallBack* _sysCallback;
	private:
};



#endif // API_BASE_H
