#include "System.h"
HGE* hge = 0;
char _strbuf[256];
extern bool FrameFunc();
extern bool RenderFunc();
System::System()
{
	hge = hgeCreate(HGE_VERSION);
}

System::~System()
{
	// Release the HGE interface.
	// If there are no more references,
	// the HGE object will be deleted.
	hge->Release();
}

int System::Init()
{
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_SCREENWIDTH, 320);
	hge->System_SetState(HGE_SCREENHEIGHT, 240);
	hge->System_SetState(HGE_TITLE, "Maxwell Game");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_LOGFILE, "game.log");
	hge->System_SetState(HGE_FPS, HGEFPS_UNLIMITED);
	return hge->System_Initiate();
}
void System::End()
{
	RsrcManager.~ResourceManager();
	hge->System_Shutdown();
}
void System::Log(char* format,...){
	///create va_list and load all arguments
	va_list ap;
	va_start(ap, format);
	vsprintf(_strbuf,format, ap); /// Call vprintf
	va_end(ap); /// Cleanup the va_list
	hge->System_Log(_strbuf);
};

