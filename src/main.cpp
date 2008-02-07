/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut01 - Minimal HGE application
*/

//#include "chipmunk.h"
#include "main.h"
#ifdef APIMODE_SDL
	#include "API_SDL.h"
	#define API_MODE API_SDL
#endif
#ifdef APIMODE_HGE
	#include "API_HGE.h"
	#define API_MODE API_HGE
#endif
#ifdef APIMODE_SDLAGG
	#include "API_SDLAGG.h"
	#define API_MODE API_SDLAGG
#endif

//Lua Function Prototypes
/*int l_PrintText( lua_State* luaVM);
int l_GetKeystate( lua_State* luaVM);
int l_DrawLine( lua_State* luaVM);
void loadLua(LuaVM* lua);*/
class InGameState : public GameState
{
    private:
        ANIM gAnims[2];
        GameAnimation sprAnim;
        GameEntity entity;
		Resource* wrldTs;
        Resource* rsrc1,* rsrc2,* rsrc3,* rsrc4;
        GfxSurface spr1, spr2, spr3, spr4;

    public:
        InGameState(){};
        virtual ~InGameState(){};

        void initialize(ApplicationBase* _app){
            app = _app;
            //Load all resources
            rsrc1 = _app->_ResourceManager->LoadResource("spr1.png","spr1");
            rsrc2 = _app->_ResourceManager->LoadResource("spr3.png","spr2");
            rsrc3 = _app->_ResourceManager->LoadResource("ts_01.png","ts_01");
            rsrc4 = _app->_ResourceManager->LoadResource("spr2.png","spr3");
            //Get surface data from resources
            Log("rsrc1 = %i", rsrc1);
            Log("Rsrc1.size() = %i", rsrc1->GetSize());
            spr1 = rsrc1->GetData();
            spr2 = rsrc2->GetData();
            spr3 = rsrc3->GetData();
            spr4 = rsrc4->GetData();
            //Get Resources here
            wrldTs = (*_app->_ResourceManager)["ts_01"];
            SET_TLBR(gAnims[0],0.0f,0.0f,1.0f,1.0f);
            SET_TLBR(gAnims[1],0.0f,0.0f,1.0f,1.0f);
            gAnims[0].pSurf = spr1;
            gAnims[1].pSurf = spr2;
            gAnims[0].fAnimSpeed = 1.0f;
            gAnims[1].fAnimSpeed = 1.0f;
            gAnims[0].lpNext = &gAnims[1];
            gAnims[1].lpNext = &gAnims[0];
            sprAnim.setAnimation(&gAnims[0]);
            sprAnim.setGraphics(_app->_Graphics);
			entity.SetPos(32,32);
            entity.SetSurface(spr4);
            Log("Memory Usage: %f MBytes", ((float)_app->_ResourceManager->GetMemoryUsage())/(1024.0f*1024.0f));
        };
        void shutdown(){
        };

        bool update(time_type delta){
        };
        void render(){
            app->_GameWorld->DrawWorld((GfxSurface)wrldTs->GetData());
            sprAnim.update(app->_System->getFrameTime());
            sprAnim.drawCurrentFrame(128,128);
            entity.Draw(app->_Graphics);
            app->_Graphics->DrawString(0,0,"FPS: %i",(int)app->_System->FPS());
            app->_Graphics->DrawString(32,32,"Hello SGE World!\nTesting Multiline Strings");
            app->_Graphics->DrawLine(0,0,64,32);
        };
};
class IntroState : public GameState
{
	private:
		time_type INTRO_TIME;
		Resource* Logo;
		bool isFadingIn;
		u8 fadeValue;

   public:
        IntroState() : _elapsedTime(SECONDS(0))
        {
            INTRO_TIME = SECONDS(0.04);
            isFadingIn = true;
            fadeValue = 0;
        }
        virtual ~IntroState(){};

        void initialize(ApplicationBase* _app){
            app = _app;
            Logo = _app->_ResourceManager->LoadResource("logo.png","logo");
           // load up whatever resources I need (background, sounds, etc)
        }
        void shutdown()
        {
           // release whatever resources I loaded in initialize
        }

		bool update(time_type delta)
		{
			_elapsedTime += delta;
			if(isFadingIn)
			{
				fadeValue++;
				if(_elapsedTime >= INTRO_TIME/2)
				{
					isFadingIn = false;
				}
			} else fadeValue--;
			if (_elapsedTime >= INTRO_TIME)
			{
				// if we've been here long enough, move on to the menu state
				StateMan()->popState();
				StateMan()->pushState(new InGameState());
			}

			return true;
		}
        void render()
        {
            app->_Graphics->DrawSurfaceAlpha(0,0,Logo->GetData(), (fadeValue*_elapsedTime)/INTRO_TIME);
            app->_Graphics->DrawString(0,0,"Time Left: %i MS",INTRO_TIME - _elapsedTime);
            app->_Graphics->DrawLine(0,0,32,32);
           // render our background, etc.
        }

    private:
        time_type _elapsedTime;
};


class MainApplication : public ApplicationBase
{
	public:
		bool bRunning;
		Resource* rsrc;
		MainApplication(API_Base* api) : ApplicationBase(api) {}
		bool Init()
		{
			StateMan()->RegisterApplicationBase(this);
			bRunning = true;
			//Set up all System-related stuff. I need to clean this all up later.
			//loadLua(&lua);
			// Starts running FrameFunc().
			// Note that the execution "stops" here
			// until "true" is returned from FrameFunc().
			StateMan()->pushState(new IntroState());
			return true;
		}
		bool RenderFunc()
		{
			StateMan()->render();
			return true;
		}
		bool FrameFunc()
		{
			StateMan()->update(_System->getFrameTime());

			/*lua.callFunction("draw");
			lua.run();*/

			return bRunning;
		}
		void onKeyPress(int keyboard_key, int keyboard_flag, int keyboard_char)
		{
			Log("Keypress: %c",keyboard_char);
			if(keyboard_key == KEY_ESCAPE) bRunning = false;
			//if(keyboard_key == SDLK_F5) loadLua(&lua);
		};
		void onKeyRelease(int keyboard_key, int keyboard_flag, int keyboard_char)
		{
			Log("Keyrelease: %c",keyboard_char);
		};
		void onMouseMove(int mouse_x, int mouse_y)
		{
			Log("Mousemove: %i, %i",mouse_x, mouse_y);
		};
		void onMousePress(int mouse_button, int mouse_x, int mouse_y)
		{
		};
		void onMouseRelease(int mouse_button, int mouse_x, int mouse_y)
		{
		};
		void onMouseWheel(int degrees, int mouse_x, int mouse_y)
		{
		};
		//LuaVM lua;
};


int main(int argc, char** argv)
{
	API_Base* api = new API_MODE;
	MainApplication MainApp(api);
	MainApp.Run();
	return false;
}

/*int l_GetKeystate( lua_State* luaVM)
{
	//lua_pushnumber( luaVM, (lua_Number)input->GetKeyState((int)lua_tonumber(luaVM, -1)));
	return true;
}
int l_DrawLine( lua_State* luaVM)
{
	//gfx->DrawLine(	(int)lua_tonumber(luaVM, -4),
	//				(int)lua_tonumber(luaVM, -3),
	//				(int)lua_tonumber(luaVM, -2),
	//				(int)lua_tonumber(luaVM, -1));
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
*/
