#include "Input.h"
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
	msgCount = 0;
	keys = SDL_GetKeyState(NULL);
}

Input::~Input()
{
	std::vector<InputHandler*>::iterator vInputIterator = vInputHandlers.begin();
	INPUT_LOOP_ITERATOR(Destroy);
	vInputHandlers.clear();
	delayedEventQueue.clear();
}
void Input::Query()
{
	SDL_Event evt;
	std::vector<InputHandler*>::iterator vInputIterator;
	while(SDL_PollEvent(&evt))
	{
		msgCount++;
		vInputIterator = vInputHandlers.begin();
		switch(evt.type)
		{
			case SDL_KEYDOWN:
				INPUT_LOOP_ITERATOR(onKeyPress,
									evt.key.keysym.sym,
									evt.key.keysym.mod,
									evt.key.keysym.scancode);
			break;
			case SDL_KEYUP:
				INPUT_LOOP_ITERATOR(onKeyRelease,
									evt.key.keysym.sym,
									evt.key.keysym.mod,
									evt.key.keysym.scancode);
			break;
			case SDL_MOUSEBUTTONDOWN:
				INPUT_LOOP_ITERATOR(onMousePress,
									evt.button.button,
									evt.button.x,
									evt.button.y);
			break;
			case SDL_MOUSEBUTTONUP:
				if(evt.button.button == SDL_BUTTON_WHEELUP)
				{
					INPUT_LOOP_ITERATOR(onMouseWheel, +1,
										evt.button.x,
										evt.button.y);
				}
				else if(evt.button.button == SDL_BUTTON_WHEELDOWN)
				{
					INPUT_LOOP_ITERATOR(onMouseWheel, -1,
										evt.button.x,
										evt.button.y);
				}
				else
				{
					INPUT_LOOP_ITERATOR(onMouseRelease,
										evt.button.button,
										evt.button.x,
										evt.button.y);
				}
			break;
			case SDL_MOUSEMOTION:
				INPUT_LOOP_ITERATOR(onMouseMove,
									evt.motion.x,
									evt.motion.y);
			break;
		}
	}
}
bool Input::GetKeyState(unsigned char key)
{
	return (keys[key] == 1);
}
void Input::AddInputHandler(InputHandler* newInput)
{
	if(newInput == NULL)
		return;
	vInputHandlers.push_back(newInput);
}
int Input::GetMsgCount()
{
	return msgCount;
}


