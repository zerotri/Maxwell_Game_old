/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut01 - Minimal HGE application
*/

#include <hge.h>
#include <hgecolor.h>
#include <hgefont.h>
#include <hgegui.h>
#include "chipmunk/chipmunk.h"
#include "main.h"
System sys;
LuaVM* lua;
extern HGE *hge;
hgeFont* font;
hgeQuad rectangle;
hgeVertex corners[4];
ANIM gAnims[2];
GameAnimation sprAnim;
HTEXTURE spr1 = 0, spr2 = 0, spr3 = 0;
bool is_Rendering = true;
Input inputHandler;
char key = '\0';
class InputA : public InputHandler
{
	void onKeyPress(int keyboard_key, int keyboard_flag, int keyboard_char)
	{
		key = keyboard_char;
	};
	void onKeyRelease(int keyboard_key, int keyboard_flag, int keyboard_char)
	{
		key = '\0';
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
};
InputA input;
int l_GetKeystate( lua_State* luaVM)
{
	lua_pushnumber( luaVM, (lua_Number)(hge->Input_GetKeyState((int)lua_tonumber(luaVM, -1))));
	return true;
}
int l_DrawLine( lua_State* luaVM)
{

	hge->Gfx_RenderLine( (lua_Number)lua_tonumber(luaVM, -4),
					(lua_Number)lua_tonumber(luaVM, -3),
					(lua_Number)lua_tonumber(luaVM, -2),
					(lua_Number)lua_tonumber(luaVM, -1),
					HWCOL(white), 1);
	return true;

}
int l_PrintText( lua_State* luaVM)
{
	if(!is_Rendering)
		return false;
	font->printf(lua_tonumber(luaVM, -3),lua_tonumber(luaVM, -2),HGETEXT_LEFT,lua_tostring(luaVM, -1));
	lua_pushnumber( luaVM, 0 );
	return true;
}
// This function will be called by HGE once per frame.
// Put your game loop code here. In this example we
// just check whether ESC key has been pressed.
void loadLua(){
	lua->resetState();
	lua->setVariable("VK_F1",	HGEK_F1);
	lua->setVariable("VK_F2",	HGEK_F2);
	lua->setVariable("VK_F3",	HGEK_F3);
	lua->setVariable("VK_F4",	HGEK_F4);
	lua->setVariable("VK_F5",	HGEK_F5);
	lua->setVariable("VK_F6",	HGEK_F6);
	lua->setVariable("VK_F7",	HGEK_F7);
	lua->setVariable("VK_F8",	HGEK_F8);
	lua->setVariable("VK_F9",	HGEK_F9);
	lua->setVariable("VK_F10",	HGEK_F10);
	lua->setVariable("VK_F11",	HGEK_F11);
	lua->setVariable("VK_F12",	HGEK_F12);
	lua->setVariable("VK_LEFT",	HGEK_LEFT);
	lua->setVariable("VK_RIGHT",HGEK_RIGHT);
	lua->setVariable("VK_UP",	HGEK_UP);
	lua->setVariable("VK_DOWN",	HGEK_DOWN);
	lua->setVariable("VK_A",	HGEK_A);
	lua->setVariable("HGEPRIM_LINES",	HGEPRIM_LINES);
	lua->setVariable("HGEPRIM_TRIPLES",	HGEPRIM_TRIPLES);
	lua->setVariable("HGEPRIM_QUADS",	HGEPRIM_QUADS);
	lua->registerFunction("PrintText",	l_PrintText);
	lua->registerFunction("GetKeystate",	l_GetKeystate);
	lua->registerFunction("DrawLine",	l_DrawLine);
	if(lua->loadFile("__game.lua")!=0)
	{
		hge->System_Log("Cannot run lua file: %s", lua->getString(-1));
	}else lua->run();
}

bool FrameFunc()
{
	// By returning "true" we tell HGE
	// to stop running the application.
	sprAnim.update(hge->Timer_GetDelta());
	if (hge->Input_GetKeyState(HGEK_F5)) loadLua();
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	// Continue execution
	return false;
}
bool RenderFunc()
{
	// Render graphics
	corners[0].col = HWCOL(blue);
	corners[1].col = HWCOL(blue);
	corners[2].col = HWCOL(blue);
	corners[3].col = HWCOL(blue);
	rectangle.v[0] = corners[0];
	rectangle.v[1] = corners[1];
	rectangle.v[2] = corners[2];
	rectangle.v[3] = corners[3];
	font->SetColor(HWCOL(white));
	hge->Gfx_BeginScene();
		is_Rendering = true;
		hge->Gfx_Clear(0);
		hge->Gfx_RenderQuad(&rectangle);
		inputHandler.Query();
		if(key!='\0')font->printf(0,0,HGETEXT_LEFT,"Key Pressed: %c", key);
		lua->callFunction("draw");
		lua->run();
		sprAnim.drawCurrentFrame(128,128);
		font->printf(32.0f,32.0f,HGETEXT_LEFT,"FPS: %i\nHello World!",hge->Timer_GetFPS());
		is_Rendering = false;
	hge->Gfx_EndScene();

	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if(sys.Init())
	{
		SET_XY(corners[0],	8,	8);
		SET_XY(corners[1],	hge->System_GetState(HGE_SCREENWIDTH) - 8,	8);
		SET_XY(corners[2],	hge->System_GetState(HGE_SCREENWIDTH) - 8,
							hge->System_GetState(HGE_SCREENHEIGHT) - 8);
		SET_XY(corners[3],	8,	hge->System_GetState(HGE_SCREENHEIGHT) - 8);
		rectangle.blend = BLEND_DEFAULT;
		lua = new LuaVM();
		loadLua();
		inputHandler.AddInputHandler(&input);
		font = new hgeFont("font.fnt");
		font->SetBlendMode(BLEND_DEFAULT);
		// Starts running FrameFunc().
		// Note that the execution "stops" here
		// until "true" is returned from FrameFunc().
        //
        spr1 = sys.RsrcManager.LoadTexture("spr1.png","spr1");
        spr2 = sys.RsrcManager.LoadTexture("spr3.png","spr2");
		SET_TLBR(gAnims[0],0.0f,0.0f,1.0f,1.0f);
		SET_TLBR(gAnims[1],0.0f,0.0f,1.0f,1.0f);
		gAnims[0].hTex = spr1;
		gAnims[1].hTex = spr2;
		gAnims[0].fAnimSpeed = 0.25f;
		gAnims[1].fAnimSpeed = 0.50f;
		gAnims[0].lpNext = &gAnims[1];
		gAnims[1].lpNext = &gAnims[0];
		sprAnim.setAnimation(&gAnims[0]);
		hge->System_Start();
	}
	else
	{
		// If HGE initialization failed show error message
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

	// Now ESC has been pressed or the user
	// has closed the window by other means.

	// Restore video mode and free
	// all allocated resources
	delete font;
	delete lua;
	sys.End();

	return 0;
}
