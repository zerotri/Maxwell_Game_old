#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#define INCLUDE_LIBS_ONLY
#include "main.h"
#include "API_Base.h"
#include <map>
#include <string>
//An enumeration of all the resource types, so we
//know what kind of resource we're dealing with.
typedef enum ResourceTypes_Enum{
    RSRC_NONE,
	RSRC_SURFACE,
	RSRC_DATA
}ResourceTypes;
typedef unsigned int ResourceType;

//This is the basic resource structure. It contains
//
class Resource{
    public:
        virtual unsigned int GetSize(){return 0;};
        virtual void* GetData(){return NULL;};
        virtual bool Load(char* filename, API_Base* _api){return false;};
        virtual void Destroy(API_Base* _api){};
    protected:
        virtual void RegisterType(){type = RSRC_NONE;};
        ResourceType type;
        unsigned int size;
};
class SurfaceResource : public Resource{
    public:
        virtual unsigned int GetSize();
        virtual void* GetData();
        virtual bool Load(char* filename, API_Base* _api);
        virtual void Destroy(API_Base* _api);
    private:
        GfxSurface surface;
};
class ResourceManager
{
	public:
		ResourceManager();
		~ResourceManager();
		void DestroyResources();
		Resource* operator[] (char* resourcename);
		Resource* LoadResource(char* filename, char* rsrcname);
		int LoadMapFile(char* filename);
		int GetMemoryUsage();
		int GetMemoryUsage(Resource* rsrc);
		void SetAPI(API_Base* _api);

	protected:
	private:
		void _deleteResource(std::pair<std::string,Resource*> resource);
		std::map<std::string,Resource*> ResourceMap;
		API_Base* api;
		unsigned long long int memUsage;
};



#endif // RESOURCEMANAGER_H
