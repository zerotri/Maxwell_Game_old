#ifndef APPLICATIONBASE_H
#define APPLICATIONBASE_H
#include "System.h"
#include "Input.h"
#include "Graphics.h"
#include "ResourceManager.h"
#include "GameWorld.h"
#include "VariableMap.h"

class ApplicationBase : public InputHandler, public SysCallBack
{
	public:
		ApplicationBase();
		virtual ~ApplicationBase();
		bool _FrameFunc();
		bool Run();
		bool Shutdown();
		virtual bool FrameFunc();
		virtual bool Init();
		virtual bool End();

		//Members
		System _System;
		ResourceManager _ResourceManager;
		Input _Input;
		Graphics _Graphics;
		//VariableMap _VariableMap;
		GameWorld _GameWorld;
	protected:
	private:
};



#endif // APPLICATIONBASE_H