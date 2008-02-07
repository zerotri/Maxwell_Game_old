#include "ApplicationBase.h"
#include "API_Base.h"

ApplicationBase::ApplicationBase(API_Base* api)
{
	_Api = api;
	_Api->Sys_SetCallBack(this);
	_System = new System();
	_Input = new Input();
	_Graphics = new Graphics();
	_ResourceManager = new ResourceManager();
	_VariableMap = new VariableMap();
	_GameWorld = new GameWorld();
	_System->SetAPI(_Api);
	_Graphics->SetAPI(_Api);
	_Input->SetAPI(_Api);
	_ResourceManager->SetAPI(_Api);
}
bool ApplicationBase::Run()
{
	_System->Log("Creating ApplicatinBase@[0x%08x]",this);
	_System->SetFrameFunc(this);
	_Graphics->SetRenderFunc(this);
	_Input->AddInputHandler(this);
	_System->Log("Initializing ApplicatinBase::_System@[0x%08x]",_System);
	if(_System->Init())
	{
		Init();
		_GameWorld->setGfx(_Graphics);
		_System->Log("Running System");
		//if(Sys_RunConstant
		{
			_System->Run();
		}
	}
	else
	{
		_System->Log("Could not initialize System@[0x%08x]",&_System);
		return true;
	}
	return true;
}
bool ApplicationBase::Shutdown()
{
	_System->Log("\t Calling Application::Shutdown()");
	return true;
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
		bool ret = FrameFunc();
		_Input->Query();
		_Graphics->Render();
		return ret;
}
bool ApplicationBase::_Render()
{
		return RenderFunc();
}
bool ApplicationBase::FrameFunc()
{
	return true;
}
bool ApplicationBase::RenderFunc()
{
	return true;
}
ApplicationBase::~ApplicationBase()
{
	//Tell Resource Manager to free all resources
	//_ResourceManager->DestroyResources();
	//this->Destroy();
	//_Input->~Input();
	//_GameWorld->~GameWorld();
	//_VariableMap->~VariableMap();
	//_System->~System();
	//delete _Input;
	delete _VariableMap;
	delete _GameWorld;
	delete _Graphics;
	delete _ResourceManager;
	delete _System;
	delete _Api;
}

