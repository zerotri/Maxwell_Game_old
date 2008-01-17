#ifndef SYSTEM_H
#define SYSTEM_H
#include <sdl.h>
#include <stdarg.h>
#include <stdio.h>
class System;
class SysCallBack
{
	public:
		virtual bool _FrameFunc() = 0;
};
//typedef bool (*sysCallback)(System&,Graphics&);

class System
{
	public:
		System();
		~System();
		int Init();
		void Run();
		void End();
		static void Log(char* format,...);
		void Sleep(int count);
		void SetFrameFunc(SysCallBack* frameFunc);
		int FPS();
		float getFrameTime();
	protected:
	private:
		int nFPS;
		float frameTime;
		bool bActive;
		SysCallBack* _private_FrameFunc;
};



#endif // SYSTEM_H
