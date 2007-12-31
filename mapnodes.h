#include <stdio.h>
#include <stdint.h>
#define MAP_NODE_WIDTH	8
#define MAP_NODE_HEIGHT	8
typedef enum{
	MNPOS_NORTH,
	MNPOS_SOUTH,
	MNPOS_EAST,
	MNPOS_WEST,
	MNPOS_UP,
	MNPOS_DOWN
}MapNode_Position;
struct PhysicalMapNode{
	uint64_t ulNodeID;
	uint32_t uiNodeTileData[MAP_NODE_WIDTH][MAP_NODE_HEIGHT];
	uint32_t uiNodeNorth;
	uint32_t uiNodeSouth;
	uint32_t uiNodeEast;
	uint32_t uiNodeWest;
	uint32_t uiNodeUp;
	uint32_t uiNodeDown;
};
struct MapNode{
	uint64_t ulNodeID;
	uint32_t uiNodeTileData[MAP_NODE_WIDTH][MAP_NODE_HEIGHT];
	MapNode* pNodeNorth;
	MapNode* pNodeSouth;
	MapNode* pNodeEast;
	MapNode* pNodeWest;
	MapNode* pNodeUp;
	MapNode* pNodeDown;
};
struct MapView{
	MapNode** pViewNodes;
	uint32_t uiNumNodes;
};
class MapBuilder{
	MapView viewCurrent;
	MapNode** pMapNodes;
	uint32_t uiNumNodes;
	uint64_t ulCurNodeID;
public:
	MapBuilder() :
		uiNumNodes(0),
		pMapNodes(NULL)
	{
		viewCurrent.pViewNodes = NULL;
		viewCurrent.uiNumNodes = 0;
	}
	int NewNode(MapNode_Position)
	{
	}
};

int main(int argc, char** argv)
{
	MapBuilder builder;
	return false;
}

