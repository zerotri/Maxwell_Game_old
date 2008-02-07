#include "ResourceManager.h"
#include "utils.h"
#include <algorithm>
#include "other_mem_fun.h"

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
    for_each(   ResourceMap.begin(),
                ResourceMap.end(),
                other_mem_fun(this, &ResourceManager::_deleteResource));
	ResourceMap.clear();
}

Resource* ResourceManager::LoadResource(char* filename, char* rsrcname)
{
	Resource* rsrc = new SurfaceResource();
	if(!rsrc->Load(filename, api))
	{
		std::string name(rsrcname);
		ResourceMap[name] = rsrc;
		Log("Load Resource: '%s' [%i KBytes] ",name.c_str(),rsrc->GetSize()/1024);
		Log("\tat location: [%i]",ResourceMap[name]);
		Log("\tat location: [%i]",rsrc);
		memUsage += rsrc->GetSize();
		return rsrc;
	}
	else
	{
		Log("Failed to load resource '%s' from file: '%s'",rsrcname,filename);
		return NULL;
	}
}
void ResourceManager::_deleteResource(std::pair<std::string,Resource*> resource)
{
    Log("Resource '%s' successfully freed!",resource.first.c_str());
    Resource* re = resource.second;
    memUsage -= re->GetSize();
    re->Destroy(api);
}
Resource* ResourceManager::operator[] (char* resourcename)
{
	return ResourceMap[resourcename];
}
int ResourceManager::GetMemoryUsage()
{
	return memUsage;
}
int ResourceManager::GetMemoryUsage(Resource* rsrc)
{
	return rsrc->GetSize();
}

unsigned int SurfaceResource::GetSize()
{
    return size;
};
void* SurfaceResource::GetData()
{
    return (void*)surface;
};
bool SurfaceResource::Load(char* filename, API_Base* _api)
{
	type = RSRC_SURFACE;
	surface = _api->Surface_Load(filename);
	if(surface!=0)
	{
	    size = _api->Surface_GetMemoryUsage(surface);
		return false;
	}
	else
	{
	    type = RSRC_NONE;
	    size = 0;
		return true;
	}
};
void SurfaceResource::Destroy(API_Base* _api)
{
    if(surface!=0)
    {
        _api->Surface_Free(surface);
    }
    size = 0;
    type = RSRC_NONE;
};
