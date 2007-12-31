#include <hgecolor.h>
#include "vector.h"
#include "lua_utils.h"
#include "LuaVM.h"
#include "Input.h"
#include "System.h"
#include "GameAnimation.h"
#include "GameWorld.h"
#include "utils.h"
extern "C" {
	#include <lua.h>
	#include "lualib.h"
	#include "lauxlib.h"
}

hgeColorRGB black(ARGB(255,0,0,0));
hgeColorRGB blue(ARGB(255,0,0,255));
hgeColorRGB white(ARGB(255,255,255,255));

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
