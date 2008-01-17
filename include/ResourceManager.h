#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#define INCLUDE_LIBS_ONLY
#include <main.h>
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
		SDL_Surface* surface;
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
		SDL_Surface* LoadTexture(char* filename, char* rsrcname);

	protected:
	private:
		void _deleteResource(Resource* rsrc);
		std::map<std::string,Resource> ResourceMap;
};



#endif // RESOURCEMANAGER_H
