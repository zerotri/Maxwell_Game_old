#include "Input.h"
extern HGE* hge;
#define INPUT_LOOP_ITERATOR(funcname, ...)\
		for(;vInputIterator!= vInputHandlers.end();vInputIterator++)\
		{\
			if((*vInputIterator)==NULL)\
				continue;\
			(*vInputIterator)->funcname(__VA_ARGS__);\
		}

Input::Input()
{
	vInputHandlers.reserve(8);
}

Input::~Input()
{
	std::vector<InputHandler*>::iterator vInputIterator = vInputHandlers.begin();
	INPUT_LOOP_ITERATOR(Destroy);
	vInputHandlers.clear();
}
void Input::Query()
{
	hgeInputEvent evt;
	std::vector<InputHandler*>::iterator vInputIterator;
	while(hge->Input_GetEvent(&evt))
	{
		vInputIterator = vInputHandlers.begin();
		switch(evt.type)
		{
			case INPUT_KEYDOWN:
				INPUT_LOOP_ITERATOR(onKeyPress, evt.key, evt.flags, evt.chr);
			break;
			case INPUT_KEYUP:
				INPUT_LOOP_ITERATOR(onKeyRelease, evt.key, evt.flags, evt.chr);
			break;
			case INPUT_MBUTTONDOWN:
				INPUT_LOOP_ITERATOR(onMousePress, evt.key, evt.x, evt.y);
			break;
			case INPUT_MBUTTONUP:
				INPUT_LOOP_ITERATOR(onMouseRelease, evt.key, evt.x, evt.y);
			break;
			case INPUT_MOUSEMOVE:
				INPUT_LOOP_ITERATOR(onMouseMove, evt.x, evt.y);
			break;
			case INPUT_MOUSEWHEEL:
				INPUT_LOOP_ITERATOR(onMouseWheel, evt.wheel, evt.x, evt.y);
			break;
		}
	}
}
void Input::AddInputHandler(InputHandler* newInput)
{
	if(newInput == NULL)
		return;
	vInputHandlers.push_back(newInput);
}


