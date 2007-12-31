#ifndef LUASTATE_H
#define LUASTATE_H
#include <vector>
#include <string>
extern "C" {
	#include <lua.h>
	#include "lualib.h"
	#include "lauxlib.h"
}


class LuaVM
{
	public:
		LuaVM();
		~LuaVM();
		lua_State* getState();
		void resetState();
		void registerFunction(const char* _fname, lua_CFunction _fptr);
		void setVariable(const char* _vname, int _vval);
		void setVariable(const char* _vname, lua_Number _vval);
		void setVariable(const char* _vname, const char* _vval);
		const char* getString(int _spos);
		lua_Number getNumber(int _spos);
		bool loadFile(const char* _fname);
		bool callFunction(const char* _fname);
		bool run();
		bool isError();
	protected:
	private:
		std::vector<std::string> errorStack;
		lua_State* luaVM;
};



#endif // LUASTATE_H
