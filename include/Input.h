#ifndef INPUT_H
#define INPUT_H
#include <vector>
#include <sdl.h>

class InputHandler;
class Input
{
	public:
		Input();
		~Input();
		void Query();
		void AddInputHandler(InputHandler* newInput);
		int GetMsgCount();
		bool GetKeyState(unsigned char key);
	protected:
		std::vector<InputHandler*> vInputHandlers;
	private:
		unsigned char* keys;
		long long int msgCount;
		int updateInterval;
		std::vector<SDL_Event> delayedEventQueue;
};

class InputHandler
{
	public:
		InputHandler(){Create();};
		virtual ~InputHandler(){is_dead = true;};
		void Create() {is_dead = false;};
		void Destroy() {this->~InputHandler();};
		int Exists() {return (is_dead == true);};
		virtual void onKeyPress(int keyboard_key, int keyboard_flag, int keyboard_char) {};
		virtual void onKeyRelease(int keyboard_key, int keyboard_flag, int keyboard_char) {};
		virtual void onMouseMove(float mouse_x, float mouse_y) {};
		virtual void onMousePress(int mouse_button, float mouse_x, float mouse_y) {};
		virtual void onMouseRelease(int mouse_button, float mouse_x, float mouse_y) {};
		virtual void onMouseWheel(int degrees, float mouse_x, float mouse_y) {};
		virtual void onMouseFocus(float mouse_x, float mouse_y) {};
		virtual void onAppClose() {};
		virtual void onAppMinimize() {};
	private:
		int is_dead;
};

#endif // INPUT_H
