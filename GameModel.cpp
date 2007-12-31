#include "GameModel.h"
#include <string.h>
#include <hge.h>

extern HGE *hge;

GameModel::GameModel(cpSpace* space)
{
	int i;
	cpFloat terrain_datum[8] = {
		32.0f,	32.0f,
		64.0f,	128.0f,
		128.0f,	256.0f,
		32.0f,	32.0f,
	};
	XMLNode xMainNode = XMLNode::openFileHelper("testmodel.xml","MDL");
	 // this prints "<Condor>":
	XMLNode xNode=xMainNode.getChildNode("Header");
	hge->System_Log("Application Name is: '%s'\n",
	xNode.getChildNode("Application").getAttribute("name"));
	XMLNode xHeader=xMainNode.getChildNode("Header");
	hge->System_Log("App Name:%s",
	xHeader.getChildNode("Application").getAttribute("name"));
	XMLNode xData=xMainNode.getChildNode("Data");
	int numPts = xData.nChildNode("Point")+1;
	cpVect* pvtx = new cpVect[numPts];
	cpBody* modelBody = cpBodyNew(INFINITY, INFINITY);
	cpVect a = cpv(0.0, 0.0);
	int myIterator=0;
	XMLNode xPoint;
	char _x[256];
	char _y[256];
	float _vx;
	float _vy;
	for(i=1; i<numPts; i++){
		xPoint = xData.getChildNode("Point",&myIterator);
		strcpy(_x,xPoint.getAttribute("x"));
		strcpy(_y,xPoint.getAttribute("y"));
		_vx = (float)atof( _x);
		_vy = (float)atof( _y);
		hge->System_Log("AddPoint(%d,%d)",_vx,_vy);
		cpVect b = cpv(_vx, _vy);
		cpShape *colSeg = cpSegmentShapeNew(modelBody, a, b, 0.0f);
		colSeg->u = 1.0;
		cpSpaceAddStaticShape(space, colSeg);
		a = b;
	  }
	  modelShape = cpPolyShapeNew(modelBody, numPts, pvtx, cpv(0.0, 0.0));
}

GameModel::~GameModel()
{
	//dtor
}
bool GameModel::loadModel(const char* _fname)
{
	/*XMLNode xMainNode=XMLNode::openFileHelper(_fname,"MDL");
	XMLNode xNode=xMainNode.getChildNode("Header");
	XMLNode xData=xMainNode.getChildNode("Data");
    printf("  model made for %s version %s\n",
			xNode.getChildNode("Application").getAttribute("name"),
			xNode.getChildNode("Application").getAttribute("version"));
    printf("  Model name: %s version %s\n",
			xNode.getChildNode("Model").getAttribute("name"));
	xNode.getChildNode("Model").getAttribute("name")
	int numPts = xData.nChildNode("Point");*/
	return true;
}
cpBody* GameModel::getBody()
{
	return modelShape->body;
}
cpShape* GameModel::getShape()
{
	return modelShape;
}

