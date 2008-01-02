#include "utils.h"
#include <hgecolor.h>
#include <math.h>
extern HGE* hge;
hgeColor	drawColor;
float 		drawLayer = 0.5f;
void Gfx_DrawLine (float x1, float y1, float x2, float y2)
{
	hge->Gfx_RenderLine(x1,y1,x2,y2,HWCOL(drawColor),drawLayer);
}

void Gfx_DrawTriangle (float x1, float y1, float x2, float y2, float x3, float y3)
{
	hgeTriple _renderTriple;
	SET_XY(_renderTriple.v[0],x1,y1);
	SET_XY(_renderTriple.v[1],x2,y2);
	SET_XY(_renderTriple.v[2],x3,y3);
	_renderTriple.v[0].z = drawLayer;
	_renderTriple.v[1].z = drawLayer;
	_renderTriple.v[2].z = drawLayer;
	_renderTriple.v[0].col = HWCOL(drawColor);
	_renderTriple.v[1].col = HWCOL(drawColor);
	_renderTriple.v[2].col = HWCOL(drawColor);
	hge->Gfx_RenderTriple(&_renderTriple);
}

void Gfx_DrawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	hgeQuad _renderQuad;
	SET_XY(_renderQuad.v[0],x1,y1);
	SET_XY(_renderQuad.v[1],x2,y2);
	SET_XY(_renderQuad.v[2],x3,y3);
	_renderQuad.v[0].z = drawLayer;
	_renderQuad.v[1].z = drawLayer;
	_renderQuad.v[2].z = drawLayer;
	_renderQuad.v[0].col = HWCOL(drawColor);
	_renderQuad.v[1].col = HWCOL(drawColor);
	_renderQuad.v[2].col = HWCOL(drawColor);
	hge->Gfx_RenderQuad(&_renderQuad);
}

void Draw_Circle(float cx, float cy, float Radius, int Segments, DWORD color)
{
  float EachAngle;
  float a;
  float x1;
  float x2;
  float y1;
  float y2;

  EachAngle = 2.0 * M_PI / (float)Segments;

  x2 = Radius;
  y2 = 0.0;

  for(a=0.0; a<= (2.0*M_PI + EachAngle); a+=EachAngle) {
    x1 = x2;
    y1 = y2;
    x2 = Radius * cos(a);
    y2 = Radius * sin(a);
    hge->Gfx_RenderLine(x1+cx, y1+cy, x2+cx, y2+cy, color);
  }
}
