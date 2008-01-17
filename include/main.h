#ifndef MAIN_H
#define MAIN_H
#include <sdl.h>
#include <sdl_image.h>
#include "vector.h"
extern "C" {
	#include <lua.h>
	#include "lualib.h"
	#include "lauxlib.h"
}

#ifndef INCLUDE_LIBS_ONLY
	#include "lua_utils.h"
	#include "LuaVM.h"
	#include "Input.h"
	#include "System.h"
	#include "Graphics.h"
	#include "GameAnimation.h"
	#include "GameWorld.h"
	#include "utils.h"
#endif
/*hgeColorRGB black(ARGB(255,0,0,0));
hgeColorRGB blue(ARGB(255,0,0,255));
hgeColorRGB white(ARGB(255,255,255,255));*/

class Vehicle{
	Vector2D loc;
};
class Game{
public:
	Vehicle car;
	void Init();
	void End();
	void Step();
	void Draw();
};
#endif
