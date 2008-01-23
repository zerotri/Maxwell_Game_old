#ifndef LUASTATE_H
#define LUASTATE_H
#include <vector>
#include <string>
#include <squirrel.h>


class ScriptVM
{
	public:
		ScriptVM();
		~ScriptVM();
		//lua_State* getState();
		void resetState();
		void registerFunction(const char* _fname, SQFUNCTION _fptr);
		void setVariable(const char* _vname, int _vval);
		void setVariable(const char* _vname, float _vval);
		void setVariable(const char* _vname, const char* _vval);
		const char* getString(int _spos);
		float getNumber(int _spos);
		bool loadFile(const char* _fname);
		bool callFunction(const char* _fname);
		bool run();
		bool isError();
	protected:
	private:
		std::vector<std::string> errorStack;
		HSQUIRRELVM v;
};



#endif // LUASTATE_H
