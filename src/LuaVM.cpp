#include "LuaVM.h"


LuaVM::LuaVM()
{
	luaVM = NULL;
	luaVM = lua_open();
}
LuaVM::~LuaVM()
{
	if(luaVM != NULL)
	{
		lua_close(luaVM);
	}
}

void LuaVM::resetState()
{
	if(luaVM != NULL)
	{
		lua_close(luaVM);
	}
	luaVM = lua_open();
}
void LuaVM::registerFunction(const char* _fname, lua_CFunction _fptr)
{
	lua_register(luaVM,_fname,_fptr);
	/*lua_pushstring(luaVM, _fname);
	lua_pushcclosure(luaVM, _fptr, 0);
	lua_settable(luaVM, LUA_GLOBALSINDEX);*/
}
void LuaVM::setVariable(const char* _vname, int _vval)
{
	lua_pushstring(luaVM, _vname);
	lua_pushnumber(luaVM, (lua_Number)_vval);
	lua_settable(luaVM, LUA_GLOBALSINDEX);
}
void LuaVM::setVariable(const char* _vname, lua_Number _vval)
{
	lua_pushstring(luaVM, _vname);
	lua_pushnumber(luaVM, _vval);
	lua_settable(luaVM, LUA_GLOBALSINDEX);
}
void LuaVM::setVariable(const char* _vname, const char* _vval)
{
	lua_pushstring(luaVM, _vname);
	lua_pushstring(luaVM, _vval);
	lua_settable(luaVM, LUA_GLOBALSINDEX);
}
const char* LuaVM::getString(int _spos)
{
	return lua_tostring(luaVM, _spos);
}
lua_Number LuaVM::getNumber(int _spos)
{
	return lua_tonumber(luaVM, _spos);
}
bool LuaVM::loadFile(const char* _fname)
{
	return luaL_loadfile(luaVM, _fname);
}
bool LuaVM::callFunction(const char* _fname)
{
	lua_getglobal(luaVM, _fname);    /* function to be called */
	/* do the call (1 arguments, 0 result) */
	if(lua_isfunction(luaVM, -1))
	{
		return run();
	}else{
		return 1;
	}
}
bool LuaVM::run()
{
	return lua_pcall(luaVM, 0, 0, 0);
}
bool LuaVM::isError()
{
	return (errorStack.size() != 0);
}
