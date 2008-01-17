#include "VariableMap.h"


VariableMap::VariableMap()
{
	//ctor
}

VariableMap::~VariableMap()
{
	//dtor
}

int& VariableMap::operator [] (std::string var)
{
	return varMap[var];
}
