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
 
typedef struct cpHandle{
	void *obj;
	int retain;
	int stamp;
} cpHandle;

typedef struct cpSpaceHashBin{
	cpHandle *handle;
	struct cpSpaceHashBin *next;
} cpSpaceHashBin;

typedef cpBB (*cpSpaceHashBBFunc)(void *obj);

typedef struct cpSpaceHash{
	int size;
	cpFloat celldim;
	cpSpaceHashBBFunc bbfunc;

	cpHashSet *handleSet;
	
	cpSpaceHashBin **cells;
	cpSpaceHashBin *bins;

	int stamp;
} cpSpaceHash;

cpSpaceHash *cpSpaceHashAlloc(void);
cpSpaceHash *cpSpaceHashInit(cpSpaceHash *hash, cpFloat celldim, int cells, cpSpaceHashBBFunc bbfunc);
cpSpaceHash *cpSpaceHashNew(cpFloat celldim, int cells, cpSpaceHashBBFunc bbfunc);

void cpSpaceHashDestroy(cpSpaceHash *hash);
void cpSpaceHashFree(cpSpaceHash *hash);

void cpSpaceHashResize(cpSpaceHash *hash, cpFloat celldim, int cells);

void cpSpaceHashInsert(cpSpaceHash *hash, void *obj, unsigned long id, cpBB bb);
void cpSpaceHashRemove(cpSpaceHash *hash, void *obj, unsigned long id);

typedef void (*cpSpaceHashIterator)(void *obj, void *data);
void cpSpaceHashEach(cpSpaceHash *hash, cpSpaceHashIterator func, void *data);

void cpSpaceHashRehash(cpSpaceHash *hash);
void cpSpaceHashRehashObject(cpSpaceHash *hash, void *obj, unsigned long id);

typedef int (*cpSpaceHashQueryFunc)(void *obj1, void *obj2, void *data);
void cpSpaceHashQuery(cpSpaceHash *hash, void *obj, cpBB bb, cpSpaceHashQueryFunc func, void *data);
void cpSpaceHashQueryInsert(cpSpaceHash *hash, void *obj, cpBB bb, cpSpaceHashQueryFunc func, void *data);
void cpSpaceHashQueryRehash(cpSpaceHash *hash, cpSpaceHashQueryFunc func, void *data);
