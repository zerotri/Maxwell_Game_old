#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <hge.h>
#include <map>
#include <string>
typedef enum{
	RSRC_SURFACE,
	RSRC_DATA
}ResourceType;
typedef struct Resource_Struct{
	ResourceType type;
	union{
		HTEXTURE surface;
		char* data;
	}rsrc;
}Resource;
class ResourceManager
{
	public:
		ResourceManager();
		~ResourceManager();
		HTEXTURE LoadTexture(char* filename, char* rsrcname);

	protected:
	private:
		void _deleteResource(Resource* rsrc);
		std::map<std::string,Resource> ResourceMap;
};



#endif // RESOURCEMANAGER_H
