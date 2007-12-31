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
 
extern int cp_contact_persistence;

typedef int (*cpCollFunc)(cpShape *a, cpShape *b, cpContact *contacts, int numContacts, void *data);

typedef struct cpCollPairFunc {
	unsigned long a;
	unsigned long b;
	cpCollFunc func;
	void *data;
} cpCollPairFunc;

typedef struct cpSpace{
	int iterations;
//	int sleepTicks;
	
	cpVect gravity;
	cpFloat damping;
	
	int stamp;

	cpSpaceHash *staticShapes;
	cpSpaceHash *activeShapes;
	
	cpArray *bodies;
	cpArray *arbiters;
	cpHashSet *contactSet;
	
	cpArray *joints;
	
	cpHashSet *collFuncSet;
	cpCollPairFunc defaultPairFunc;
} cpSpace;

cpSpace* cpSpaceAlloc(void);
cpSpace* cpSpaceInit(cpSpace *space);
cpSpace* cpSpaceNew(void);

void cpSpaceDestroy(cpSpace *space);
void cpSpaceFree(cpSpace *space);
void cpSpaceFreeChildren(cpSpace *space);

void cpSpaceAddCollisionPairFunc(cpSpace *space, unsigned long a, unsigned long b,
                                 cpCollFunc func, void *data);
void cpSpaceRemoveCollisionPairFunc(cpSpace *space, unsigned long a, unsigned long b);
void cpSpaceSetDefaultCollisionPairFunc(cpSpace *space, cpCollFunc func, void *data);

void cpSpaceAddShape(cpSpace *space, cpShape *shape);
void cpSpaceAddStaticShape(cpSpace *space, cpShape *shape);
void cpSpaceAddBody(cpSpace *space, cpBody *body);
void cpSpaceAddJoint(cpSpace *space, cpJoint *joint);

void cpSpaceRemoveShape(cpSpace *space, cpShape *shape);
void cpSpaceRemoveStaticShape(cpSpace *space, cpShape *shape);
void cpSpaceRemoveBody(cpSpace *space, cpBody *body);
void cpSpaceRemoveJoint(cpSpace *space, cpJoint *joint);

typedef void (*cpSpaceBodyIterator)(cpBody *body, void *data);
void cpSpaceEachBody(cpSpace *space, cpSpaceBodyIterator func, void *data);

void cpSpaceResizeStaticHash(cpSpace *space, cpFloat dim, int count);
void cpSpaceResizeActiveHash(cpSpace *space, cpFloat dim, int count);
void cpSpaceRehashStatic(cpSpace *space);

void cpSpaceStep(cpSpace *space, cpFloat dt);
