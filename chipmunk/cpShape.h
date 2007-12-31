/* Copyright (c) 2007 Scott Lembcke
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
void cpResetShapeIdCounter(void);

typedef enum cpShapeType{
	CP_CIRCLE_SHAPE,
	CP_SEGMENT_SHAPE,
	CP_POLY_SHAPE,
	CP_NUM_SHAPES
} cpShapeType;

typedef struct cpShape{
	cpShapeType type;
	cpBB (*cacheData)(struct cpShape *shape, cpVect p, cpVect rot);
	void (*destroy)(struct cpShape *shape);
		
	unsigned long id;
	cpBB bb;
	
	unsigned long collision_type;
	unsigned long group;
	unsigned long layers;
	
	void *data;
	
	cpBody *body;
	cpFloat e, u;
	cpVect surface_v;
} cpShape;

// low level shape init func
cpShape* cpShapeInit(cpShape *shape, cpShapeType type, cpBody *body);

void cpShapeDestroy(cpShape *shape);
void cpShapeFree(cpShape *shape);

cpBB cpShapeCacheBB(cpShape *shape);


typedef struct cpCircleShape{
	cpShape shape;
	
	cpVect c;
	cpFloat r;
	
	cpVect tc;
} cpCircleShape;

cpCircleShape *cpCircleShapeAlloc(void);
cpCircleShape *cpCircleShapeInit(cpCircleShape *circle, cpBody *body, cpFloat radius, cpVect offset);
cpShape *cpCircleShapeNew(cpBody *body, cpFloat radius, cpVect offset);


typedef struct cpSegmentShape{
	cpShape shape;
	
	cpVect a, b, n;
	cpFloat r;
	cpVect ta, tb, tn;
} cpSegmentShape;

cpSegmentShape* cpSegmentShapeAlloc(void);
cpSegmentShape* cpSegmentShapeInit(cpSegmentShape *seg, cpBody *body, cpVect a, cpVect b, cpFloat r);
cpShape* cpSegmentShapeNew(cpBody *body, cpVect a, cpVect b, cpFloat r);
