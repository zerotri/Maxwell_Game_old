#include "ApplicationBase.h"


ApplicationBase::ApplicationBase()
{
}
bool ApplicationBase::Run()
{
	_System.Log("Creating ApplicatinBase@[0x%08x]",this);
	_System.SetFrameFunc(this);
	_Input.AddInputHandler(this);
	_System.Log("Initializing ApplicatinBase::_System@[0x%08x]",&_System);
	if(_System.Init())
	{
		Init();
		_GameWorld.setGfx(&_Graphics);
		_System.Log("Running System");
		_System.Run();
	}
	else
	{
		_System.Log("Could not initialize System@[0x%08x]",&_System);
		return true;
	}
	return true;
}
bool Shutdown()
{
}
bool ApplicationBase::Init()
{
	return true;
}
bool ApplicationBase::End()
{
	return true;
}
bool ApplicationBase::_FrameFunc()
{
		return FrameFunc();
}
bool ApplicationBase::FrameFunc()
{
	return true;
}
ApplicationBase::~ApplicationBase()
{
	//Tell Resource Manager to free all resources
	_System.End();
	//_ResourceManager.DestroyResources();
	//this->Destroy();
	_Input.~Input();
	_GameWorld.~GameWorld();
	//_VariableMap.~VariableMap();
	_System.~System();
}

