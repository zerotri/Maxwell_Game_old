#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#define INCLUDE_LIBS_ONLY
#include "main.h"
#include "API_Base.h"
#include <map>
#include <string>
//An enumeration of all the resource types, so we
//know what kind of resource we're dealing with.
typedef enum ResourceType_Enum{
	RSRC_SURFACE,
	RSRC_DATA
}ResourceType;

//This is the basic resource structure. It contains
//
typedef struct Resource_Struct{
	ResourceType type;
	union{
		GfxSurface surface;
		char* data;
	}rsrc;
}Resource;
class ResourceManager
{
	public:
		ResourceManager();
		~ResourceManager();
		void DestroyResources();
		Resource& operator[] (char* resourcename);
		GfxSurface LoadTexture(char* filename, char* rsrcname);
		void SetAPI(API_Base* _api);

	protected:
	private:
		void _deleteResource(Resource* rsrc);
		std::map<std::string,Resource> ResourceMap;
		API_Base* api;
};



#endif // RESOURCEMANAGER_H
