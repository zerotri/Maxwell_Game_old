#include "ResourceManager.h"
extern HGE *hge;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	std::map<std::string,Resource>::iterator deleteResource = ResourceMap.begin();
	for(;deleteResource!=ResourceMap.end();deleteResource++)
	{
		_deleteResource(&deleteResource->second);
		hge->System_Log("Resource '%s' successfully freed!",deleteResource->first.c_str());
	}
	ResourceMap.clear();
}

HTEXTURE ResourceManager::LoadTexture(char* filename, char* rsrcname)
{
	Resource rsrc;
	rsrc.type = RSRC_SURFACE;
	rsrc.rsrc.surface = hge->Texture_Load(filename);
	if(rsrc.rsrc.surface!=0)
	{
		std::string name(rsrcname);
		ResourceMap[name] = rsrc;
		hge->System_Log("Resource '%s' successfully loaded!",name.c_str());
	}
	else
	{
		hge->System_Log("Failed to load resource '%s' from file: '%s'",rsrcname,filename);
		return 0;
	}
	return rsrc.rsrc.surface;
}
void ResourceManager::_deleteResource(Resource* rsrc)
{
	switch(rsrc->type)
	{
		case RSRC_SURFACE:
			hge->Texture_Free(rsrc->rsrc.surface);
		break;
		case RSRC_DATA:
		break;
	}
}
