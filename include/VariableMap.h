#ifndef VARIABLEMAP_H
#define VARIABLEMAP_H

#include <map>
#include <string>


class VariableMap
{
	public:
		VariableMap();
		~VariableMap();
		int& operator [] (std::string var);
	protected:
	private:
	std::map<std::string, int> varMap;
};



#endif // VARIABLEMAP_H
