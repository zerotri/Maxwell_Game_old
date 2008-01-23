#include "ScriptVM.h"
#include "sqstdmath.h"
#include "sqstdaux.h"
#include "sqstdstring.h"
#include "sqstdio.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef SQUNICODE
#define scvprintf vwprintf
#else
#define scvprintf vprintf
#endif

void printfunc(HSQUIRRELVM v, const SQChar *s, ...)
{
va_list arglist;
va_start(arglist, s);
scvprintf(s, arglist);
va_end(arglist);
}

ScriptVM::ScriptVM()
{
	v = sq_open(1024); // creates a VM with initial stack size 1024

	//sq_pushroottable(v); //push the root table were to register the lib function
	//sqstd_register_iolib(v);
	//sqstd_seterrorhandlers(v); //registers the default error handlers

	//sq_setprintfunc(v, printfunc); //sets the print function

	sq_pushroottable(v); //push the root table(were the globals of the script will be stored)
	if(SQ_SUCCEEDED(sqstd_dofile(v, _SC("test.nut"), SQFalse, SQTrue))) // also prints syntax errors if any
	{
		//call_foo(v,1,2.5,_SC("teststring"));
	}
	/*luaVM = NULL;
	luaVM = lua_open();*/
}
ScriptVM::~ScriptVM()
{
	sq_pop(v,1); //pops the root table
	sq_close(v);
	/*if(luaVM != NULL)
	{
		lua_close(luaVM);
	}*/
}

void ScriptVM::resetState()
{
	/*if(luaVM != NULL)
	{
		lua_close(luaVM);
	}
	luaVM = lua_open();*/
}
void ScriptVM::registerFunction(const char* _fname, SQFUNCTION _fptr)
{
	//lua_register(luaVM,_fname,_fptr);
	/*lua_pushstring(luaVM, _fname);
	lua_pushcclosure(luaVM, _fptr, 0);
	lua_settable(luaVM, LUA_GLOBALSINDEX);*/
}
void ScriptVM::setVariable(const char* _vname, int _vval)
{
	/*lua_pushstring(luaVM, _vname);
	lua_pushnumber(luaVM, (lua_Number)_vval);
	lua_settable(luaVM, LUA_GLOBALSINDEX);*/
}
void ScriptVM::setVariable(const char* _vname, float _vval)
{
	/*lua_pushstring(luaVM, _vname);
	lua_pushnumber(luaVM, _vval);
	lua_settable(luaVM, LUA_GLOBALSINDEX);*/
}
void ScriptVM::setVariable(const char* _vname, const char* _vval)
{
	/*lua_pushstring(luaVM, _vname);
	lua_pushstring(luaVM, _vval);
	lua_settable(luaVM, LUA_GLOBALSINDEX);*/
}
const char* ScriptVM::getString(int _spos)
{
	//return lua_tostring(luaVM, _spos);
}
float ScriptVM::getNumber(int _spos)
{
	//return lua_tonumber(luaVM, _spos);
}
bool ScriptVM::loadFile(const char* _fname)
{
	//return luaL_loadfile(luaVM, _fname);
}
bool ScriptVM::callFunction(const char* _fname)
{
	/*lua_getglobal(luaVM, _fname);    // function to be called
	// do the call (1 arguments, 0 result)
	if(lua_isfunction(luaVM, -1))
	{
		return run();
	}else{
		return 1;
	}*/
}
bool ScriptVM::run()
{
	//return lua_pcall(luaVM, 0, 0, 0);
}
bool ScriptVM::isError()
{
	//return (errorStack.size() != 0);
}
