/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut01 - Minimal HGE application
*/

//#include "chipmunk.h"
#include "main.h"
#include "ApplicationBase.h"

//Lua Function Prototypes
int l_PrintText( lua_State* luaVM);
int l_GetKeystate( lua_State* luaVM);
int l_DrawLine( lua_State* luaVM);
void loadLua(LuaVM* lua);
class MainApplication : public ApplicationBase
{
	public:
	bool bRunning;
	ANIM gAnims[2];
	GameAnimation sprAnim;
	Resource rsrc;
	Resource wrldTs;
	bool Init()
	{
		bRunning = true;
		//Set up all System-related stuff. I need to clean this all up later.
		loadLua(&lua);

		/*spr1 = _ResourceManager.LoadTexture("spr1.png","spr1");
		spr2 = _ResourceManager.LoadTexture("spr3.png","spr2");
		spr3 = _ResourceManager.LoadTexture("ts_01.png","ts_01");
		rsrc = _ResourceManager["spr1"];
		wrldTs = _ResourceManager["ts_01"];
		// Starts running FrameFunc().
		// Note that the execution "stops" here
		// until "true" is returned from FrameFunc().
		SET_TLBR(gAnims[0],0.0f,0.0f,1.0f,1.0f);
		SET_TLBR(gAnims[1],0.0f,0.0f,1.0f,1.0f);
		gAnims[0].pSurf = spr1;
		gAnims[1].pSurf = spr2;
		gAnims[0].fAnimSpeed = 1.0f;
		gAnims[1].fAnimSpeed = 1.0f;
		gAnims[0].lpNext = &gAnims[1];
		gAnims[1].lpNext = &gAnims[0];
		sprAnim.setAnimation(&gAnims[0]);
		sprAnim.setGraphics(&_Graphics);*/
		return true;
	}
	bool FrameFunc()
	{
		_Input.Query();
		//gfx.DrawString(0.0f,20.0f,"Input->MsgCount: %i",sys.getInput().GetMsgCount());
		//gfx.DrawSurface(32,32,rsrc.rsrc.surface);
		// Process window messages if not in "child mode"
		// (if in "child mode" the parent application will do this for us)
		//_GameWorld.DrawWorld(wrldTs.rsrc.surface);
		//sprAnim.update(_System.getFrameTime());
		//sprAnim.drawCurrentFrame(128,128);
		_Graphics.Render();
		_Graphics.DrawString(0,0,"FPS: %i",(int)_System.FPS());
		_Graphics.DrawString(32,32,"Hello SGE World!\nWynter is %i", 17);

		lua.callFunction("draw");
		lua.run();

		return bRunning;
	}
	void onKeyPress(int keyboard_key, int keyboard_flag, int keyboard_char)
	{
		if(keyboard_key == SDLK_ESCAPE) bRunning = false;
		//if(keyboard_key == SDLK_F5) loadLua(&lua);
	};
	void onKeyRelease(int keyboard_key, int keyboard_flag, int keyboard_char)
	{
	};
	void onMouseMove(float mouse_x, float mouse_y)
	{
	};
	void onMousePress(int mouse_button, float mouse_x, float mouse_y)
	{
	};
	void onMouseRelease(int mouse_button, float mouse_x, float mouse_y)
	{
	};
	void onMouseWheel(int degrees, float mouse_x, float mouse_y)
	{
	};
	SDL_Surface* spr1, *spr2, *spr3;
	LuaVM lua;
};


int main(int argc, char** argv)
{
	putenv("SDL_VIDEODRIVER=directx");
	MainApplication MainApp;
	bool returnval = MainApp.Run();
	MainApp.~ApplicationBase();
	return returnval;
}

int l_GetKeystate( lua_State* luaVM)
{
	//lua_pushnumber( luaVM, (lua_Number)input->GetKeyState((int)lua_tonumber(luaVM, -1)));
	return true;
}
int l_DrawLine( lua_State* luaVM)
{
	/*gfx->DrawLine(	(int)lua_tonumber(luaVM, -4),
					(int)lua_tonumber(luaVM, -3),
					(int)lua_tonumber(luaVM, -2),
					(int)lua_tonumber(luaVM, -1));*/
	return true;

}
int l_PrintText( lua_State* luaVM)
{
	//gfx->DrawString((int)lua_tonumber(luaVM, -3),(int)lua_tonumber(luaVM, -2),(char*)lua_tostring(luaVM, -1));
	return true;
}
// This function will be called by HGE once per frame.
// Put your game loop code here. In this example we
// just check whether ESC key has been pressed.
void loadLua(LuaVM* lua){
	lua->resetState();
	lua->setVariable("VK_F1",	SDLK_F1);
	lua->setVariable("VK_F2",	SDLK_F2);
	lua->setVariable("VK_F3",	SDLK_F3);
	lua->setVariable("VK_F4",	SDLK_F4);
	lua->setVariable("VK_F5",	SDLK_F5);
	lua->setVariable("VK_F6",	SDLK_F6);
	lua->setVariable("VK_F7",	SDLK_F7);
	lua->setVariable("VK_F8",	SDLK_F8);
	lua->setVariable("VK_F9",	SDLK_F9);
	lua->setVariable("VK_F10",	SDLK_F10);
	lua->setVariable("VK_F11",	SDLK_F11);
	lua->setVariable("VK_F12",	SDLK_F12);
	lua->setVariable("VK_LEFT",	SDLK_LEFT);
	lua->setVariable("VK_RIGHT",SDLK_RIGHT);
	lua->setVariable("VK_UP",	SDLK_UP);
	lua->setVariable("VK_DOWN",	SDLK_DOWN);
	lua->setVariable("VK_A",	'A');
	lua->registerFunction("PrintText",		l_PrintText);
	lua->registerFunction("GetKeystate",	l_GetKeystate);
	lua->registerFunction("DrawLine",		l_DrawLine);
	if(lua->loadFile("__game.lua")!=0)
	{
		Log("Cannot run lua file: %s", lua->getString(-1));
	}else lua->run();
}
