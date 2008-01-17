#include "ResourceManager.h"
#include "system.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}
void ResourceManager::DestroyResources()
{
	std::map<std::string,Resource>::iterator deleteResource = ResourceMap.begin();
	for(;deleteResource!=ResourceMap.end();deleteResource++)
	{
		_deleteResource(&deleteResource->second);
		System::Log("Resource '%s' successfully freed!",deleteResource->first.c_str());
	}
	ResourceMap.clear();
}

SDL_Surface* ResourceManager::LoadTexture(char* filename, char* rsrcname)
{
	Resource rsrc;
	rsrc.type = RSRC_SURFACE;
	rsrc.rsrc.surface = SDL_DisplayFormatAlpha(IMG_Load(filename));
	if(rsrc.rsrc.surface!=0)
	{
		std::string name(rsrcname);
		ResourceMap[name] = rsrc;
		System::Log("Resource '%s' successfully loaded!",name.c_str());
	}
	else
	{
		System::Log("Failed to load resource '%s' from file: '%s'",rsrcname,filename);
		return 0;
	}
	return rsrc.rsrc.surface;
}
void ResourceManager::_deleteResource(Resource* rsrc)
{
	switch(rsrc->type)
	{
		case RSRC_SURFACE:
			SDL_FreeSurface(rsrc->rsrc.surface);
		break;
		case RSRC_DATA:
		break;
	}
}
Resource& ResourceManager::operator[] (char* resourcename)
{
	return ResourceMap[resourcename];
}
