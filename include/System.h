#ifndef SYSTEM_H
#define SYSTEM_H

#include <hge.h>
#include <stdarg.h>
#include <stdio.h>
#include "ResourceManager.h"


class System
{
	public:
		System();
		~System();
		int Init();
		void End();
		void Log(char* format,...);
		ResourceManager RsrcManager;
	protected:
	private:
};



#endif // SYSTEM_H
