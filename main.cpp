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
#include "chipmunk/chipmunk.h"
#include "main.h"
LuaVM* lua;
HGE *hge = 0;
hgeFont* font;
GameModel* model;
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
void DrawFontRotated(hgeFont* font, char* text, float x, float y, float angle, bool centered)
{
	float pos = 0;
	font->SetRotation(angle);
	int fullLength = (int)(font->GetStringWidth(text)/2.0f);
	for (int i=0;i<(int)strlen(text);i++)
	{
		char curC[2] = "\0";
		curC[0] = text[i];
		if (!centered)
				font->Render(x+pos*cos(angle), y+pos*sin(angle),0,curC);
		else
				font->Render(x+(pos-fullLength)*cos(angle), y+(pos-fullLength)*sin(angle),0,curC);
		pos += font->GetStringWidth(curC);
	}
	font->SetRotation(0);
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
void DrawModel(GameModel* _model)
{
	cpBody *body = _model->getBody();
	cpPolyShape *poly = (cpPolyShape*)_model->getShape();
	cpVect *verts = poly->verts+1;
	//double lastx = 0.0f, lasty = 0.0f;
	//hgeVertex *vtx = hge->Gfx_StartBatch(HGEPRIM_QUADS, 0, BLEND_DEFAULT, 0);
	for(int i=0; i<poly->numVerts; i++){
		cpVect v = cpvadd(body->p, cpvrotate(verts[i], body->rot));
		//hge->Gfx_RenderLine(lastx, lasty, v.x, v.y, HWCOL(white),1.0f);
		//SET_XY(vtx[i],v.x,v.y);
		//vtx[i].col = 0xFFFFFFFF;
	}
	//hge->Gfx_FinishBatch(1);
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
		sprAnim.drawCurrentFrame(32,32);
		DrawModel(model);
		font->printf(32.0f,32.0f,HGETEXT_LEFT,"FPS: %i\nHello World!",hge->Timer_GetFPS());
		is_Rendering = false;
	hge->Gfx_EndScene();

	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Here we use global pointer to HGE interface.
	// Instead you may use hgeCreate() every
	// time you need access to HGE. Just be sure to
	// have a corresponding hge->Release()
	// for each call to hgeCreate()
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_SCREENWIDTH, 320);
	hge->System_SetState(HGE_SCREENHEIGHT, 240);
	hge->System_SetState(HGE_TITLE, "Pegasus' Great Adventure - Test Demos");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_LOGFILE, "hge_tut05.log");
	hge->System_SetState(HGE_FPS, HGEFPS_UNLIMITED);
	cpInitChipmunk();
	SET_XY(corners[0],	8,	8);
	SET_XY(corners[1],	hge->System_GetState(HGE_SCREENWIDTH) - 8,	8);
	SET_XY(corners[2],	hge->System_GetState(HGE_SCREENWIDTH) - 8,
						hge->System_GetState(HGE_SCREENHEIGHT) - 8);
	SET_XY(corners[3],	8,	hge->System_GetState(HGE_SCREENHEIGHT) - 8);
	rectangle.blend = BLEND_DEFAULT;
	lua = new LuaVM();
	GameWorld world;
	model = new GameModel(world.getSpace());
	inputHandler.AddInputHandler(&input);
	// Tries to initiate HGE with the states set.
	// If something goes wrong, "false" is returned
	// and more specific description of what have
	// happened can be read with System_GetErrorMessage().
	loadLua();
	if(hge->System_Initiate())
	{
		font = new hgeFont("font.fnt");
		font->SetBlendMode(BLEND_DEFAULT);
		// Starts running FrameFunc().
		// Note that the execution "stops" here
		// until "true" is returned from FrameFunc().
        //
		spr1 = hge->Texture_Load("spr1.png");
		spr2 = hge->Texture_Load("spr3.png");
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
	hge->Texture_Free(spr1);
	hge->Texture_Free(spr2);
	hge->Texture_Free(spr3);
	hge->System_Shutdown();

	// Release the HGE interface.
	// If there are no more references,
	// the HGE object will be deleted.
	hge->Release();

	return 0;
}
