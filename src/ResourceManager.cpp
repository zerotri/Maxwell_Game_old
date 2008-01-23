#include "ResourceManager.h"
#include "utils.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	DestroyResources();
}
void ResourceManager::SetAPI(API_Base* _api)
{
	api = _api;
}
void ResourceManager::DestroyResources()
{
	std::map<std::string,Resource>::iterator deleteResource = ResourceMap.begin();
	for(;deleteResource!=ResourceMap.end();deleteResource++)
	{
		_deleteResource(&deleteResource->second);
		Log("Resource '%s' successfully freed!",deleteResource->first.c_str());
	}
	ResourceMap.clear();
}

GfxSurface ResourceManager::LoadTexture(char* filename, char* rsrcname)
{
	Resource rsrc;
	rsrc.type = RSRC_SURFACE;
	rsrc.rsrc.surface = api->Surface_Load(filename);
	if(rsrc.rsrc.surface!=0)
	{
		std::string name(rsrcname);
		ResourceMap[name] = rsrc;
		Log("Resource '%s' successfully loaded!",name.c_str());
	}
	else
	{
		Log("Failed to load resource '%s' from file: '%s'",rsrcname,filename);
		return 0;
	}
	return rsrc.rsrc.surface;
}
void ResourceManager::_deleteResource(Resource* rsrc)
{
	switch(rsrc->type)
	{
		case RSRC_SURFACE:
			api->Surface_Free(rsrc->rsrc.surface);
		break;
		case RSRC_DATA:
		break;
	}
}
Resource& ResourceManager::operator[] (char* resourcename)
{
	return ResourceMap[resourcename];
}
