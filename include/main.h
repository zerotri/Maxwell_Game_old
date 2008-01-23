#ifndef MAIN_H
#define MAIN_H

typedef void* GfxSurface;
typedef struct Rect_TYPE{
	unsigned int x;
	unsigned int y;
	unsigned int w;
	unsigned int h;
}Rect;

#ifndef INCLUDE_NO_LIBS
	#include <sdl.h>
	#include <sdl_image.h>
	#include <sge.h>
	#include "vector.h"
#endif
#ifndef INCLUDE_LIBS_ONLY
	#include "ScriptVM.h"
	#include "Input.h"
	#include "System.h"
	#include "Graphics.h"
	#include "GameAnimation.h"
	#include "GameWorld.h"
	//#include "utils.h"
#endif
#include "utils.h"
/*hgeColorRGB black(ARGB(255,0,0,0));
hgeColorRGB blue(ARGB(255,0,0,255));
hgeColorRGB white(ARGB(255,255,255,255));*/

/*class Vehicle{
	Vector2D<int> loc;
};
class Game{
public:
	Vehicle car;
	void Init();
	void End();
	void Step();
	void Draw();
};*/
#endif
