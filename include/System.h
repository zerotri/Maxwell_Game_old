#ifndef SYSTEM_H
#define SYSTEM_H
#include "API_Base.h"
#include <stdio.h>

class System;
class SysCallBack
{
	public:
		virtual bool _FrameFunc(){return false;};
};

class System
{
	public:
		System();
		~System();
		int Init();
		void Run();
		void End();
		void Log(char* format,...);
		void Sleep(int count);
		void SetFrameFunc(SysCallBack* frameFunc);
		void SetAPI(API_Base* _api);
		int FPS();
		float getFrameTime();
	protected:
	private:
		int nFPS;
		float frameTime;
		bool bActive;
		SysCallBack* _private_FrameFunc;
		API_Base* api;
		FILE* _logFile;
};



#endif // SYSTEM_H
