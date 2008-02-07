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
}

Input::~Input()
{
	std::vector<InputHandler*>::iterator vInputIterator = vInputHandlers.begin();
	INPUT_LOOP_ITERATOR(Destroy);
	vInputHandlers.clear();
}
void Input::Query()
{
	if(!api)
		return;
	InputEvent evt;
	evt.type = InputEvent::Evt_None;
	std::vector<InputHandler*>::iterator vInputIterator;
	while(api->Input_GetEvent(&evt))
	{
		msgCount++;
		vInputIterator = vInputHandlers.begin();
		switch(evt.type)
		{
			case InputEvent::Evt_KeyPress:
				INPUT_LOOP_ITERATOR(onKeyPress,
									evt.key.keyboard_key,
									evt.key.keyboard_flag,
									evt.key.keyboard_char);
			break;
			case InputEvent::Evt_KeyRelease:
				INPUT_LOOP_ITERATOR(onKeyRelease,
									evt.key.keyboard_key,
									evt.key.keyboard_flag,
									evt.key.keyboard_char);
			break;
			case InputEvent::Evt_MousePress:
				INPUT_LOOP_ITERATOR(onMousePress,
									evt.mouse.button,
									evt.mouse.x,
									evt.mouse.y);
			break;
			case InputEvent::Evt_MouseRelease:
				INPUT_LOOP_ITERATOR(onMouseRelease,
										evt.mouse.button,
										evt.mouse.x,
										evt.mouse.y);
			break;
			case InputEvent::Evt_MouseWheel:
					INPUT_LOOP_ITERATOR(onMouseWheel,
										evt.mouse.degrees,
										evt.mouse.x,
										evt.mouse.y);
			break;
			case InputEvent::Evt_MouseMove:
				INPUT_LOOP_ITERATOR(onMouseMove,
									evt.mouse.x,
									evt.mouse.y);
			break;
			default:
			break;
		}
	}
}
bool Input::GetKeyState(unsigned char key)
{
	return api->Input_GetKeyState(key);
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
void Input::SetAPI(API_Base* _api)
{
	api = _api;
}
